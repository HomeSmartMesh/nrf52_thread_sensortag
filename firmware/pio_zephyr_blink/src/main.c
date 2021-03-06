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

void main(void)
{
	bool led_is_on = true;
	int ret = 0;

	LOG_INF("Starting");

	struct device const *dev = device_get_binding(LED0);
	if (dev == NULL) {
		return;
	}

	ret = gpio_pin_configure(dev, PIN, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return;
	}

	int count = 0;
	while (1) {
		gpio_pin_set(dev, PIN, (int)led_is_on);
		led_is_on = !led_is_on;
		k_msleep(SLEEP_TIME_MS);
		LOG_INF("loop: %d",count++);
	}
}
