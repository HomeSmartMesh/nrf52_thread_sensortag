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

#include <drivers/sensor.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   300

/* The devicetree node identifier for the "led0" alias. */
//led0_green led1_red/green/blue
#define LED0_NODE DT_ALIAS(led0)

#define LED0	DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN	DT_GPIO_PIN(LED0_NODE, gpios)

extern int max44009_init(const struct device *dev);

void test_sensor(){
	const struct device *dev;
	struct sensor_value val;
	uint32_t lum = 0U;

	printk("MAX44009 light sensor application\n");

	dev = device_get_binding("MAX44009");
	if (!dev) {
		printk("sensor: device not found.\n");
		return;
	}

	max44009_init(dev);

	while (1) {
		if (sensor_sample_fetch_chan(dev, SENSOR_CHAN_LIGHT) != 0) {
			printk("sensor: sample fetch fail.\n");
			return;
		}

		if (sensor_channel_get(dev, SENSOR_CHAN_LIGHT, &val) != 0) {
			printk("sensor: channel get fail.\n");
			return;
		}

		lum = val.val1;
		printk("sensor: lum reading: %d\n", lum);

		k_sleep(K_MSEC(4000));
	}	
}

void main(void)
{

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
	LOG_INF("testing sensor");

	test_sensor();

	int count = 0;
	while (1) {
		gpio_pin_set(dev, PIN, (int)led_is_on);
		led_is_on = !led_is_on;
		k_msleep(SLEEP_TIME_MS);
		LOG_INF("loop: %d",count++);
	}
}
