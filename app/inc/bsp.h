/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

#ifndef BSP__H_
#define BSP__H_

#include <dev/led.h>

#include <stdint.h>

#include <mod/spi_tft_lcd/Touch_LCD_Shield_for_Arduino_2_8_inch.h>

#include <gui/Bmp565Buffer.h>

void initializeBoard(void);

extern Bmp565Buffer brush;

extern Touch_LCD_Shield_for_Arduino_2_8_inch lcd;

#endif

