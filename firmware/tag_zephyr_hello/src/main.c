
#include <zephyr.h>
#include <logging/log.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

#define SLEEP_TIME_MS   1000

void main(void)
{
	bool led_is_on = true;
	int ret = 0;

	LOG_INF("Starting");

	int count = 0;
	while (1) {
		k_msleep(SLEEP_TIME_MS);
		LOG_INF("loop: %d",count++);
	}
}
