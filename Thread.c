#include "Thread.h"
#include "Init.h"
#include "Scheduler.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <errno.h>

void *__wrapperFunc(void* arg)
{

	void* ret;
	WrapperArg* pArg = (WrapperArg*)arg;
	
	// child waiting until TCB is initialized
	while(__getThread(pthread_self()) == NULL) {
		printf("not yet!\n");
	}
	// child is ready to run & sleep
	__thread_wait_handler(0);
	printf("dddd");

	// Run child function 
	ret = (*pArg->funcPtr)(pArg->funcArg);
	return ret;
}

void __thread_wait_handler(int signo)
{
	Thread* pTh;
	pTh = __getThread(pthread_self());
	pthread_mutex_lock(&(pTh->readyMutex));
	printf("bye Im sleep\n");
	while (pTh->bRunnable == FALSE) {}
	pthread_cond_wait(&(pTh->readyCond), &(pTh->readyMutex));
	pthread_mutex_unlock(&(pTh->readyMutex));
}

int 	thread_create(thread_t *thread, thread_attr_t *attr, void *(*start_routine) (void *), void *arg)
{

	WrapperArg wrapperArg;
	wrapperArg.funcPtr = start_routine;
	wrapperArg.funcArg = arg;

	pthread_create(&thread, attr, __wrapperFunc,&wrapperArg);
	insertAtTail(READY_QUEUE, thread);	// insert readyQ
	
	
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

	printf("add thread : %u\n", thread);

	printf("send signal to thread(%u) SIGUSR1\n", thread);

	
}


int 	thread_join(thread_t thread, void **retval)
{

}


int 	thread_suspend(thread_t tid)
{

}


int	thread_resume(thread_t tid)
{

}




thread_t	thread_self()
{
	return pthread_self();
}	

Thread* __getThread(pthread_t tid)
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

Thread* createNode(pthread_t tid)
{
	Thread* newNode = (Thread*)malloc(sizeof(Thread));

	/* initialize Thread struct */
	newNode->status = THREAD_STATUS_READY;
	newNode->tid = tid;
	newNode->parentTid = pthread_self();
	pthread_cond_init(&(newNode->readyCond), NULL);
	newNode->bRunnable = 0;
	pthread_mutex_init(&(newNode->readyMutex), NULL);
	newNode->pNext = NULL;
	newNode->pPrev = NULL;

	return newNode;
}


void	insertAtTail(Queue queue, pthread_t tid)
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

Thread* searchQueue(Queue queue, pthread_t tid)
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
		printf(" *  Prev : %p,  \tNext : %p,     \ttid: %d\n *  status : %d,  \tbRunnable : %d\n",  temp->pPrev, temp->pNext, temp->tid, temp->status, temp->bRunnable);
		temp = temp->pNext;
		i++;
	}
	printf("\n");
}

