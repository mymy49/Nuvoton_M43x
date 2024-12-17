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

uint32_t gTimer0Cnt;

void isr_timer0(void)
{
	gTimer0Cnt++;
}

void isr_PD2(void)
{
	debug_printf("PD2!!\n", gTimer0Cnt);
}

void isr_PD3(void)
{
	debug_printf("PD3!!\n", gTimer0Cnt);
}

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
	
	// GPIO 인터럽트 활성화 예제
	gpioD.enablInterrupt(2, Gpio::EDGE_FALLING, isr_PD2);
	gpioD.enablInterrupt(3, Gpio::EDGE_FALLING, isr_PD3);
	gpioD.enableInterrupt(true);
	
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


