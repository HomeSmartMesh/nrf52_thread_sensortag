* added `boards\nrf52840dongle_nrf52840.json` but due to the dongle using a different flash layout in zephyr dts flashing the app result it being on a disconnected location where a 2nd zephyr bootloader is missing
* fallback on using board `nrf52840_dk`
* if MBR is flashed might have to erase flash before uploading
* jlink is the default upload method for the nrf52840 boards
