#include "Init.h"
#include "Thread.h"
#include "Scheduler.h"
#include "Run.h"
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>


int		RunScheduler( void )
{
	while(1)
	{
		//printQ();
		pthread_mutex_lock(&mainMutex);
		if(runStop != 0){
			//printf("wait!!\n");
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
		pCurThread->status = THREAD_STATUS_READY;
		pthread_kill(pCurThread->tid, SIGUSR1);
		insertAtTail(READY_QUEUE, pCurThread);
	}
	runTh = deleteAtFirst(READY_QUEUE);
	runTh->status = THREAD_STATUS_RUN;

	//printf("wakeup %u\n", runTh->tid);
	__thread_wakeup(runTh);	
	return;
}


