#include "Thread.h"
#include "Init.h"
#include "Scheduler.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <errno.h>
void runScheduler_resume();


void __thread_wait_handler(int signo);

void *__wrapperFunc(void* arg)
{

	void* ret;
	WrapperArg* pArg = (WrapperArg*)arg;
	//printf("self : %u\n", pthread_self());
	
	int retSig;
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	signal(SIGUSR1, __thread_wait_handler);
	
	// child waiting until TCB is initialized
	while(__getThread(pthread_self()) == NULL) {
	//	printf("not yet!\n");
	}
	// child is ready to run & sleep
	__thread_wait_handler(0);
	//printf("i'm wakeup at %u\n", pthread_self());
	// Run child function 
	ret = (*(pArg->funcPtr))(pArg->funcArg);
	free(arg);
	printf("byebye\n");
	return ret;
}

void __thread_wakeup(Thread* pTh)
{
	printf("wake up tid : %u \n", pTh->tid);
	pthread_mutex_lock(&(pTh->readyMutex));
	pTh->bRunnable = TRUE;
	pthread_cond_signal(&(pTh->readyCond));
	pthread_mutex_unlock(&(pTh->readyMutex));
}

void __thread_wait_handler(int signo)
{
	Thread* pTh;
	pTh = __getThread(pthread_self());
	pthread_mutex_lock(&(pTh->readyMutex));
	//printf("dd?? %d, %u\n",pTh->bRunnable, pthread_self());
	while (pTh->bRunnable == FALSE){
		//printf("bye Im sleep tid : %u \n", pTh->tid);
		pthread_cond_wait(&(pTh->readyCond), &(pTh->readyMutex));
	}
	//printf("fin wait\n");
	pthread_mutex_unlock(&(pTh->readyMutex));
}

int 	thread_create(thread_t *thread, thread_attr_t *attr, void* (*start_routine) (void *), void *arg)
{
	//printf("child1 : %d\n", start_routine);

	WrapperArg* wrapperArg=(WrapperArg*)malloc(sizeof(WrapperArg));
	wrapperArg->funcPtr = start_routine;
	wrapperArg->funcArg = arg;

	pthread_create(thread, attr, __wrapperFunc,wrapperArg);
	insertAtTail(READY_QUEUE, *thread);	// insert readyQ
	//sleep(2);
		
/*
	int status = pthread_kill(thread,SIGUSR1);	// wake child function
    if ( status == ESRCH ) {
            printf("Thread ID[%d] not exist..\n", thread);
            return 0;
    } else if ( status == EINVAL ) {
            printf("Thread ID[%d] is yet alive\n", thread);
    }  else {
            printf("Thread ID[%d] is yet alive\n", thread);
    }
*/	
}


int 	thread_join(thread_t tid, void **retval)
{
	Thread* pTR = searchQueue(READY_QUEUE, tid);
	Thread* pTW = NULL;
	
	//pTh->status = THREAD_STATUS_READY;
	// insertAtTail(WAITING_QUEUE, tid);
	// pTW = searchQueue(WAITING_QUEUE, tid);
	// copyNode(pTR, pTW);
	// deleteAtFirst(READY_QUEUE);

	// sleep
	pTR->bRunnable = FALSE;
	__thread_wait_handler(0);

	//wake up


}

int 	thread_exit(void **retval)
{
	//Thread* pTh = __getThread(tid);
	//	pTh->status = THREAD_STATUS_READY;

}


int 	thread_suspend(thread_t tid)
{
	printf("%p, %p\n", &mainMutex, &mainCond);
	if(searchQueue(READY_QUEUE, tid) == NULL)
		return -1; // no tid

	runStop = 1;
	pthread_mutex_lock(&mainMutex);

	if(__getThread(tid)->bRunnable == TRUE){
		runScheduler_resume();
		return -1;	// running thread cannot suspend
	}
	
	insertAtTail(WAITING_QUEUE, tid);
	
	Thread* readyNode = searchQueue(READY_QUEUE, tid);	// find TCB in waiting queue
	Thread* waitNode = searchQueue(WAITING_QUEUE, tid);	// find TCB in waiting queue

	if(readyNode == NULL || waitNode == NULL ){
		runScheduler_resume();
		return -1; // fail to find tid in Q
	}

	copyNode(readyNode,waitNode); // copy Node
	waitNode->status = THREAD_STATUS_BLOCKED;
	
	if(deleteNode(READY_QUEUE, tid) < 0 ){
		runScheduler_resume();
		return -1;	// fail to delete node
	}

	runScheduler_resume();
	return 0;	// success!

}


int	thread_resume(thread_t tid)
{
	if(searchQueue(WAITING_QUEUE, tid) == NULL)
		return -1; // no tid
	insertAtTail(READY_QUEUE, tid);
	runStop = 1;
	pthread_mutex_lock(&mainMutex);
	Thread* readyNode = searchQueue(READY_QUEUE, tid);	// find TCB in waiting queue
	Thread* waitNode = searchQueue(WAITING_QUEUE, tid);	// find TCB in waiting queue

	if(readyNode == NULL || waitNode == NULL )
	{
		runScheduler_resume();
		return -1; // fail to find tid in Q
	}

	copyNode(waitNode, readyNode); // copy Node
	readyNode->status = THREAD_STATUS_BLOCKED;

	if(deleteNode(WAITING_QUEUE, tid) < 0 )
	{
		runScheduler_resume();
		return -1;	// fail to delete node
	}
	runScheduler_resume();
	return 0;	// success!
}

thread_t	thread_self()
{
	return pthread_self();
}	

Thread* __getThread(thread_t tid)
{
	return searchQueue(READY_QUEUE, tid);
}

/* doubly linked list functions */
Thread**	selectQHead(Queue queue)
{
	if( queue == READY_QUEUE )
		return &ReadyQHead;
	else if(queue == WAITING_QUEUE)
		return &WaitQHead;
}

Thread**	selectQTail(Queue queue)
{
	if( queue == READY_QUEUE )
		return &ReadyQTail;
	else if(queue == WAITING_QUEUE)
		return &WaitQTail;
}

Thread* createNode(thread_t tid)
{
	Thread* newNode = (Thread*)malloc(sizeof(Thread));

	/* initialize Thread struct */
	newNode->status = THREAD_STATUS_READY;
	newNode->pExitCode = (void*)0;
	newNode->tid = tid;
	newNode->parentTid = pthread_self();
	pthread_cond_init(&(newNode->readyCond), NULL);
	newNode->bRunnable = FALSE;
	pthread_mutex_init(&(newNode->readyMutex), NULL);
	newNode->pNext = NULL;
	newNode->pPrev = NULL;

	return newNode;
}


void	insertAtTail(Queue queue, thread_t tid)
{
	Thread** pHead = selectQHead(queue);
	Thread** pTail = selectQTail(queue);
	Thread* newNode = createNode(tid);
	if(*pHead == NULL)
	{
		*pHead = newNode;
		return;
	}
	Thread* temp = *pHead;
	while(temp->pNext != NULL)
		temp=temp->pNext;
	temp->pNext = newNode;
	newNode->pPrev = temp;
	*pTail = newNode;

	return;
}

int deleteNode(Queue queue, thread_t tid)
{
	Thread** pHead = selectQHead(queue);
	Thread** pTail = selectQTail(queue);
	Thread* cur = *pHead;
	Thread* pre = NULL;

	if( *pHead == NULL )
		return 0;

	while(cur->tid != tid)
	{
		if(cur->pNext == NULL)
			return -1;	// can't find tid
		else
		{
			pre = cur;	// save current node
			cur = cur->pNext;
		}
	}

	if(cur == *pHead)
		*pHead = (*pHead)->pNext;
	else
		cur->pPrev->pNext = cur->pNext;

	if(cur == *pTail)
		*pTail = cur->pPrev;
	else
		cur->pNext->pPrev = cur->pPrev;

	free(cur);	// delete node(tid)
	return 0;
}

void deleteAtFirst(Queue queue)
{
	Thread** pHead = selectQHead(queue);
	Thread** pTail = selectQTail(queue);
	Thread* temp = *pHead;
	if(*pHead == NULL)	// no one to delete
		return;
	(*pHead) = (*pHead)->pNext;
	if(*pHead == NULL)
	{
		*pTail = NULL;
		return;
	}
	(*pHead)->pPrev = NULL;
	free(temp);
	return;
}

void copyNode(Thread* sour, Thread* dest)
{
	Thread* next = dest->pNext;
	Thread* prev = dest->pPrev;
	memcpy(dest, sour, sizeof(Thread));
	dest->pNext = next;
	dest->pPrev = prev;

}

Thread* searchQueue(Queue queue, thread_t tid)
{
	Thread** pHead = selectQHead(queue);
	Thread* temp = *pHead;
	while(temp != NULL)
	{
		if(temp->tid == tid)
			break;
		temp=temp->pNext;
	}
	return temp;
}

void runScheduler_resume()
{

	pthread_cond_signal(&mainCond);
	pthread_mutex_unlock(&mainMutex);
	runStop = 0;
	return;
}

void runScheduler_stop()
{

}

void print(Queue queue)
{
	Thread** pHead = selectQHead(queue);
	Thread** pTail = selectQTail(queue);
	Thread* temp = *pHead;
	printf("\n----------------------------QUEUE LIST----------------------------\n");
	printf("\n\tHead(%p)\t\t Tail(%p)\n", *pHead, *pTail);
	int i=0;
	while(temp != NULL)
	{
		printf("\nnode%2d(%p) ------------------------------------------------\n",i, temp);
		printf(" *  Prev : %p,  \tNext : %p,     \ttid: %u\n",  temp->pPrev, temp->pNext, temp->tid);
		printf(" *  status : %d,  \tbRunnable : %d\n", temp->status, temp->bRunnable);
		temp = temp->pNext;
		i++;
	}
	printf("\n");
}

