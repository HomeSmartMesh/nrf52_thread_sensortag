# sensor tag hello

## environment variables
* `GNUARMEMB_TOOLCHAIN_PATH` = D:\tools\gnu_arm_embedded\9_2020-q2-update
* `ZEPHYR_BASE` = D:\Projects\zp\zephyrproject\zephyr
* `ZEPHYR_TOOLCHAIN_VARIANT` = gnuarmemb

## Zephyr version
* Note that up to Zephyr version `zephyr-v2.5.0-159-g2bfaadffb807` the compilation throws an error 
## usage
```bash
west build -b nrf52840_sensortag
west flash
```

* this example has the shell configured running on RTT and not the log

config
```bash
-- west build: generating a build system
Including boilerplate (Zephyr base): D:/Projects/zp/zephyrproject/zephyr/cmake/app/boilerplate.cmake
-- Application: D:/Dev/nrf52/nrf52_thread_sensortag/firmware/08_tag_zephyr_thread
-- Zephyr version: 2.5.99 (D:/Projects/zp/zephyrproject/zephyr)
-- Found Python3: C:/Users/User/AppData/Local/Programs/Python/Python39/python.exe (found suitable exact version "3.9.0") found components: Interpreter
-- Found west (found suitable version "0.10.1", minimum required is "0.7.1")
-- Board: nrf52840_sensortag
-- Cache files will be written to: D:/Projects/zp/zephyrproject/zephyr/.cache
-- Found toolchain: gnuarmemb (D:/tools/gnu_arm_embedded/10 2020-q4-major)
-- Found BOARD.dts: D:/Dev/nrf52/nrf52_thread_sensortag/firmware/boards/arm/nrf52840_sensortag/nrf52840_sensortag.dts
```

shell log
```log
rtt:~$ *** Booting Zephyr OS build zephyr-v2.5.0-2187-g757cd12e6602  ***
kernel
kernel - Kernel commands
Subcommands:
  cycles   :Kernel cycles.
  reboot   :Reboot.
  stacks   :List threads stack usage.
  threads  :List kernel threads.
  uptime   :Kernel uptime.
  version  :Kernel version.
rtt:~$ ot state
leader

Done

rtt:~$ 
```
