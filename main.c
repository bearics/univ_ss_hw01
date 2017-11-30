#include "Init.h"
#include "Scheduler.h"
#include "Thread.h"
#include "App.h"
#include<stdio.h>
#include <signal.h>
#include <stdlib.h>
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

	thread_t a,b,c;
	// printf("main tid : %u\n", pthread_self());
	// int t=-1;
	// //a= pthread_create(&c, NULL,__wrapperFunc,&wrapperArg);
	thread_create(&a, NULL,child1,10);
	thread_create(&b, NULL,child2,10);	
	thread_create(&c, NULL,child3,10);
	// int status;
	// printf("kill SIGUSR1\n");
	// print(READY_QUEUE);
	// Thread* th = (Thread*)malloc(sizeof(Thread));
	// th->tid = 0;
	// th->pNext =NULL;
	// th->pPrev =NULL;
	// sleep(3);
	// printf("a : %u\n", a);
	// __ContextSwitch(*th, __getThread(a));

	// sleep(10);
	
 	Thread* th;

	//insertAtTail(READY_QUEUE, tid);
	//insertAtTail(READY_QUEUE, tid);
	//insertAtTail(READY_QUEUE, tid);
	print(READY_QUEUE);
	printf("a: %u\n", a);
	deleteNode(READY_QUEUE, a);
	print(READY_QUEUE);
	printf("c: %u\n", c);
	deleteNode(READY_QUEUE, c);
	print(READY_QUEUE);
	printf("b: %u\n", b);
	deleteNode(READY_QUEUE, b);
	print(READY_QUEUE);

	
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

