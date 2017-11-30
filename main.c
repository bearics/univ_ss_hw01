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

void *__wrapperFunc(void* arg)
{

	void* ret;
	WrapperArg* pArg = (WrapperArg*)arg;
	sigset_t set;
	Thread pTh;
	int retSig;
	// child sleeps until TCB is initialized
	printf("self :%u\n",pthread_self());
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	//sleep(1);
	//sigwait(&set, &retSig);
	printf("11%d\n", retSig);
	while(__getThread(pthread_self()) == (Thread *)(-1)) {
		printf("not yet!\n");
	}
	// child is ready to run
	__thread_wait_handler(0);
	printf("dddd");

	// Run child function 
	ret = (*pArg->funcPtr)(pArg->funcArg);
	return ret;
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
	WrapperArg wrapperArg;
	wrapperArg.funcPtr = child;
	wrapperArg.funcArg = 10;
	printf("main tid : %d\n", pthread_self());
	int a=-1;
	//a= pthread_create(&c, NULL,__wrapperFunc,&wrapperArg);
	a= thread_create(&c, NULL,__wrapperFunc,&wrapperArg);
	sleep(3);
	a= thread_create(&c, NULL,__wrapperFunc,&wrapperArg);
	sleep(1);
	a= thread_create(&c, NULL,__wrapperFunc,&wrapperArg);
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

