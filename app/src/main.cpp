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
#include <UsbClass/NuvotonCdc.h>
#include <stdio.h>
#include <string.h>

NuvotonCdc cdc;

void thread_blinkLedR(void);
void thread_blinkLedY(void);
void thread_blinkLedG(void);
void thread_testUart(void);

int main(void)
{
	char sendBuf[256], rcvBuf[64];
	uint32_t len, cnt = 0;

	// 운영체체 초기화
	initializeYss();

	// 보드 초기화
	initializeBoard();

	thread::add(thread_blinkLedR, 512);
	thread::add(thread_blinkLedG, 512);
	thread::add(thread_blinkLedY, 512);
	thread::add(thread_testUart, 512);

	// CDC 초기화
	const char *manufacture = "Nuvoton";
	const char *product= "yss OS Virtual COM Port";

	Cdc::config_t cdcConfig = 
	{
		1,				//uint8_t inEpNum;
		64,				//uint16_t inEpMaxPacketSize;
		2,				//uint8_t outEpNum;
		64,				//uint16_t outEpMaxPacketSize;
		3,				//uint8_t ctlEpNum;
		8,				//uint16_t ctlEpMaxPacketSize;
		manufacture,	//const char *manufactureString;
		product,		//const char *productString;
		0				//const char *serialNumberString;
	};

	cdc.initialize(cdcConfig);
	//cdc.initialize();

	// USBD 초기화
	gpioA.setAsAltFunc(12, Gpio::PA12_USB_VBUS);
	gpioA.setAsAltFunc(13, Gpio::PA13_USBD_DN);
	gpioA.setAsAltFunc(14, Gpio::PA14_USBD_DP);
	gpioA.setAsAltFunc(15, Gpio::PA15_USB_OTG_ID);

	usbd.enableClock();
	usbd.initialize(cdc);
	usbd.enableInterrupt();

	thread::delay(5000);
	
	while(1)
	{
		if(cdc.isClearToSend())
		{
			sprintf(sendBuf, "Hello World!! Test String!! yss OS is Great Operating System!! Have a Enjoy!! %d\n\r", cnt++); 
			len = strlen(sendBuf);
			cdc.send(sendBuf, len); // 최대 초당 750 kB 전송속도 확인
		}

		len = cdc.getRxDataCount();
		if(len > 0)
		{
			cdc.getRxData(rcvBuf, len);
			for(uint32_t i = 0; i < len; i++)
				debug_printf("%c", rcvBuf[i]);
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


