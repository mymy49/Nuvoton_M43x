/*
 * Copyright (c) 2023 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

#include <task.h>
#include <yss.h>
#include <bsp.h>
#include <util/Timeout.h>
#include <../bmp/NuvotonLogo.h>
#include <../font/Ubuntu_14_B.h>
#include <../font/Ubuntu_20_B.h>

namespace Task
{
	error_t displayLogo(FunctionQueue *obj)
	{
		(void)obj;

		lock();			// unlock()을 만날 때까지 외부에서 이 함수를 강제 종료 시키지 못한다.
		clearTask();	// 이전에 등록된 쓰레드 등을 전부 제거한다.
		
		// LCD 화면을 구성한다.
		lcd.lock();
		lcd.drawBitmap({30, 30}, NuvotonLogo);

		brush.setSize(240, 20);
		brush.setBackgroundColor(0xFF, 0xFF, 0xFF);
		brush.setFontColor(0x00, 0x00, 0x00);
		brush.setFont(Font_Ubuntu_14_B);

		brush.clear();
		brush.drawStringToCenterAligned("NuMaker-M433SE V1.0");
		lcd.drawBitmap({0, 100}, brush.getBitmap());

		brush.clear();
		brush.drawStringToCenterAligned("with");
		lcd.drawBitmap({0, 125}, brush.getBitmap());

		brush.clear();
		brush.drawStringToCenterAligned("2.8inch TFT Touch Shield");
		lcd.drawBitmap({0, 150}, brush.getBitmap());

		brush.clear();
		brush.drawStringToCenterAligned("Powered by yss OS");
		lcd.drawBitmap({0, 280}, brush.getBitmap());

		brush.setFont(Font_Ubuntu_20_B);
		brush.setSize(200, 25);

		brush.clear();
		brush.drawStringToCenterAligned("Exameple");
		lcd.drawBitmap({20, 200}, brush.getBitmap());
		
		// 백라이트를 Fade in 한다.
		fadeinBackLight();
		
		// 5초간 로고 화면에서 대기한다.
		Timeout tout(5000);
		while(!tout.isTimeout())
		{
			thread::delay(250);
			brush.clear();
			lcd.drawBitmap({20, 200}, brush.getBitmap());

			thread::delay(250);
			brush.clear();
			brush.drawStringToCenterAligned("Exameple");
			lcd.drawBitmap({20, 200}, brush.getBitmap());
		}

		lcd.unlock();
		
		// 백라이트를 Fade out 한다.
		fadeoutBackLight();

		unlock();

		return error_t::ERROR_NONE;
	}
}


