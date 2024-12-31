/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

#include <yss.h>
#include <bsp.h>
#include <util/runtime.h>
#include <yss/debug.h>
#include <std_ext/string.h>

void thread_blinkLedR(void);
void thread_blinkLedY(void);
void thread_blinkLedG(void);
void thread_testUart(void);

int main(void)
{
	// 운영체체 초기화
	initializeYss();

	// 보드 초기화
	initializeBoard();

	thread::add(thread_blinkLedR, 512);
	thread::add(thread_blinkLedG, 512);
	thread::add(thread_blinkLedY, 512);
	thread::add(thread_testUart, 512);
	
	// bpwm0 초기화
	gpioA.setAsAltFunc(11, Gpio::PA11_BPWM0_CH0);
	gpioA.setAsAltFunc(10, Gpio::PA10_BPWM0_CH1);
	gpioA.setAsAltFunc(9, Gpio::PA9_BPWM0_CH2);;
	gpioA.setAsAltFunc(8, Gpio::PA8_BPWM0_CH3);

	bpwm0.enableClock();
	bpwm0.initialize(1000);
	bpwm0.setAsPwmOutput(0, true);
	bpwm0.setAsPwmOutput(1);
	bpwm0.setAsPwmOutput(2);
	bpwm0.setAsPwmOutput(3);
	bpwm0.start();

	bpwm0.setDutyRatio(0, 0.1);
	bpwm0.setDutyRatio(1, 0.2);
	bpwm0.setDutyRatio(2, 0.3);
	bpwm0.setDutyRatio(3, 0.4);

	while(1)
	{
		thread::yield();
	}
}

void thread_blinkLedR(void)
{
	while(1)
	{
		led::setLedR(true);
		thread::delay(250);

		led::setLedR(false);
		thread::delay(250);
	}
}

void thread_blinkLedG(void)
{
	while(1)
	{
		led::setLedG(true);
		thread::delay(500);

		led::setLedG(false);
		thread::delay(500);
	}
}

void thread_blinkLedY(void)
{
	while(1)
	{
		led::setLedY(true);
		thread::delay(1000);

		led::setLedY(false);
		thread::delay(1000);
	}
}

void thread_testUart(void)
{
	while(1)
	{
		uart0.send("Hello World!!\n\r", sizeof("Hello World!!\n\r"));
	}
}


