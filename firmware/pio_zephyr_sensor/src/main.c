/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <logging/log.h>

#include <drivers/i2c.h>

#define MAX44009_I2C_ADDR	0x4A

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   300

/* The devicetree node identifier for the "led0" alias. */
//led0_green led1_red/green/blue
#define LED0_NODE DT_ALIAS(led0)

#define LED0	DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN	DT_GPIO_PIN(LED0_NODE, gpios)
//override dts due to using nrf52840_dk instead of nrf52840dongle_nrf52840
//#define PIN	12


static int read_bytes(const struct device *i2c_dev, uint16_t addr,
		      uint8_t *data, uint32_t num_bytes)
{
	uint8_t wr_addr[2];
	struct i2c_msg msgs[2];

	/* Now try to read back from FRAM */

	/* FRAM address */
	wr_addr[0] = (addr >> 8) & 0xFF;
	wr_addr[1] = addr & 0xFF;

	/* Setup I2C messages */

	/* Send the address to read from */
	msgs[0].buf = wr_addr;
	msgs[0].len = 2U;
	msgs[0].flags = I2C_MSG_WRITE;

	/* Read from device. STOP after this. */
	msgs[1].buf = data;
	msgs[1].len = num_bytes;
	msgs[1].flags = I2C_MSG_READ | I2C_MSG_STOP;

	return i2c_transfer(i2c_dev, &msgs[0], 2, MAX44009_I2C_ADDR);
}

void main(void)
{
	const struct device *i2c_dev;

	bool led_is_on = true;
	int ret = 0;

	LOG_INF("Starting");

	struct device const *dev = device_get_binding(LED0);
	if (dev == NULL) {
		return;
	}
	LOG_INF("pin configure");

	ret = gpio_pin_configure(dev, PIN, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return;
	}
	LOG_INF("next Starting I2C");

	//i2c_dev = device_get_binding("I2C_0");
	i2c_dev = device_get_binding(DT_LABEL(DT_NODELABEL(i2c0)));
	//i2c_dev = device_get_binding(DT_LABEL(DT_ALIAS(i2c_0)));
	
	LOG_INF("i2c_dev=0x%0x",i2c_dev);
	__ASSERT(i2c_dev, "Failed to get the device");
	if (!i2c_dev) {
		printk("I2C: Device driver not found.\n");
		return;
	}
	LOG_INF("binding obtained");
	uint8_t data[10];
	ret = read_bytes(i2c_dev, 0x02, &data[0], 1);
	if (ret) {
		printk("Error reading from FRAM! error code (%d)\n", ret);
		return;
	} else {
		printk("Read 0x%X from address 0x00.\n", data);
	}


	int count = 0;
	while (1) {
		gpio_pin_set(dev, PIN, (int)led_is_on);
		led_is_on = !led_is_on;
		k_msleep(SLEEP_TIME_MS);
		LOG_INF("loop: %d",count++);
	}
}
