# Persistence loading and saving

Map-dependent persistence uses a shared buffer and detached serializer; catalog persistence writes synchronously. Neither provides a transaction across the map files. A successful API return can precede disk replacement or coexist with a write failure.

The addresses below refer to `librobopersist.so` in firmware `4.3.5_1612`. The [instruction-backed findings](../../../analysis/re/evidence/components/persistence.json) link to the corresponding decompiled functions. For copying files without relying on save acknowledgments, use the [stopped-backup procedure](../../guides/stopped-backup.md).

## Protobuf envelope

`PersistData_*.data` and `SharedMultiMapInfo` use this schema, embedded in `librobopersist.so` at file offset `0x1efc8`:

```proto
syntax = "proto3";
package robopersist;

message PersistInfo {
  int32 id = 10;
  string name = 20;
}

message PersistRegionInfo {
  int32 id = 10;
  bool compress = 20;
  bool encrypt = 30;
  uint32 rawDataSize = 40;
  repeated bytes value = 50;
  repeated uint32 rawDataPartSize = 60;
}

message PersistData {
  PersistInfo persistInfo = 10;
  repeated PersistRegionInfo regionInfo = 20;
}
```

Region IDs describe payload types, not map flags or filename suffixes. The decompressed bytes have separate [region layouts](regions.md); preserving the protobuf envelope alone does not preserve their meaning.

## Map-dependent saves

`PersistSaveMapInfo(vector<flag>)`, at `0x1bb20`, performs these operations:

1. Lock persistence type 0 and find its subscribed regions. With no subscriptions, return true without writing a file.
2. Convert destination flags to a bitmask and cancel older buffered work for those destinations.
3. Wait for buffer capacity. The outer wait deadline is 20 seconds; this is not a wait for the new save to finish.
4. Copy persistence metadata and subscribed regions into the buffer. Each region is locked, copied and unlocked separately, with callbacks before and after its copy.
5. Publish the buffer information, mark it ready, start a detached pthread, and return success.

A writer that uses the region lock cannot change the region while it is being copied. The save function unlocks each region before locking the next, so other regions can change between copies. It has not been checked whether every setter also acquires the outer persistence lock.

The detached serializer starts at `0x1d10c`. It builds the protobuf record and writes each destination separately. Its results are not returned to the original save caller.

### Shared buffer and locks

The buffer's control data is stored in the POSIX shared-memory object `/BufferedMapInfo`, mapped read/write with `MAP_SHARED`. This firmware allocates one task entry. A named semaphore controls access to it.

The root and task mutexes are initialized as process-shared and robust. The persistence metadata lock is also process-shared: persistence records are stored in shared region 7 and selected by persistence type. These locks coordinate processes using the library; they do not prevent shell copies or replacements. Error paths around robust locks also prevent treating their presence as an unconditional synchronization guarantee.

The task uses these state values:

| State | Observed use |
| --- | --- |
| 0 | Idle |
| 1 | Preparing/copying buffer |
| 2 | Buffer ready for serializer |
| 3 | Serializing/compressing |
| 4 | Writing/replacing destination files |
| 5 | Canceled |
| 6 | Meaning unresolved; cancellation skips it |

The task also records the saving process's PID, a bitmask of destination flags, region IDs/offsets/lengths, and buffer mapping information. Another process can open the shared buffer and load its contents.

**Code references:** root creation at `0x1a990`; mutex initialization at `0x1a8c6`; persistence metadata initialization at `0x179bc`; per-region copying at `0x1c102`; thread creation/detachment at `0x1c294`/`0x1c2d0`.

## Encoding

The serializer writes each region's ID, `compress`, `encrypt`, and raw size into the protobuf. It compresses the bytes when `compress` is true. It records `encrypt` but does not encrypt the bytes. The load function also checks `compress` without checking `encrypt`.

All available map-region values are single zlib streams, even though both flags are true. Inflating them directly produces the declared `rawDataSize`.

For larger payloads, the background serializer can split compression work between workers. The split calculation considers region size and CPU count, and rounds part sizes to multiples of eight. Compressed parts are stored in the repeated `value` field. Loading inflates each `value` independently into an offset calculated from the prefix sum of `rawDataPartSize`; it does not concatenate compressed streams. Workers are joined before the post-load callback. Count, total-size and inflation errors can leave the parse-success result true. The historical capture has no multipart example; these findings come from the loader instructions.

The cancellable compressor checks task status between deflate calls. Cancellation can therefore stop compression, but calling the cancellation function does not wait for that stop.

**Code references:** background encoding branches at `0x1d412–0x1d420`; cancellable compressor at `0x1a530`; ordinary compressor at `0x17664`; synchronous serializer flag assignment at `0x18812`; load branch at `0x1969c`.

## Destination-file writes

For each destination still enabled in the task mask, the background worker does the following:

```text
path = GetMapInfoPersistFileName(flag)
tmp  = path + ".tmp" + decimal(task_index)

open tmp as binary output
serialize protobuf to tmp
close tmp

lock buffer root
if flag is still in destination mask:
    rename tmp to path
else:
    unlink tmp
unlock buffer root
```

The suffix is the task index loaded at `0x1dc76` and passed to the formatter at `0x1dc84`. The owner PID is a separate field. With the one initialized task, the suffix is `.tmp0`.

The mask check and rename occur under the same root mutex used by cancellation. A cancellation that removes the bit before this check prevents the rename. A cancellation after rename does not restore the previous file.

The worker replaces each file separately and releases the root lock between files. It does not update a manifest or otherwise commit the set together. The code examined does not call `fsync`, `fdatasync`, or sync the containing directory.

The worker ignores `SerializeToOstream`'s boolean result. If opening or closing the stream fails, it sets the stream's failure state but can still proceed to the rename. If the rename fails, it logs the error. None of these errors are returned to the original caller. The worker frees its buffer and marks the task idle even if some files were not replaced.

Consequently, neither successful save return nor an idle task is a reliable indication that the files were written successfully. Renaming the temporary file also provides no explicit power-loss durability guarantee in this implementation.

**Code references:** temporary-name construction at `0x1dc4c–0x1dc84`; open/serialize/close at `0x1ddaa–0x1ddcc`; mask check/rename at `0x1ddf2–0x1de00`; canceled-file removal at `0x1defa`; failure branches at `0x1df14`, `0x1df46`, `0x1df5a`.

## Cancellation

`CancelSavingTasksForMaps(mask)`, at `0x1b564`, locks the root and removes matching destination bits from active work. It skips task states 0 and 6. If no destination bits remain, it sets state 5.

The function returns after updating the task. It does not wait for the serializer to finish, flush files, or undo earlier renames. If only some destinations are canceled, the worker can still write the others.

## Loads can use the buffer

`PersistLoadMapInfo(flag)`, at `0x1c620`, acquires the type-0 persistence lock and the buffer-root lock. It reads the destination file when there is no applicable buffered task, including idle/canceled state or a destination-mask mismatch.

If a matching save has buffered data, the load can use that buffer instead. Within the saving process, it uses the recorded pointer. In another process, it opens the corresponding shared-memory object read-only. It locks each region before restoring it and runs callbacks before and after copying. A matching task in state 1 does not fall back to disk: it resets the task and returns false, or may abort for model-version 2. Other matching states, including unresolved value 6, enter the buffer path. Missing subscribed region IDs can be skipped, so success need not mean every current region was restored.

A successful load can therefore return data newer than the destination file. Replacing the file and requesting a load does not by itself force the firmware to use the replacement.

### Filename overloads

The `char const*` argument in these overloads does not select an arbitrary file:

```text
PersistSaveMapInfo(char const*, flag)
PersistLoadMapInfo(char const*, flag)
```

The save overload logs the string, constructs a single-element flag vector and calls the vector implementation. The load overload logs the string and calls the flag implementation. The flag determines the actual filename or matching buffer. These overloads are not arbitrary-path import/export functions.

**Code references:** save overload at `0x1c578`; load overload at `0x1d0b8`, forwarding at `0x1d0f0`.

### Load-and-save behavior

`PersistLoadMapInfoAndSave`, at `0x1cbf0`, first loads the source flag. It then cancels pending work for its destination flags and copies the source **file** into destination files through streams. This copy uses direct binary output, not the background temporary-file/rename implementation.

If the initial load used buffered data, that data need not match the source file subsequently copied. The file-copy errors also do not replace the successful-load return value. This function is therefore neither a buffer flush nor a transaction across destination files.

## Generic persistence saves

`PersistSave(type, filename)`, at `0x185c0`, delegates type 0 to asynchronous map saving after parsing the map flag from the filename. Only nonzero types wait for compression workers and write synchronously to the selected destination. That direct-write path has no temporary-file/rename step or sync call and can return true after stream or serialization failure. Catalog persistence uses type 1.

`PersistLoad`, at `0x19ba4`, similarly delegates type 0 to buffer-aware map loading; nonzero types use the file-only loader.

The file loader's exactly-one-value, uncompressed branch copies the value count (one byte), not the declared raw size. The compressed historical map records do not exercise that branch. Do not toggle encoding flags or infer malformed-input safety from a successful parse result.

## Backup and restore implications

If files are copied immediately after the save API returns, they may be older than the buffer used by a native load. Waiting for the serializer avoids copying while that worker is writing, but other processes can still change the regions, grid, catalog or database.

No transaction covering all these files was found in the examined code. Caller-specific replies must not be treated as set-wide durability acknowledgments without tracing their actual completion conditions. Task-capacity repair and cancellation are not flush or safe-shutdown protocols.

Replacing files while buffers and grid caches remain active can cause a later load or save to use old state. The [maintenance procedure](../../guides/stopped-backup.md) avoids those live races by stopping the hosts and rebooting after restoring supervision. The [file contract](matching-set.md) defines which companions belong together; a stopped copy preserves disk state but does not repair a previously interrupted save.
