#include "Init.h"
#include "Scheduler.h"
#include "Thread.h"

#include<stdio.h>

int main(void)
{
	// init ready, wait queue	
	ReadyQHead = NULL;
	ReadyQTail = NULL;

	WaitQHead = NULL;
	WaitQTail = NULL;

	pthread_t tid;
	insertAtTail(READY_QUEUE, tid);
	insertAtTail(READY_QUEUE, tid);
	insertAtTail(READY_QUEUE, tid);
	insertAtTail(READY_QUEUE, tid);
	insertAtTail(READY_QUEUE, tid);
	insertAtTail(READY_QUEUE, tid);
	deleteAtFirst(READY_QUEUE);
	print(READY_QUEUE);

	deleteAtFirst(READY_QUEUE);
	print(READY_QUEUE);

	deleteAtFirst(READY_QUEUE);
	print(READY_QUEUE);

}

