/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT maxim_max44009

#include <device.h>
#include <drivers/i2c.h>
#include <drivers/sensor.h>
#include <sys/__assert.h>
#include <logging/log.h>

#include "veml6030.h"

LOG_MODULE_REGISTER(VEML6030, CONFIG_SENSOR_LOG_LEVEL);

static int veml6030_reg_read(struct veml6030_data *drv_data, uint8_t reg,

			     uint8_t *val, bool send_stop)
{
	struct i2c_msg msgs[2] = {
		{
			.buf = &reg,
			.len = 1,
			.flags = I2C_MSG_WRITE,
		},
		{
			.buf = val,
			.len = 1,
			.flags = I2C_MSG_READ,
		},
	};

	if (send_stop) {
		msgs[1].flags |= I2C_MSG_STOP;
	}

	if (i2c_transfer(drv_data->i2c, msgs, 2, VEML6030_I2C_ADDRESS) != 0) {
		return -EIO;
	}

	return 0;
}

static int veml6030_reg_write(struct veml6030_data *drv_data, uint8_t reg,
			      uint8_t val)
{
	uint8_t tx_buf[2] = {reg, val};

	return i2c_write(drv_data->i2c, tx_buf, sizeof(tx_buf),
			 VEML6030_I2C_ADDRESS);
}

static int veml6030_reg_update(struct veml6030_data *drv_data, uint8_t reg,
			       uint8_t mask, uint8_t val)
{
	uint8_t old_val = 0U;
	uint8_t new_val = 0U;

	if (veml6030_reg_read(drv_data, reg, &old_val, true) != 0) {
		return -EIO;
	}

	new_val = old_val & ~mask;
	new_val |= val & mask;

	return veml6030_reg_write(drv_data, reg, new_val);
}

static int veml6030_attr_set(const struct device *dev,
			     enum sensor_channel chan,
			     enum sensor_attribute attr,
			     const struct sensor_value *val)
{
	struct veml6030_data *drv_data = dev->data;
	uint8_t value;
	uint32_t cr;

	if (chan != SENSOR_CHAN_LIGHT) {
		return -ENOTSUP;
	}

	switch (attr) {
	case SENSOR_ATTR_SAMPLING_FREQUENCY:
		/* convert rate to mHz */
		cr = val->val1 * 1000 + val->val2 / 1000;

		/* the sensor supports 1.25Hz or continuous conversion */
		switch (cr) {
		case 1250:
			value = 0U;
			break;
		default:
			value = VEML6030_CONTINUOUS_SAMPLING;
		}

		if (veml6030_reg_update(drv_data, VEML6030_REG_CONFIG,
					VEML6030_SAMPLING_CONTROL_BIT,
					value) != 0) {
			LOG_DBG("Failed to set attribute!");
			return -EIO;
		}

		return 0;

	default:
		return -ENOTSUP;
	}

	return 0;
}

static int veml6030_sample_fetch(const struct device *dev,
				 enum sensor_channel chan)
{
	struct veml6030_data *drv_data = dev->data;
	uint8_t val_h, val_l;

	__ASSERT_NO_MSG(chan == SENSOR_CHAN_ALL || chan == SENSOR_CHAN_LIGHT);

	drv_data->sample = 0U;

	if (veml6030_reg_read(drv_data, VEML6030_REG_LUX_HIGH_BYTE, &val_h,
			      false) != 0) {
		return -EIO;
	}

	if (veml6030_reg_read(drv_data, VEML6030_REG_LUX_LOW_BYTE, &val_l,
			      true) != 0) {
		return -EIO;
	}

	drv_data->sample = ((uint16_t)val_h) << 8;
	drv_data->sample += val_l;

	return 0;
}

static int veml6030_channel_get(const struct device *dev,
				enum sensor_channel chan,
				struct sensor_value *val)
{
	struct veml6030_data *drv_data = dev->data;
	uint32_t uval;

	if (chan != SENSOR_CHAN_LIGHT) {
		return -ENOTSUP;
	}

	/**
	 * sample consists of 4 bits of exponent and 8 bits of mantissa
	 * bits 15 to 12 are exponent bits
	 * bits 11 to 8 and 3 to 0 are the mantissa bits
	 */
	uval = drv_data->sample;
	uval = (uval & VEML6030_MANTISSA_LOW_NIBBLE_MASK) +
	       ((uval & VEML6030_MANTISSA_HIGH_NIBBLE_MASK) >> 4);
	uval = uval << (drv_data->sample >> VEML6030_SAMPLE_EXPONENT_SHIFT);

	/* lux is the integer of sample output multiplied by 0.045. */
	val->val1 = (uval * 45U) / 1000;
	val->val2 = ((uval * 45U) % 1000) * 1000U;

	return 0;
}

static const struct sensor_driver_api veml6030_driver_api = {
	.attr_set = veml6030_attr_set,
	.sample_fetch = veml6030_sample_fetch,
	.channel_get = veml6030_channel_get,
};

int veml6030_init(const struct device *dev)
{
	struct veml6030_data *drv_data = dev->data;

	drv_data->i2c = device_get_binding(DT_INST_BUS_LABEL(0));
	if (drv_data->i2c == NULL) {
		LOG_DBG("Failed to get pointer to %s device!",
			    DT_INST_BUS_LABEL(0));
		return -EINVAL;
	}

	return 0;
}

static struct veml6030_data veml6030_drv_data;

DEVICE_DT_INST_DEFINE(0, veml6030_init, device_pm_control_nop,
	    &veml6030_drv_data, NULL, POST_KERNEL,
	    CONFIG_SENSOR_INIT_PRIORITY, &veml6030_driver_api);
