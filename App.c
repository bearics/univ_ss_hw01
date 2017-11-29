#include "App.h"
#include "TestCase.h"
#include <stdio.h>

void* AppTask(void* param)
{
	TestCase();
	return NULL;
}