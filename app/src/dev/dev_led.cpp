#include <dev/led.h>
#include <yss/instance.h>

namespace led
{
	void initialize(void)
	{
		gpioB.setAsOutput(14);
		gpioB.setAsOutput(11);
		gpioB.setAsOutput(10);

		setLedR(false);
		setLedY(false);
		setLedG(false);
	}

	void setLedR(bool on)
	{
		gpioB.setOutput(14, !on);
	}

	void setLedY(bool on)
	{
		gpioB.setOutput(11, !on);
	}

	void setLedG(bool on)
	{
		gpioB.setOutput(10, !on);
	}
}

