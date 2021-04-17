
#include <zephyr.h>
#include <logging/log.h>
#include <drivers/sensor.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

void main(void)
{
	LOG_INF("Hello from Sensor Tag I2C example");

	const struct device *dev;
	struct sensor_value val;
	uint32_t lum = 0U;

	LOG_INF("VEML6030 light sensor application\n");

	dev = device_get_binding("VEML6030");
	if (!dev) {
		LOG_ERR("sensor: device not found.\n");
		return;
	}

	while (1) {
		if (sensor_sample_fetch_chan(dev, SENSOR_CHAN_LIGHT) != 0) {
			LOG_ERR("sensor: sample fetch fail.\n");
			return;
		}

		if (sensor_channel_get(dev, SENSOR_CHAN_LIGHT, &val) != 0) {
			LOG_ERR("sensor: channel get fail.\n");
			return;
		}

		lum = val.val1;
		LOG_INF("sensor: lum reading: %d\n", lum);

		k_sleep(K_MSEC(4000));
	}
}
