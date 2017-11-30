#include "Init.h"
#include "Scheduler.h"
#include "Thread.h"
#include "App.h"
#include<stdio.h>
#include <signal.h>

#include <errno.h>


// typedef struct __wrapperArg {
// 	void*  (*funcPtr)(void*);
// 	void* funcArg;
// } WrapperArg;




void *child(void *arg) {
	printf("child\n");
	return NULL;
}



int main(void)
{
// 	// init ready, wait queue	
 	pthread_t tid;
// 	int arg;
// 	Init();

// //	thread_create(&tid, NULL, AppTask, &arg);

// 	RunScheduler();

	pthread_t c;
	printf("main tid : %u\n", pthread_self());
	int a=-1;
	//a= pthread_create(&c, NULL,__wrapperFunc,&wrapperArg);
	a= thread_create(&c, NULL,child,10);
	sleep(3);
	a= thread_create(&c, NULL,child,10);
	sleep(1);
	a= thread_create(&c, NULL,child,10);
	int status;
	printf("kill SIGUSR1\n");
	print(READY_QUEUE);

	sleep(1);
	


	// insertAtTail(READY_QUEUE, tid);
	// insertAtTail(READY_QUEUE, tid);
	// insertAtTail(READY_QUEUE, tid);
	// insertAtTail(READY_QUEUE, tid);
	// insertAtTail(READY_QUEUE, tid);
	// insertAtTail(READY_QUEUE, tid);
	// print(READY_QUEUE);
	// deleteAtFirst(READY_QUEUE);
	// deleteAtFirst(READY_QUEUE);
	// deleteAtFirst(READY_QUEUE);
	// deleteAtFirst(READY_QUEUE);
	// deleteAtFirst(READY_QUEUE);

	// print(READY_QUEUE);
	// deleteAtFirst(READY_QUEUE);
	// print(READY_QUEUE);

}

