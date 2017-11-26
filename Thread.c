#include "Thread.h"
#include "Init.h"
#include "Scheduler.h"
#include <stdlib.h>
#include <stdio.h>


int 	thread_create(thread_t *thread, thread_attr_t *attr, void *(*start_routine) (void *), void *arg)
{

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
	newNode->pNext = NULL;
	newNode->pPrev = NULL;
	newNode->tid = tid;
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
	Thread* temp = *pHead;
	if(*pHead == NULL)
		return;
	(*pHead) = (*pHead)->pNext;
	(*pHead)->pPrev = NULL;
	free(temp);
	return;
}

void print(Queue queue)
{
	Thread** pHead = selectQHead(queue);
	Thread** pTail = selectQTail(queue);
	Thread* temp = *pHead;
	printf("Head(%p)\t Tail(%p)\n", *pHead, *pTail);
	int i=0;
	while(temp != NULL)
	{
		printf("node%2d(%p) > ",i, temp);
		printf("Prev : %p,  \tNext : %p\n",  temp->pPrev, temp->pNext);
		temp = temp->pNext;
		i++;
	}
	printf("\n");
}