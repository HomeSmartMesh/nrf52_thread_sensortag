# tag zephyr thread

## usage
```bash
west build -b nrf52840_sensortag -- -DCONF_FILE=prj-shell.conf
west build -b nrf52840_sensortag -- -DCONF_FILE=prj-log.conf
west flash
```

## Thread network configuration
* menuconfig only runs on linux or wsl with the command `west build -t menuconfig`
* the generated config is under `build/zephyr/.config`
* Note that once the openthread config is persisted in non-volatile memory, changing the config would have no effect as the stored config has precedence over code
* the persisted config can be deleted with `ot factory reset`

## environment variables
* `GNUARMEMB_TOOLCHAIN_PATH` = D:\tools\gnu_arm_embedded\9_2020-q2-update
* `ZEPHYR_BASE` = D:\Projects\zp\zephyrproject\zephyr
* `ZEPHYR_TOOLCHAIN_VARIANT` = gnuarmemb

## Zephyr version
* Note that up to Zephyr version `zephyr-v2.5.0-159-g2bfaadffb807` the compilation throws an error 

* this example has the shell configured running on RTT and not the log

