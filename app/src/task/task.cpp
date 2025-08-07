/*
 * Copyright (c) 2023 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

#include "../inc/task.h"
#include <yss.h>
#include <util/key.h>

#define MAX_TASK_THREAD		4

namespace Task
{
	uint32_t gThreadCnt;
	threadId_t gThreadId[MAX_TASK_THREAD];
	FunctionQueue *gFq;
	Mutex gMutex;

	void setFunctionQueue(FunctionQueue &obj)
	{
		gFq = &obj;
	}

	void lock(void)
	{
		gMutex.lock();
	}

	void unlock(void)
	{
		gMutex.unlock();
	}

	void addThread(void (*func)(void), uint32_t stackSize)
	{
		if(gThreadCnt < MAX_TASK_THREAD)
			gThreadId[gThreadCnt++] = thread::add(func, stackSize);
	}

	void clearTask(void)
	{
		key::clear();

		for(uint32_t i=0;i<gThreadCnt;i++)
		{
			if(gThreadId[i])
			{
				thread::remove(gThreadId[i]);
				gThreadId[i] = 0;
			}
		}

		gThreadCnt = 0;
	}
}

