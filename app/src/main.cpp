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
#include <UsbClass/NuvotonDualCdc.h>
#include <UsbClass/NuvotonCdc.h>
#include <stdio.h>
#include <string.h>

NuvotonDualCdc cdc;

void thread_blinkLedR(void);
void thread_blinkLedY(void);
void thread_blinkLedG(void);
void thread_testUart(void);
void thread_testCdcEcho0(void);
void thread_testCdcEcho1(void);

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

	// CDC 초기화
	cdc.initialize();

	// USBD 초기화
	gpioA.setAsAltFunc(12, Gpio::PA12_USB_VBUS);
	gpioA.setAsAltFunc(13, Gpio::PA13_USBD_DN);
	gpioA.setAsAltFunc(14, Gpio::PA14_USBD_DP);
	gpioA.setAsAltFunc(15, Gpio::PA15_USB_OTG_ID);

	usbd.enableClock();
	usbd.initialize(cdc);
	usbd.enableInterrupt();

	// CDC Port0 ECHO Test
	thread::add(thread_testCdcEcho0, 512);

	// CDC Port1 ECHO Test
	thread::add(thread_testCdcEcho1, 512);

	while(1)
	{
		thread::yield();
	}
}

void thread_testCdcEcho0(void)
{
	char buf[64];
	uint32_t len;

	while(1)
	{
		if(cdc.isClearToSend0())
		{
			len = cdc.getRxDataCount0();
			if(len > 0)
			{
				cdc.getRxData0(buf, len);
				cdc.send0(buf, len);
			}
		}

		thread::yield();
	}
}

void thread_testCdcEcho1(void)
{
	char buf[64];
	uint32_t len;

	while(1)
	{
		if(cdc.isClearToSend1())
		{
			len = cdc.getRxDataCount1();
			if(len > 0)
			{
				cdc.getRxData1(buf, len);
				cdc.send1(buf, len);
			}
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


