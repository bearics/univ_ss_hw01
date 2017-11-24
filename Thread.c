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
Thread**	selectQueue(Queue queue)
{
	if( queue == READY_QUEUE )
		return &ReadyQHead;
	else if(queue == WAITING_QUEUE)
		return &WaitQHead;
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
	Thread** pHead = selectQueue(queue);
	Thread* newNode = createNode(tid);
	if(*pHead == NULL)
	{
		*pHead = newNode;
		newNode->pPrev = *pHead;
		return;
	}
	Thread* temp = *pHead;
	while(temp->pNext != NULL)
		temp=temp->pNext;
	temp->pNext = newNode;
	newNode->pPrev = temp;
}

void deleteAtFirst(Queue queue)
{
	Thread** head;
	if( queue == READY_QUEUE )
		head = &ReadyQHead;
	else if(queue == WAITING_QUEUE)
		head = &WaitQHead;
	Thread* temp = *head;
	if(head == NULL)
		return;
	(*head)->pNext = ((*head)->pNext)->pNext;
	free(temp->pNext);
	return;
}

void print(Queue queue)
{
	Thread** pHead = selectQueue(queue);

	printf("Head  (%p) > ", *pHead);
	int i=0;
	while(*pHead != NULL)
	{
		if( i != 0)
			printf("node%2d(%p) > ",i, pHead);
		printf("Prev : %p,  \tNext : %p\n",  (*pHead)->pPrev, (*pHead)->pNext);
		(*pHead) = (*pHead)->pNext;
		i++;
	}
	printf("\n");

}