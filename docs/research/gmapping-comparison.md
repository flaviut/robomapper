# Is this firmware OpenSLAM GMapping?

**Do not use OpenSLAM's structures as this device's map-file schema.** The inspected firmware path implements particle prediction, grid scoring and resampling, but its actual representation and scoring sequence differ substantially from the available OpenSLAM implementation. A heavily rewritten descendant remains possible; this comparison found no distinctive evidence establishing that ancestry. The name `GMapping` alone is misleading evidence.

OpenSLAM is useful algorithm background, not a practical shortcut to editing persisted maps or room metadata. Continue from the device-specific grid and persistence readers already recovered here.

## Scope and inputs

Read-only local comparison; no firmware execution, robot access, builds, tests or existing validation suites. Temporary disassembly stayed in `/tmp`; existing exports and the closed Ghidra baseline were not changed.

- Source: `/home/user/dev/co/openslam_gmapping`, `ros-perception/openslam_gmapping` commit `5105476edb125bd3e05df3583b5817c486238dec`. Source paths below are relative to that checkout.
- Firmware: `binaries/4.3.5_1612/opt/rockrobo/cleaner/lib/`. `librrslamdrv.so` SHA256 `b48f5f56eb1b2d22abbf727725ea558762337f8f0103229d8da6c1ab6275608a`; `librrnavdrv.so` SHA256 `603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475` (identities recorded in existing component evidence).
- Method: source reading, ELF sections/imports/unwind entries, strings and LLVM 21 disassembly. Firmware addresses are virtual addresses. `.text` was decoded as Thumb; ARM PLT entries were inspected separately. Nearest-symbol labels in stripped disassembly are not function identities. Unnamed routines below are identified by address and observed behavior, not recovered source names.

## Observed comparison

### The navigation name belongs to a device-facing adapter

`librrnavdrv.so` retains global RTTI `8GMapping` and `11GMappingMap`, not the OpenSLAM namespace's `GMapping::GridSlamProcessor` or `GMapping::ScanMatcher`. Lambda RTTI includes `NotifySLAMCommand`, `_IPC_Slam_MapFlag`, `NavTimer` and relocation methods.

This is more than a name search: the routine at `0x2608dc`, identified by its `RequestSLAMGlobalRelocate` logging reference at `0x2608fc`, constructs a `GlobalRelocateTimer`, builds `_IPC_Slam_Status` sets and passes command `0x1d` to `0x25fcac` at `0x2609e8`. The candidate routine at `0x2616c8`, identified by `GetMovingRelocateCandidates`, iterates four-byte map flags and calls the `NotifySLAMCommand`-identified routine `0x25f4e4` with command `0x27` at `0x261758`. These are command/timer operations, not OpenSLAM's scan-processing loop.

### A reachable scoring/resampling path is structurally different

In `librrslamdrv.so`, the unwind-listed routine `0x1321c` provides a useful comparison path:

1. It passes a particle collection and common scan/grid context to `GOMP_parallel` at `0x132a4`. Resolving its PC-relative function pointer gives Thumb entry `0x113c1`, meaning code at `0x113c0`.
2. That worker partitions particle indices between OpenMP threads. Each particle advances **16 bytes**. Constructor `0x23814` copies three pose words and writes a float score at offset `12`; accessor `0x23828` reads that float. There is no room in this record for OpenSLAM's embedded map and trajectory-node fields.
3. Worker `0x113c0` transforms two-float scan points using each pose, rounds coordinates after multiplying by `20`, bounds-checks them and suppresses duplicate cells with a thread-local bitset (`0x115a4–0x11610`). It addresses a common byte grid as `base + (y-top)*width + (x-left)` (`0x11614–0x11638`). Predicate `0x2bc98` returns one for cell values **greater than `0x87`**. It stores the hit count divided by the counted unique endpoints as the particle's score (`0x1164c–0x1168e`).
4. Back in `0x1321c`, `0x22424` selects the maximum-score record, then `0x2259c` computes `(sum w)^2 / sum(w*w)` and compares it with **0.2N and 0.8N** (`0x225b2–0x2266e`; constants at `0x22690/0x22698`). Thus the effective-sample-size calculation is real, but generic.
5. Depending on that result and best score, it reaches rank/copy helpers `0x22b38` or `0x22b98`, then logs `Sharp resample: %d` at `0x1334c`. `0x22b38` calls sorting-shaped routine `0x22a48` and copies a selected prefix into the tail through `0x222d0`; the alternate helper also thresholds sorted scores. This observed branch is not OpenSLAM's cumulative-weight/random-offset index sampler. Later code can compute a weighted pose through `0x226b8` and maintain an inertial-particle list through `0x1a6e0`.

Compare the source's concrete sequence:

- `gridfastslam/gridslamprocessor.cpp`, `GridSlamProcessor::processScan`: draw odometry noise for each particle; gate by motion/time; scan-match; update trajectory-tree weights; resample; register scans.
- `include/gmapping/gridfastslam/gridslamprocessor.hxx`, `scanMatch/normalize/resample`: optimize each pose against **its own map**, add log likelihood to `weight/weightSum`, exponentiate shifted log weights, calculate effective sample size, select ancestor indices, create `TNode`s and register scans into copied maps.
- `include/gmapping/gridfastslam/gridslamprocessor.h`, `Particle`: embedded `ScanMatcherMap`, current/previous double-precision poses, several weights, previous index and `TNode*`. `include/gmapping/scanmatcher/smmap.h` defines cells as `PointAccumulator { FloatPoint acc; int n, visits; }` in `HierarchicalArray2D` storage.
- `scanmatcher/scanmatcher.cpp`, `ScanMatcher::optimize`, tries six axial/rotational neighbors and halves step sizes on refinement. Its inline `score/likelihoodAndScore` in `include/gmapping/scanmatcher/scanmatcher.h` searches a cell neighborhood, checks occupied/free cells and uses Gaussian distance from accumulated hit means. That is not the firmware worker's unique-endpoint byte-threshold fraction.
- `include/gmapping/particlefilter/particlefilter.h`, `uniform_resampler::resampleIndexes`, accumulates weights, chooses `interval*drand48()` and advances the target by a fixed interval. Neither ranking nor keeping a score-selected prefix defines that sampler.

The firmware path therefore supports a shared-grid pose-hypothesis filter interpretation, rather than identifying the inspected records as OpenSLAM's per-particle-map filter. This is a bounded path comparison, not an exhaustive inventory of every mapping mode.

### Motion and logging do not supply a missing fingerprint

Firmware predictor `0x1199c` calls `0x2bee4` to prepare motion, then loops over 16-byte records calling `0x2c0c0`, composing poses through `0x21cbc` and updating scores (`0x11a1e–0x11a88`). `0x2c0c0` adds three values returned by helper `0x3b810` to stored motion components before constructing a pose, consistent with sampled perturbations. Noise plus pose composition is not a distinctive fingerprint.

OpenSLAM's `gridfastslam/motionmodel.cpp`, `MotionModel::drawFromMotion`, has explicit `srr/str/srt/stt` relationships; its pose-difference overload includes cross-axis factor `0.3*srr`. Those equations were not matched to the inspected firmware path. Firmware imports C++ `random_device` and float math; source `utils/stat.cpp` uses `drand48` in its Gaussian sampler. These differences do not rule out rewritten code, but do not establish copying either.

Neither binary contains the checked OpenSLAM class/cell names or characteristic messages such as `Average Scan Matching Score=`, `Scan Matching Failed, using odometry. Likelihood=`, `Deleting Nodes:` and `Registering Scans:`. Conversely, source searches did not find firmware messages `Incoming particle`, `Sharp resample` or `need_resample`. Firmware does retain `rock::slam::system::Controller` in lambda/thread RTTI. Stripping and changed logging make absence weak evidence; the representation and call-path differences above carry more weight.

## Inference, unknowns and practical value

**Inference:** readily available OpenSLAM is not a drop-in source match for this firmware. Shared terminology, occupancy grids, noisy motion and effective sample size are not distinctive lineage markers. There is insufficient evidence to call this an OpenSLAM fork, and equally insufficient evidence to declare all its algorithms independently authored or categorically “proprietary.” Renaming, changing precision and replacing major data structures could conceal ancestry.

**Unknown:** other stripped paths or older source revisions might preserve copied routines. The full motion-noise equations and every resampling mode were not recovered. Resolving historical authorship would need a positive code fingerprint or build/source provenance, not device movement. That question need not block map research.

**Persisted data is a separate problem.** Existing [grid evidence](../../analysis/re/evidence/components/grid.json), backed by writer `0x1ab84` and reader `0x1d21c`, identifies the packed 30-byte `RRSLAM` v2 prefix, row-major byte cells and trailing cell-block digest. OpenSLAM's in-memory `PointAccumulator` and particle ancestry are not that format. The inspected source provides no device room-ID/name catalog or `PersistData` schema. Existing [room reconciliation findings](../../analysis/re/evidence/restore/room-reconcile/handoff.json) instead identify geometry-dependent low-six-bit label fills and AppProxy name/ID remapping; source GMapping does not explain those transformations.

A grid-image edit is technically plausible from the device-specific codec evidence. Preserving room identity, names and companion state after geometry changes remains the difficult part. Porting OpenSLAM or mapping its structs onto saved bytes does not solve it.

## Plausible next step

Use the recovered device readers to compare ordinary application-generated snapshots, not modified firmware. The smallest useful remaining observations are paired captures around **one room rename** and **one supported split/merge**, with unchanged physical geometry, selected map flag and the complete companion-state set recorded. Existing captures may already supply part of this comparison. These observations would separate name-only changes from label/geometry changes and show which persisted records move together.

No new device observation is required to reject OpenSLAM struct reuse. Before any edited-map restore, the separate unresolved issue is whether the active writer/cache state and all companion files can be captured and reloaded coherently; this comparison establishes no safe restore command or shutdown procedure. No robot operation is prescribed here.
