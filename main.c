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


void *child1(void *arg) {
	while(1)
		printf("child 1\n");
	return NULL;
}

void *child2(void *arg) {
	while(1)
		printf("child 2\n");
	return NULL;
}

void *child3(void *arg) {
	while(1)
		printf("child 3\n");
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
	a= thread_create(&c, NULL,child1,10);
	a= thread_create(&c, NULL,child2,10);	
	a= thread_create(&c, NULL,child3,10);
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

