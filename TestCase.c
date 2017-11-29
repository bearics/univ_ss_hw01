#include "TestCase.h"
#include <stdio.h>


void* foo1(void* arg)
{
	while(1)
		printf("1\n");
}

void* foo2(void* arg)
{

	while(1)
		printf("2\n");		
}

void TestCase(void)
{
	int tid1, tid2, tid3;
	int arg1, arg2, arg3;
	printf("add\n");
//	thread_create(&tid1, NULL, foo1, &arg1);
//	thread_create(&tid2, NULL, foo2, &arg2);
//	thread_create(&tid3, NULL, foo3, &arg3);
//	thread_suspend(tid1);
//	thread_suspend(tid2);
//	thread_resume(tid1);
	while(1);
}