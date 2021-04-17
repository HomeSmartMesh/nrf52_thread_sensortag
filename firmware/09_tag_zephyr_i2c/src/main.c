
#include <zephyr.h>
#include <logging/log.h>
#include <drivers/i2c.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

void main(void)
{
	LOG_INF("Hello from Sensor Tag I2C example");

	const struct device *i2c_dev;
	int ret;

	i2c_dev = device_get_binding("I2C_0");
	if (!i2c_dev) {
		LOG_INF("I2C: Device driver not found.\n");
		return;
	}

	uint8_t data[16];
	uint16_t addr = 0x48;
	ret = i2c_reg_read_byte(i2c_dev, addr, 0, &data[0]);
	if (ret) {
		LOG_ERR("I2C: i2c_reg_read_byte() @%X failed %X.",addr, ret);
	} else {
		LOG_INF("VEML6030 @%X reg[0] 'ALS_CONF' = %d",addr,data[0]);
	}

	addr = 0x40;
	ret = i2c_reg_read_byte(i2c_dev, addr, 0xE7, &data[0]);
	if (ret) {
		LOG_ERR("I2C: i2c_reg_read_byte() @%X failed %X.",addr, ret);
	} else {
		LOG_INF("MS8607 @%X 'Relative Humidity RH' reg[0xE7] 'user register' = %d",addr,data[0]);
	}

	addr = 0x76;
	ret = i2c_reg_read_byte(i2c_dev, addr, 0, &data[0]);
	if (ret) {
		LOG_ERR("I2C: i2c_reg_read_byte() @%X failed %X.",addr, ret);
	} else {
		LOG_INF("MS8607 @%X 'Pressure and Temperature' reg[0] 'ADC Read' => %d",addr,data[0]);
	}
}
