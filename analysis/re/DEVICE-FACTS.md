# Device observations for offline map maintenance

Read-only SSH inspection on October 21, 2026 confirms that the running robot uses Linux `3.4.39` on ARMv7 and firmware identifier `A.01.0057-V1612`. The map hosts and data paths match the saved configuration so far. This does not establish that stopping the loader or taking over its UART is safe; both remain outside this inspection.

The connection to `root@valetudo-illegalplainape.local` succeeded with `BatchMode=yes`, `ConnectTimeout=10` and `StrictHostKeyChecking=yes`. No services have been stopped, no device nodes have been opened and no robot commands have been sent. Inspection is still in progress.

## Running configuration

The loader is PID 448, running `/opt/rockrobo/cleaner/bin/rr_loader`. Its mapped libraries include chassis, navigation, SLAM, persistence, IPC and `libuart_api.so.4.0.2`. It also maps `/dev/uart_mcu`; these mappings were observed through `/proc`, not by opening the device. `RoboController` is PID 507 with process name `robo_main`, and `AppProxy` is PID 509 with process name `app_main`. Their changed process names explain why a search limited to `/proc/PID/comm` would miss them.

WatchDoge is PID 372, Valetudo is PID 371 and `miio_client` is PID 513. Their observed environment, and that of both controller hosts and the loader, agrees on `RR_ROOT=/opt/rockrobo`, `RR_UDATA=/mnt/data` and `NAV_DYNAMIC_CONFIG_PATH=/mnt/data/rockrobo`. Only those three environment variables were inspected.

`/mnt/data` is an ext4 mount. `/run` and `/run/shm` are tmpfs, and `/dev/shm` is a symlink to `/run/shm`. This matches the layout assumed by the [matching-set procedure](MAP-FILE-CONTRACT.md). The initial observation found 56,410 KiB free on `/mnt/data`; later staging must still account for the complete snapshot, replacement and quarantine together.
