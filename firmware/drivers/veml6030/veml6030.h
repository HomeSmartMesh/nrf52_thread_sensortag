/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_DRIVERS_SENSOR_VEML6030_VEML6030_H_
#define ZEPHYR_DRIVERS_SENSOR_VEML6030_VEML6030_H_

#include <sys/util.h>

#define VEML6030_I2C_ADDRESS	DT_INST_REG_ADDR(0)

#define VEML6030_ALS_CONF_ALS_SD		BIT(0)
#define VEML6030_ALS_CONF_ALS_INT_EN	BIT(1)
#define VEML6030_ALS_CONF_ALS_PRES_MASK	0x30

#define VEML6030_REG_ALS_CONF		0x00
#define VEML6030_REG_ALS_WH			0x03
#define VEML6030_REG_ALS_WL			0x04
#define VEML6030_REG_POWER_SAVING	0x04
#define VEML6030_REG_ALS			0x04
#define VEML6030_REG_WHITE			0x04
#define VEML6030_REG_ALS_INT		0x04

struct veml6030_data {
	const struct device *i2c;
	uint16_t sample;
};

#endif /* _SENSOR_VEML6030_ */
