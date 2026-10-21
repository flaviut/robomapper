# Prepare a fixed-frame raster edit locally

These commands prepare one raster on the local machine; they do not deploy it. **Edited-map loading remains untested.** Read the [edit constraints](../reference/maps/editing.md) first, retain an untouched matching set, and do not change frame, topology, poses or restrictions.

## Offline codec

The codec uses only Python's standard library. Run it locally from the repository root against a copied raster, not against the robot or the outer backup archive. `inspect` prints header fields and hashes; `export` writes raw cells as an 8-bit binary PGM; `pack` retains the original prefix and computes the new cell digest. These commands do not deploy anything:

```sh
work=$(mktemp -d /tmp/map-edit.XXXXXX)
python3 tools/map-maint/map_codec.py inspect SNAPSHOT.map
python3 tools/map-maint/map_codec.py export SNAPSHOT.map "$work/original.pgm"
# Save a deliberate same-size edit separately as "$work/edited.pgm".
python3 tools/map-maint/map_codec.py pack SNAPSHOT.map "$work/edited.pgm" "$work/candidate.map"
```

The private temporary directory keeps map contents out of shared output paths. Both output files must be new; the codec refuses to overwrite an existing destination. Keep the original raster and exported PGM unchanged. It rejects unsupported headers, dimension/length mismatches and a bad input digest; `pack` also requires a same-sized binary PGM with maximum value 255.

Native cell `(x,y)` is byte `30 + y*width + x`; no display-y inversion belongs here. Cells are consistent with 0=free, 128=unknown and 255=occupied, but intermediate probabilities are not calibrated. Do not copy display-preview colors or room-label bytes into the raster. The codec does not establish obstacle truth, robot clearance, room connectivity or correspondence with persistence.

## Deployment boundary — not demonstrated

1. Stage only the selected fixed-frame occupancy patch with the existing codec; preserve the untouched matching set and genuine backup. Reject the candidate if its intended meaning requires a changed doorway, disconnected room, map extent, origin, dock/pose or restriction geometry.
2. Use the [proposed whole-set replacement and cold-start path](matching-set-restore.md), not a live load. Keep automatic cleaning and other command producers gated; this guide supplies no live IPC sender or supervision commands.
3. Once the intended map is loaded, obtain its **current** room IDs and name mapping through the ordinary client. Do not reuse IDs from a cached screenshot or pre-edit response. If existing room labels are absent/incoherent, stop the hybrid path; split/merge is not a substitute for full regeneration.
4. If room boundaries alone need adjustment, use one ordinary split or two-room merge at a time, with the [native command encoding](../reference/maps/room-operations.md#valetudo-encoding-and-the-s7-generation-boundary). Let the native operation publish the label grid; then refresh the map and names before the next operation. Preserve the occupancy raster during these label operations; they are not obstacle editing commands.
5. Rename using a full refreshed list, unique current IDs and 1..23 ASCII bytes per name. Keep this first candidate to at most 16 rooms (the native stable-ID pool is 16..31), preferably the captured smaller room set. Retain the vendor `oldId`/`newId` association and refresh again: naming a temporary room can promote its ID. On failure, reacquire the current IDs instead of resending stale ones.
6. Allow ordinary native saves to settle before a later stopped snapshot. Preserve the resulting native matching set as a new state, separate from the original rollback set. A command reply or digest match alone is not evidence that the robot can safely navigate the edited geometry.

This path avoids implementing segmentation **only while the original occupancy frame and useful segmentation remain coherent**. Never delete a real obstacle to make a desired split succeed, or infer that a label merge opens a physical doorway.

If the intended correction changes room connectivity or coordinates, retain the original raster or use vendor remapping. Do not add manual segmentation as an automatic import repair.
