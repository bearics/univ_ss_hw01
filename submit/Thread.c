#include "Thread.h"
#include "Init.h"
#include "Scheduler.h"
#include "Run.h"
#include <stdlib.h>
#include <signal.h>

int 	thread_create(thread_t *thread, thread_attr_t *attr, void *(*start_routine) (void *), void *arg)
{
	Thread* pTh = NULL;
	runStop++;
	waitCreate = 0;
	pthread_mutex_lock(&mainMutex);
	WrapperArg* wrapperArg=(WrapperArg*)malloc(sizeof(WrapperArg));
	wrapperArg->funcPtr = start_routine;
	wrapperArg->funcArg = arg;
	pthread_create(thread, attr, __wrapperFunc,wrapperArg);
	pTh = insertAtTail(READY_QUEUE, createNode(*thread));	// insert readyQ
	while(waitCreate != 1) {}
	pthread_mutex_lock(&(pTh->readyMutex));
	pthread_mutex_unlock(&(pTh->readyMutex));
	runResume();
}


int 	thread_join(thread_t thread, void **retval)
{
	Thread* pth = NULL;
	Thread* cth = NULL;
	runStop++;
	pthread_mutex_lock(&mainMutex);
	printf("Im(%u) join!!! = %u\n", pthread_self(), thread);
	printQ();
	if(searchQueue(WAITING_QUEUE, thread) == NULL)
	{	
		printf("Im waiting tid = %u\n", thread);
		printQ();
		if(runTh == NULL)
			return -1;
		pth = runTh;
		insertAtTail(WAITING_QUEUE, pth);
		runTh = NULL;
		while(searchQueue(WAITING_QUEUE, thread) == NULL)
		{
			runResume();
			__thread_wait_handler(0);
			printf("join wake up!!\n"); 
			pthread_mutex_lock(&mainMutex);
		}

		runStop++;
		
		insertAtTail(READY_QUEUE, pth);
		deleteNode(WAITING_QUEUE, pth->tid);
		printf("join wake up!! (%u) tid = %u\n", pthread_self() , thread);
	}
	//printf("%u\n", thread);
	cth=searchQueue(WAITING_QUEUE, thread);
	*retval = cth->pExitCode;
	printf("delete tid = %u , %u\n", cth->tid, thread);
	free(deleteNode(WAITING_QUEUE, cth->tid));
	printQ();
	runResume();
	return 0;
}


int 	thread_suspend(thread_t tid)
{

}


int	thread_resume(thread_t tid)
{

}

int thread_exit(void* retval)
{
	//printf("exit exe!\n");
	Thread* pth=NULL;
	Thread* cth=NULL;
	runStop++;
	pthread_mutex_lock(&mainMutex);
	cth = runTh;
	printQ();
	printf("exi: tid=%u\n", pthread_self());
	cth->pExitCode = retval;
	cth->status = THREAD_STATUS_ZOMBIE;
	insertAtTail(WAITING_QUEUE, cth);
	while((cth = searchQueue(WAITING_QUEUE, cth->tid)) == NULL){}
	runTh = NULL;

	if( (pth = searchQueue(WAITING_QUEUE, cth->parentTid)) != NULL)
		__thread_wakeup(pth);

	runResume();
	return 0;
}

thread_t	thread_self()
{
	return pthread_self();
}	
