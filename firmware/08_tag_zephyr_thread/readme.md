# sensor tag hello

## environment variables
* `GNUARMEMB_TOOLCHAIN_PATH` = D:\tools\gnu_arm_embedded\9_2020-q2-update
* `ZEPHYR_BASE` = D:\Projects\zephyrproject\zephyr
* `ZEPHYR_TOOLCHAIN_VARIANT` = gnuarmemb

## usage
```bash
west build -b nrf52840_sensortag
west flash
```

* this example has the shell configured running on RTT and not the log

config
```bash
-- west build: generating a build system
Including boilerplate (Zephyr base (cached)): D:/Projects/zephyrproject/zephyr/cmake/app/boilerplate.cmake
-- Application: D:/Dev/nrf52/nrf52_thread_sensortag/firmware/08_tag_zephyr_thread
-- Zephyr version: 2.5.99 (D:/Projects/zephyrproject/zephyr)
-- Found west (found suitable version "0.9.0", minimum required is "0.7.1")
-- Board: nrf52840_sensortag
-- Cache files will be written to: D:/Projects/zephyrproject/zephyr/.cache
-- Found toolchain: gnuarmemb (D:/tools/gnu_arm_embedded/9_2020-q2-update)
-- Found BOARD.dts: D:/Dev/nrf52/nrf52_thread_sensortag/firmware/boards/arm/nrf52840_sensortag/nrf52840_sensortag.dts
```

shell log
```log
*** Booting Zephyr OS build zephyr-v2.5.0-159-g2bfaadffb807  ***

rtt:~$ kernel
kernel - Kernel commands
Subcommands:
  cycles   :Kernel cycles.
  stacks   :List threads stack usage.
  threads  :List kernel threads.
  uptime   :Kernel uptime.
  version  :Kernel version.
rtt:~$ ot
ot: command not found
rtt:~$ 
```
