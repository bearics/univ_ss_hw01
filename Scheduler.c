#include "Init.h"
#include "Thread.h"
#include "Scheduler.h"
#include <string.h>
#include <signal.h>

int		RunScheduler( void )
{
	Thread* runTh = createNode((thread_t)0);	// running Thread pointer
	Thread* nextTh = createNode((thread_t)0);
	while(1)
	{
		if(ReadyQHead != NULL)
		{
			if( runTh->tid != (thread_t)0 )
			{
				insertAtTail(READY_QUEUE, runTh->tid);
				Thread* readyNode = searchQueue(READY_QUEUE, runTh->tid);	// find TCB in waiting queue
				copyNode(runTh, readyNode);
				readyNode->bRunnable = FALSE;
				readyNode->status = THREAD_STATUS_READY;
			}
			copyNode(ReadyQHead, nextTh);
			deleteAtFirst(READY_QUEUE);
			nextTh->status = THREAD_STATUS_RUN;
			nextTh->bRunnable = TRUE;
			__ContextSwitch(*runTh, nextTh);
		}
		sleep(TIMESLICE);
	}
}

// pCurThread is running(in 1st node), pNewThread is next queue.(in 2nd node)
void __ContextSwitch(Thread pCurThread, Thread* pNewThread)
{
	printf("%u , %u\n", pCurThread.tid, pNewThread->tid);

	printf("hello?\n");
	// sleep Current Thread(running)
	if( pCurThread.tid != (thread_t)0 )
		pthread_kill(pCurThread.tid, SIGUSR1);

	// wakeup next thread(ready)
	__thread_wakeup(pNewThread);

	printf("context tid : %u, next=%p, prev=%p\n", pCurThread.tid, pCurThread.pNext,pCurThread.pPrev);
	printf("context tid : %u, next=%p, prev=%p\n", pNewThread->tid, pNewThread->pNext,pNewThread->pPrev);

}

