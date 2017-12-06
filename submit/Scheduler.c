#include "Init.h"
#include "Thread.h"
#include "Scheduler.h"
#include "Run.h"
#include <stdio.h>
#include <pthread.h>
#include <signal.h>


int		RunScheduler( void )
{
	while(1)
	{
		pthread_mutex_lock(&mainMutex);
		if(runStop != 0){
			printf("wait!!\n");
			pthread_cond_wait(&mainCond, &mainMutex);
		}
		__ContextSwitch(runTh, ReadyQHead);
		pthread_mutex_unlock(&mainMutex);
		//printQ();
		sleep(TIMESLICE);
		
	}
}

void    __ContextSwitch(Thread* pCurThread, Thread* pNewThread)
{
	// sleep current thread
	// nothing in current thread
	if(pNewThread == NULL)
		return;	// nothing to run

	if(pCurThread != NULL)
	{
		runTh->status = THREAD_STATUS_READY;
		pthread_kill(runTh->tid, SIGUSR1);
		insertAtTail(READY_QUEUE, runTh);
	}
	runTh = deleteAtFirst(READY_QUEUE);
	runTh->status = THREAD_STATUS_RUN;

	//printf("wakeup %u\n", runTh->tid);
	__thread_wakeup(runTh);	
	return;
}


/*
	print(READY_QUEUE);
	printf("0000000000000000000000000000000000000000000000000\n");
	print(WAITING_QUEUE);
	printRunningTh();
	printf("my tid = %u\n", pthread_self());

*/

