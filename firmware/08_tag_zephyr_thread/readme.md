# tag zephyr thread
## Thread network configuration
* menuconfig only runs on linux or wsl with the command `west build -t menuconfig`
* the generated config is under `build/zephyr/.config`
* Note that once the openthread config is persisted in non-volatile memory, changing the config would have no effect as the stored config has precedence over code
* the persisted config can be deleted with `ot factory reset`

```conf
#
# Thread Network configuration
#
CONFIG_OPENTHREAD_PANID=43981
CONFIG_OPENTHREAD_CHANNEL=13
CONFIG_OPENTHREAD_NETWORK_NAME="ot_zephyr"
CONFIG_OPENTHREAD_XPANID="de:ad:00:be:ef:00:ca:fe"
CONFIG_OPENTHREAD_MASTERKEY=""
CONFIG_OPENTHREAD_FTD=y
# CONFIG_OPENTHREAD_MTD is not set
CONFIG_OPENTHREAD_MAX_CHILDREN=32
CONFIG_OPENTHREAD_MAX_IP_ADDR_PER_CHILD=6
CONFIG_OPENTHREAD_CONFIG_PLATFORM_INFO="Zephyr"
CONFIG_OPENTHREAD_RADIO_LINK_IEEE_802_15_4_ENABLE=y
# CONFIG_OPENTHREAD_RADIO_LINK_TREL_ENABLE is not set
CONFIG_OPENTHREAD_CSL_SAMPLE_WINDOW=30
CONFIG_OPENTHREAD_CSL_RECEIVE_TIME_AHEAD=3
# CONFIG_OPENTHREAD_SRP_CLIENT is not set
# CONFIG_OPENTHREAD_SRP_SERVER is not set
# end of Thread Network configuration
```

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
ot state
leader

Done

rtt:~$ ot ipaddr
fdde:ad00:beef:0:0:ff:fe00:fc00

fdde:ad00:beef:0:0:ff:fe00:1800

fdde:ad00:beef:0:e004:6a1d:8704:d57f

fe80:0:0:0:38a9:1cd0:752:f538

Done
```
