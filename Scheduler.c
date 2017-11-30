#include "Init.h"
#include "Thread.h"
#include "Scheduler.h"
#include <string.h>
#include <signal.h>

int		RunScheduler( void )
{
	Thread* runTh = malloc(sizeof(Thread));	// running Thread pointer
	
	while(1)
	{
		if(ReadyQHead != NULL)
		{
			if(runTh != NULL)
				insertAtTail(READY_QUEUE, runTh->tid);
			memcpy(runTh, ReadyQHead, sizeof(Thread));
			runTh->bRunnable = TRUE;
			runTh->status = THREAD_STATUS_RUN;
			deleteAtFirst(READY_QUEUE);
			sleep(TIMESLICE);
			break;
			if(runTh == NULL)	// no running Thread
			{
				
			}
			else
			{

			}


			__ContextSwitch(*runTh, ReadyQHead);
			//Thread running = 
			//__ContextSwitch(ReadyQHead, ReadyQHead->pNext);
		}
		sleep(TIMESLICE);
	}
}

// pCurThread is running(in 1st node), pNewThread is next queue.(in 2nd node)
void __ContextSwitch(Thread pCurThread, Thread* pNewThread)
{
	printf("%p , %p", pCurThread, pNewThread);
	//if(pNewThread != NULL){
	if(1){
		printf("hello?\n");
		pthread_kill(pCurThread.tid, SIGUSR1);
		__thread_wakeup(pNewThread);
		printf("context tid : %u, next=%p, prev=%p\n", pCurThread.tid, pCurThread.pNext,pCurThread.pPrev);
		printf("context tid : %u, next=%p, prev=%p\n", pNewThread->tid, pNewThread->pNext,pNewThread->pPrev);
		//__thread_wakeup(pNewThread);
		//insertAtTail(READY_QUEUE, pCurThread.tid);
		//deleteAtFirst(READY_QUEUE);	
	}
}

