
#include <zephyr.h>
#include <logging/log.h>
#include <drivers/i2c.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

#define SLEEP_TIME_MS   1000

void main(void)
{
	LOG_INF("Hello from Sensor Tag");

	const struct device *i2c_dev;
	i2c_dev = device_get_binding("I2C_0");
	if (!i2c_dev) {
		LOG_INF("I2C: Device driver not found.\n");
		return;
	}

	uint8_t data[16];
	int ret;
	uint16_t addr = 0x48;
	ret = i2c_read(i2c_dev, &data[0], 1, addr);
	if (ret) {
		LOG_INF("I2C: read failed %X.", addr);
	} else {
		LOG_INF("I2C: success %X.", addr);
	}

	addr = 0x40;
	ret = i2c_read(i2c_dev, &data[0], 1, addr);
	if (ret) {
		LOG_INF("I2C: read failed %X.", addr);
	} else {
		LOG_INF("I2C: success %X.", addr);
	}

	addr = 0x76;
	ret = i2c_read(i2c_dev, &data[0], 1, addr);
	if (ret) {
		LOG_INF("I2C: read failed %X.", addr);
	} else {
		LOG_INF("I2C: success %X.", addr);
	}


}
