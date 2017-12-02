#include "Init.h"
#include "Thread.h"
#include "Scheduler.h"
#include <string.h>
#include <signal.h>



int		RunScheduler( void )
{
	while(1)
	{
		if(ReadyQHead != NULL)
		{
			if( ReadyQHead->status != THREAD_STATUS_RUN )	// no running thread
			{
				//printf("start first\n");
				ReadyQHead->status = THREAD_STATUS_RUN;
				__thread_wakeup(ReadyQHead);
				// __thread_wakeup(runTh);
			}
			else
			{
				// move running thread node to last node
				insertAtTail(READY_QUEUE, ReadyQHead->tid);
				copyNode(ReadyQHead, ReadyQTail);
				ReadyQTail->status = THREAD_STATUS_READY;
				ReadyQTail->bRunnable = FALSE;
				deleteAtFirst(READY_QUEUE);
				ReadyQHead->status = THREAD_STATUS_RUN;
				// run first node and stop last node(running thread)
				__ContextSwitch(*ReadyQTail, ReadyQHead);

			}
			
		}
		sleep(TIMESLICE);
	}
	print(READY_QUEUE);
	free(runTh);
}

// pCurThread is running(in runTh), pNewThread is next queue.(in 1st node)
void __ContextSwitch(Thread pCurThread, Thread* pNewThread)
{
	//printf("%u , %u\n", pCurThread.tid, pNewThread->tid);

	// sleep Current Thread(running)
	pthread_kill(pCurThread.tid, SIGUSR1);
	// wakeup next thread(ready)
	__thread_wakeup(pNewThread);

	//printf("context tid : %u, next=%p, prev=%p\n", pCurThread.tid, pCurThread.pNext,pCurThread.pPrev);
	//printf("context tid : %u, next=%p, prev=%p\n", pNewThread->tid, pNewThread->pNext,pNewThread->pPrev);

}

