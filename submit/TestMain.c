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

void hyounglin()
{
	pthread_t tid1, tid2, tid3;
	print(READY_QUEUE);
	print(WAITING_QUEUE);
	insertAtTail(READY_QUEUE, createNode((pthread_t)0));

	print(READY_QUEUE);
	print(WAITING_QUEUE);
	insertAtTail(READY_QUEUE, createNode((pthread_t)1));

	print(READY_QUEUE);
	print(WAITING_QUEUE);
	insertAtTail(READY_QUEUE, createNode((pthread_t)2));

	print(READY_QUEUE);
	print(WAITING_QUEUE);


	insertAtTail(WAITING_QUEUE ,deleteAtFirst(READY_QUEUE));
	print(READY_QUEUE);
	print(WAITING_QUEUE);

	insertAtTail(WAITING_QUEUE ,deleteAtFirst(READY_QUEUE));
	print(READY_QUEUE);
	print(WAITING_QUEUE);

	insertAtTail(WAITING_QUEUE ,deleteAtFirst(READY_QUEUE));
	print(READY_QUEUE);
	print(WAITING_QUEUE);

	insertAtTail(READY_QUEUE ,deleteAtFirst(WAITING_QUEUE));
	print(READY_QUEUE);
	print(WAITING_QUEUE);

	insertAtTail(READY_QUEUE ,deleteAtFirst(WAITING_QUEUE));
	print(READY_QUEUE);
	print(WAITING_QUEUE);

	insertAtTail(READY_QUEUE ,deleteAtFirst(WAITING_QUEUE));
	print(READY_QUEUE);
	print(WAITING_QUEUE);

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

