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
#include <util/ElapsedTime.h>
#include <UsbClass/NuvotonAudio10.h>
#include <stdio.h>
#include <string.h>

NuvotonAudio10 audio10;

void thread_blinkLedR(void);
void thread_blinkLedY(void);
void thread_blinkLedG(void);
void thread_testUart(void);

int main(void)
{
	uint32_t cnt;
	uint8_t data[512];

	// 운영체체 초기화
	initializeYss();

	// 보드 초기화
	initializeBoard();

	thread::add(thread_blinkLedR, 512);
	thread::add(thread_blinkLedG, 512);
	thread::add(thread_blinkLedY, 512);
	thread::add(thread_testUart, 512);

	// USB Audio Class 초기화
	audio10.initialize();

	// USBD 초기화
	gpioA.setAsAltFunc(12, Gpio::PA12_USB_VBUS);
	gpioA.setAsAltFunc(13, Gpio::PA13_USBD_DN);
	gpioA.setAsAltFunc(14, Gpio::PA14_USBD_DP);
	gpioA.setAsAltFunc(15, Gpio::PA15_USB_OTG_ID);

	usbd.enableClock();
	usbd.initialize(audio10);
	usbd.enableInterrupt();

	while(1)
	{
		cnt = audio10.getRxDataCount();

		if(cnt > 0)
		{
			audio10.getRxData(data, cnt);
			//debug_printf("%d\n", cnt);
		}

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


