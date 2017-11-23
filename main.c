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
	insertAtTail(&ReadyQHead, tid);
	insertAtTail(&ReadyQHead, tid);
	insertAtTail(&ReadyQHead, tid);
	insertAtTail(&ReadyQHead, tid);
	insertAtTail(&ReadyQHead, tid);
	insertAtTail(&ReadyQHead, tid);
	deleteAtFirst(&ReadyQHead);
	print(&ReadyQHead);

	deleteAtFirst(&ReadyQHead);
	print(&ReadyQHead);

	deleteAtFirst(&ReadyQHead);
	print(&ReadyQHead);

}

