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


void* child1(void *arg) {
	int i=0;
	while(i<5){
		printf("child 1\n");
		sleep(1);
		i++;
	}
	return NULL;
}

void *child2(void *arg) {
	int i=0;
	while(i<5){
		printf("child 2\n");
		sleep(1);
		i++;
	}
	return NULL;
}

void *child3(void *arg) {
	int i=0;
	while(i<5){
		printf("child 3\n");
		sleep(1);
		i++;
	}
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

	thread_t a,b,c, s;
	// printf("main tid : %u\n", pthread_self());
	// int t=-1;
	// //a= pthread_create(&c, NULL,__wrapperFunc,&wrapperArg);
	printf("child1 : %d\n", child1);
	thread_create(&a, NULL, child1,10);
	thread_create(&b, NULL, child2,10);	
	thread_create(&c, NULL, child3,10);

	print(READY_QUEUE);
	sleep(2);
	printf("tid :%u\n", a);
	__thread_wakeup(__getThread(a));
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
	sleep(2);
	print(READY_QUEUE);
	//pthread_create( &s, NULL, RunScheduler, NULL );
	sleep(10);


	
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

