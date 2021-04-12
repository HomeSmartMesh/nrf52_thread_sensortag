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

config
```bash
-- west build: generating a build system
Including boilerplate (Zephyr base): D:/Projects/zephyrproject/zephyr/cmake/app/boilerplate.cmake
-- Application: D:/Dev/nrf52/nrf52_thread_sensortag/firmware/07_tag_zephyr_button
-- Zephyr version: 2.5.99 (D:/Projects/zephyrproject/zephyr)
-- Found Python3: C:/Users/User/AppData/Local/Programs/Python/Python39/python.exe (found suitable exact version "3.9.0") found components: Interpreter
-- Found west (found suitable version "0.9.0", minimum required is "0.7.1")
-- Board: nrf52840_sensortag
-- Cache files will be written to: D:/Projects/zephyrproject/zephyr/.cache
-- Found toolchain: gnuarmemb (D:/tools/gnu_arm_embedded/9_2020-q2-update)
-- Found BOARD.dts: D:/Dev/nrf52/nrf52_thread_sensortag/firmware/boards/arm/nrf52840_sensortag/nrf52840_sensortag.dts
```

rtt log
```log
00> *** Booting Zephyr OS build zephyr-v2.5.0-159-g2bfaadffb807  ***
00> 
00> [00:00:00.334,259] <inf> main: Hello from Sensor Tag Button example
00> [00:00:00.334,289] <inf> main: Set up button at GPIO_1 pin 9
00> 
00> [00:00:01.334,350] <inf> main: loop: 0
00> [00:00:02.334,442] <inf> main: loop: 1
00> [00:00:03.334,533] <inf> main: loop: 2
00> [00:00:04.334,625] <inf> main: loop: 3
00> [00:00:05.334,716] <inf> main: loop: 4
00> [00:00:06.334,808] <inf> main: loop: 5
00> [00:00:07.334,899] <inf> main: loop: 6
00> [00:00:08.334,991] <inf> main: loop: 7
00> [00:00:09.335,083] <inf> main: loop: 8
00> [00:00:10.335,174] <inf> main: loop: 9
00> [00:00:11.335,266] <inf> main: loop: 10
00> [00:00:12.335,357] <inf> main: loop: 11
00> [00:00:13.335,449] <inf> main: loop: 12
00> [00:00:14.335,540] <inf> main: loop: 13
00> [00:00:15.335,632] <inf> main: loop: 14
00> [00:00:16.335,723] <inf> main: loop: 15
00> [00:00:17.335,815] <inf> main: loop: 16
00> [00:00:18.335,906] <inf> main: loop: 17
00> [00:00:19.335,998] <inf> main: loop: 18
00> [00:00:20.336,090] <inf> main: loop: 19
00> [00:00:21.336,181] <inf> main: loop: 20
00> [00:00:22.336,273] <inf> main: loop: 21
00> [00:00:23.336,364] <inf> main: loop: 22
00> [00:00:24.336,456] <inf> main: loop: 23
00> [00:00:25.336,547] <inf> main: loop: 24
00> [00:00:26.336,639] <inf> main: loop: 25
00> [00:00:27.336,730] <inf> main: loop: 26
00> [00:00:28.336,822] <inf> main: loop: 27
00> [00:00:29.336,914] <inf> main: loop: 28
00> [00:00:30.337,005] <inf> main: loop: 29
00> [00:00:31.337,097] <inf> main: loop: 30
00> [00:00:32.337,188] <inf> main: loop: 31
00> [00:00:32.920,257] <inf> main: Button pressed at 1078731
00> 
00> [00:00:33.282,348] <inf> main: Button pressed at 1090596
00> 
00> [00:00:33.337,249] <inf> main: loop: 32
00> [00:00:34.337,310] <inf> main: loop: 33
00> [00:00:35.337,402] <inf> main: loop: 34
00> [00:00:36.337,493] <inf> main: loop: 35
00> [00:00:37.337,585] <inf> main: loop: 36
00> [00:00:38.337,677] <inf> main: loop: 37
00> [00:00:39.337,768] <inf> main: loop: 38
00> [00:00:40.337,860] <inf> main: loop: 39
00> [00:00:41.337,951] <inf> main: loop: 40
00> [00:00:42.338,043] <inf> main: loop: 41
00> [00:00:43.338,134] <inf> main: loop: 42
00> [00:00:44.338,226] <inf> main: loop: 43
00> [00:00:45.338,317] <inf> main: loop: 44
00> *** Booting Zephyr OS build zephyr-v2.5.0-159-g2bfaadffb807  ***
00> 
00> [00:00:00.250,396] <inf> main: Hello from Sensor Tag Button example
00> [00:00:00.250,396] <inf> main: Set up button at GPIO_1 pin 9
00> 
00> [00:00:01.250,457] <inf> main: loop: 0
00> [00:00:02.250,549] <inf> main: loop: 1
00> [00:00:03.250,640] <inf> main: loop: 2
00> [00:00:04.250,732] <inf> main: loop: 3
00> [00:00:05.250,823] <inf> main: loop: 4
00> [00:00:05.709,991] <inf> main: Button pressed at 187105
00> 
00> [00:00:06.250,915] <inf> main: loop: 5
00> [00:00:07.250,976] <inf> main: loop: 6
00> [00:00:08.251,068] <inf> main: loop: 7
00> [00:00:09.251,159] <inf> main: loop: 8
00> [00:00:10.251,251] <inf> main: loop: 9
00> [00:00:11.251,342] <inf> main: loop: 10
00> [00:00:12.251,434] <inf> main: loop: 11
00> [00:00:13.251,525] <inf> main: loop: 12
00> [00:00:14.251,617] <inf> main: loop: 13
00> [00:00:15.251,708] <inf> main: loop: 14
00> [00:00:16.251,800] <inf> main: loop: 15
00> [00:00:17.251,892] <inf> main: loop: 16
00> [00:00:18.251,983] <inf> main: loop: 17
00> [00:00:19.252,075] <inf> main: loop: 18
00> [00:00:20.252,166] <inf> main: loop: 19
00> [00:00:21.252,258] <inf> main: loop: 20
00> [00:00:22.252,349] <inf> main: loop: 21
```
