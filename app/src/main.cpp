/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

#include <yss.h>
#include <bsp.h>

int main(void)
{
	// 운영체체 초기화
	initializeYss();

	// 보드 초기화
	initializeBoard();

	while(1)
	{
		thread::yield();
	}
}
