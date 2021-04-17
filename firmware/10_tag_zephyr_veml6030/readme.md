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


https://stackoverflow.com/questions/62358554/zephyros-how-to-add-driver-module-to-out-of-tree-project

https://www.zephyrproject.org/how-to-build-drivers-for-zephyr-rtos/

https://interrupt.memfault.com/blog/building-drivers-on-zephyr

https://docs.zephyrproject.org/latest/reference/drivers/index.html
https://docs.zephyrproject.org/1.9.0/devices/drivers/drivers.html
https://docs.zephyrproject.org/latest/reference/peripherals/sensor.html