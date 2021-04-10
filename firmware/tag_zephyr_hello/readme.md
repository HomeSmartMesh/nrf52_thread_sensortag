# sensor tag hello

## environment variables
* `GNUARMEMB_TOOLCHAIN_PATH` = D:\tools\gnu_arm_embedded\9_2020-q2-update
* `ZEPHYR_BASE` = D:\Projects\zephyrproject\zephyr
* `ZEPHYR_TOOLCHAIN_VARIANT` = gnuarmemb

## usage
```bash
west build -p auto -b nrf52840dk_nrf52840
west flash
```

config
```bash
-- west build: generating a build system
Including boilerplate (Zephyr base (cached)): D:/Projects/zephyrproject/zephyr/cmake/app/boilerplate.cmake
-- Application: D:/Dev/nrf52/nrf52_thread_sensortag/firmware/tag_zephyr_hello
-- Zephyr version: 2.5.99 (D:/Projects/zephyrproject/zephyr)
-- Found west (found suitable version "0.9.0", minimum required is "0.7.1")
-- Board: nrf52840dk_nrf52840
-- Cache files will be written to: D:/Projects/zephyrproject/zephyr/.cache
-- Found toolchain: gnuarmemb (D:/tools/gnu_arm_embedded/9_2020-q2-update)
```

rtt log
```log
*** Booting Zephyr OS build zephyr-v2.5.0-159-g2bfaadffb807  ***

[00:00:00.337,707] <inf> main: Starting
[00:00:01.337,768] <inf> main: loop: 0
[00:00:02.337,860] <inf> main: loop: 1
[00:00:03.338,012] <inf> main: loop: 2
[00:00:04.338,104] <inf> main: loop: 3
[00:00:05.338,256] <inf> main: loop: 4
[00:00:06.338,348] <inf> main: loop: 5
[00:00:07.338,500] <inf> main: loop: 6
[00:00:08.338,562] <inf> main: loop: 7
[00:00:09.338,653] <inf> main: loop: 8
[00:00:10.338,745] <inf> main: loop: 9
[00:00:11.338,836] <inf> main: loop: 10
[00:00:12.338,928] <inf> main: loop: 11
[00:00:13.339,019] <inf> main: loop: 12
[00:00:14.339,111] <inf> main: loop: 13
[00:00:15.339,202] <inf> main: loop: 14
[00:00:16.339,294] <inf> main: loop: 15
[00:00:17.339,385] <inf> main: loop: 16
[00:00:18.339,477] <inf> main: loop: 17
```
