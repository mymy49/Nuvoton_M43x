/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

#include <bsp.h>
#include <yss/instance.h>

void initializeBoard(void)
{
	// LED 초기화
	led::initialize();

	// UART0 초기화
	gpioB.setAsAltFunc(12, Gpio::PB12_UART0_RXD);
	gpioB.setAsAltFunc(13, Gpio::PB13_UART0_TXD);

	uart0.enableClock();
	uart0.initialize(115200, 64);
	uart0.enableInterrupt();

	// SPI1 초기화
	gpioC.setAsOutput(0);
	gpioC.setAsAltFunc(1, Gpio::PC1_SPI1_CLK);
	gpioC.setAsAltFunc(2, Gpio::PC2_SPI1_MOSI);
	gpioC.setAsAltFunc(3, Gpio::PC3_SPI1_MISO);

	spi1.enableClock();
	spi1.initializeAsMain();
	spi1.enableInterrupt();
}

