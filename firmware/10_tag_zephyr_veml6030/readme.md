# sensor tag hello

## environment variables
* `GNUARMEMB_TOOLCHAIN_PATH` = D:\tools\gnu_arm_embedded\9_2020-q2-update
* `ZEPHYR_BASE` = D:\Projects\zephyrproject\zephyr
* `ZEPHYR_TOOLCHAIN_VARIANT` = gnuarmemb

## usage
```bash
west build -b nrf52840_sensortag -- -DCONF_FILE=prj-shell.conf
west build -b nrf52840_sensortag -- -DCONF_FILE=prj-log.conf
west flash
```

error
```log
[00:00:00.325,012] <inf> main: Hello from Sensor Tag I2C example
[00:00:00.325,012] <inf> main: VEML6030 light sensor application

[00:00:00.325,042] <err> main: sensor: device not found.
```


https://docs.zephyrproject.org/latest/guides/porting/board_porting.html

https://stackoverflow.com/questions/62358554/zephyros-how-to-add-driver-module-to-out-of-tree-project

https://www.zephyrproject.org/how-to-build-drivers-for-zephyr-rtos/

https://interrupt.memfault.com/blog/building-drivers-on-zephyr

https://docs.zephyrproject.org/latest/reference/drivers/index.html
https://docs.zephyrproject.org/1.9.0/devices/drivers/drivers.html
https://docs.zephyrproject.org/latest/reference/peripherals/sensor.html


https://www.mouser.com/datasheet/2/427/veml6030-1767367.pdf
https://www.mouser.com/datasheet/2/418/5/NG_DS_MS8607-02BA01_B3-1134999.pdf
