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

NuvotonCdc cdc;

void thread_blinkLedR(void);
void thread_blinkLedY(void);
void thread_blinkLedG(void);
void thread_testUart(void);

int main(void)
{
	ElapsedTime powerDownTime;

	// 운영체체 초기화
	initializeYss();

	// 보드 초기화
	initializeBoard();

	thread::add(thread_blinkLedR, 512);
	thread::add(thread_blinkLedG, 512);
	thread::add(thread_blinkLedY, 512);
	//thread::add(thread_testUart, 512);

	// EPWM0 초기화
	gpioA.setAsAltFunc(5, Gpio::PA5_EPWM0_CH0);
	gpioA.setAsAltFunc(4, Gpio::PA4_EPWM0_CH1);
	gpioA.setAsAltFunc(3, Gpio::PA3_EPWM0_CH2);
	gpioA.setAsAltFunc(2, Gpio::PA2_EPWM0_CH3);
	gpioA.setAsAltFunc(1, Gpio::PA1_EPWM0_CH4);
	gpioA.setAsAltFunc(0, Gpio::PA0_EPWM0_CH5);

	epwm0.enableClock();
	
	// CH0 초기화
	epwm0.initialize(0, 1000);
	epwm0.setAsPwmOutput(0, true);
	epwm0.start(0);
	epwm0.setDutyRatio(0, 0.1);

	// CH1 초기화
	epwm0.initialize(1, 1000);
	epwm0.setAsPwmOutput(1);
	epwm0.start(1);
	epwm0.setDutyRatio(1, 0.2);

	// CH2 초기화
	epwm0.initialize(2, 1000);
	epwm0.setAsPwmOutput(2);
	epwm0.start(2);
	epwm0.setDutyRatio(2, 0.3);

	// CH3 초기화
	epwm0.initialize(3, 1000);
	epwm0.setAsPwmOutput(3);
	epwm0.start(3);
	epwm0.setDutyRatio(3, 0.4);

	// CH4 초기화
	epwm0.initialize(4, 1000);
	epwm0.setAsPwmOutput(4);
	epwm0.start(4);
	epwm0.setDutyRatio(4, 0.5);
	
	// CH5 초기화
	epwm0.initialize(5, 1000);
	epwm0.setAsPwmOutput(5);
	epwm0.start(5);
	epwm0.setDutyRatio(5, 0.6);

	// CDC 초기화
	Cdc::config_t cdcConfig = 
	{
		1,	//uint8_t inEpNum;
		64,	//uint16_t inEpMaxPacketSize;
		2,	//uint8_t outEpNum;
		64,	//uint16_t outEpMaxPacketSize;
		3,	//uint8_t ctlEpNum;
		8	//uint16_t ctlEpMaxPacketSize;
	};

	cdc.initialize(cdcConfig);

	// USBD 초기화
	gpioA.setAsAltFunc(12, Gpio::PA12_USB_VBUS);
	gpioA.setAsAltFunc(13, Gpio::PA13_USBD_DN);
	gpioA.setAsAltFunc(14, Gpio::PA14_USBD_DP);
	gpioA.setAsAltFunc(15, Gpio::PA15_USB_OTG_ID);

	usbd.enableClock();
	usbd.initialize(cdc);
	usbd.enableInterrupt();
	
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


