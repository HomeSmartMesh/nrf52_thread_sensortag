
MQTT-SN Documentation https://www.homesmartmesh.com/docs/networks/thread/#mqtt-sn

This example is a portof the [nRFSDK for Thread and Zigbee v4.1.0](https://www.nordicsemi.com/Software-and-tools/Software/nRF5-SDK-for-Thread-and-Zigbee/Download#infotabs) [mqttsn_sleepy_publisher example](examples\thread\mqttsn_sleepy_publisher) to the nRF52840 USB dongle (PCA10059)

* Adapted Makefile
* As the usb dongle has only one user key KEY_0, the sequence of `search_gateway`, `connect`, `publish` is not cyclically executed when pressing KEY_0 multiple times.
