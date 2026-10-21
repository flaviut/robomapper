# One short service-maintenance session

This session is being prepared, not run. Services must remain up until the parent has read the exact operations and recovery scripts and explicitly approved the next step. Preparation may create private staging files only; it must not execute the helper, open UART, arm recovery, send exclusions, stop a service, reboot, or alter active configuration.

The only proposed map operation is an untouched stopped backup of the finite namespace in [the file contract](MAP-FILE-CONTRACT.md). No map replacement, restore, SQL change, firmware work, motion, docking, authentication or network change belongs to this session. [The native helper](MAINTENANCE-HELPER.md) and [A14 heartbeat findings](A14-HEARTBEAT.md) explain why loader exit and an acknowledged `-1` request must precede that backup. An acknowledgment is not semantic sentinel readback.

Preparation started on October 21, 2026, at 04:55 UTC, from repository commit `58823a4`. The supplied helper's SHA256 is `4ace18a953eff862a6c3815179a6e35ec3e1bf5e4d5e86cd19f39eb2944d51a0`; its local MD5 is `96ca12ccedba100b8905cd69137b4702`. Neither was obtained by executing the binary. Current observations, private paths and the proposed bounded recovery sequence will be recorded below before approval is requested.
