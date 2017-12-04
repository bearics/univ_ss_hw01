#include "Run.h"
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>


void *__wrapperFunc(void* arg)
{
	void* ret;
	WrapperArg* pArg = (WrapperArg*)arg;
	
	int retSig;
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	signal(SIGUSR1, __thread_wait_handler);
	
	while(searchQueue(READY_QUEUE, pthread_self()) == NULL) {} // 
	__thread_wait_handler(0);
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
	pTh = searchQueue(READY_QUEUE, pthread_self());
	pthread_mutex_lock(&(pTh->readyMutex));
	while (pTh->bRunnable == FALSE){
		pthread_cond_wait(&(pTh->readyCond), &(pTh->readyMutex));
	}
	pthread_mutex_unlock(&(pTh->readyMutex));
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

void	insertAtTail(Queue queue, Thread* pth)
{
	Thread** pHead = selectQHead(queue);
	Thread** pTail = selectQTail(queue);

	pth->pNext = NULL;
	pth->pPrev = NULL;

	if(*pHead == NULL)
	{
		*pHead = pth;
		*pTail = pth;
		return;
	}
	
	(*pTail)->pNext = pth;
	pth->pPrev = *pTail;
	*pTail = pth;
	return;
}


Thread*	deleteAtFirst(Queue queue)
{
	Thread** pHead = selectQHead(queue);
	Thread** pTail = selectQTail(queue);
	Thread* temp = *pHead;

	if(*pHead == NULL)
		return NULL;	// nothing to delete
	if(temp->pNext == NULL)
	{
		*pHead = NULL;
		*pTail = NULL;
	}
	else
	{
		*pHead = temp->pNext;
		(*pHead)->pPrev = NULL;
	}
	return temp;
}

Thread* deleteNode(Queue queue, thread_t tid)
{

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

