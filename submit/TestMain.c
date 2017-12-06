#include <stdio.h>
#include <stdlib.h>

#include "TestCase1.h"
#include "TestCase2.h"
#include "TestCase3.h"

#include "Init.h"
#include "Scheduler.h"
#include "Thread.h"
#include "Run.h"


// #include "Task.h"
// #include "init.h"
// #include "ObjMgr.h"
// #include "Scheduler.h"

void* hi(void* w)
{
	printf("here??\n");	
	while(1)
	{
		printf("=%d\n", *((int*)w));
		sleep(1);
	}
}

void hyounglin()
{
	pthread_t tid1, tid2, tid3;

	int a=7;

	thread_create(&tid1, NULL, (void*)hi, (void*)&a);

	print(READY_QUEUE);

	sleep(2);
	__thread_wakeup(searchQueue(READY_QUEUE, tid1));
	
	printf("tid : %u\n", tid1);

	while(1){}


	return;
}


void main(int argc, char* argv[])
{
	int TcNum;
	thread_t tid1,tid2,tid3,tid4;

	if(argc != 2)
	{
		perror("Input TestCase Number!");
		exit(0);
	}
	
	Init(  );
	
	TcNum = atoi(argv[1]);
	
	switch(TcNum)
	{
		case 1:
		    thread_create(&tid1, NULL, (void*)TestCase1, 0);
			break;
		case 2:
			thread_create(&tid2, NULL, (void*)TestCase2, 0);
		    break;
		case 3:
			thread_create(&tid3, NULL, (void*)TestCase3, 0);
		   	break;
		case 4:
			hyounglin();
			break;

	}

	RunScheduler();
	while(1){}
}

