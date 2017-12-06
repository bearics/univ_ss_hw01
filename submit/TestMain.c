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
	pthread_t tid1 = (pthread_t)0;
	pthread_t tid2 = (pthread_t)0;
	pthread_t tid3 = (pthread_t)0;
	pthread_t tid4 = (pthread_t)0;
	pthread_t tid5 = (pthread_t)0;

	Thread th1;
	th1.tid = (pthread_t)1;
	Thread th2;
	th2.tid = (pthread_t)2;
	Thread th3;
	th3.tid = (pthread_t)3;
	Thread th4;
	th4.tid = (pthread_t)4;
	Thread th5;
	th5.tid = (pthread_t)5;

	insertAtTail(READY_QUEUE, &th1);
	insertAtTail(READY_QUEUE, &th2);
	insertAtTail(READY_QUEUE, &th3);
	insertAtTail(READY_QUEUE, &th4);
	insertAtTail(READY_QUEUE, &th5);

	printQ();

	insertAtTail(WAITING_QUEUE, deleteNode(READY_QUEUE, (pthread_t)5 ));
	printQ();

	insertAtTail(READY_QUEUE, deleteNode(WAITING_QUEUE, (pthread_t)5 ));

	printQ();
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

