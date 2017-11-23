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
Thread* createNode(pthread_t tid)
{
	Thread* newNode = (Thread*)malloc(sizeof(Thread));
	newNode->tid = tid;
	return newNode;
}

void	insertAtTail(Thread** head, pthread_t tid)
{
	Thread* temp = *head;
	Thread* newNode = createNode(tid);
	if(*head == NULL)
	{
		*head = newNode;
		return;
	}
	while(temp->pNext != NULL)
		temp=temp->pNext;
	temp->pNext = newNode;
	newNode->pPrev = temp;
}

void deleteAtFirst(Thread** head)
{
	Thread* temp = *head;
	if(*head == NULL)
		return;
	(*head)->pNext = ((*head)->pNext)->pNext;
	free(temp->pNext);
	return;
}

void print(Thread** head)
{
	Thread* temp = *head;
	printf("Head  (%p) > ", *head);
	int i=0;
	while(temp != NULL)
	{
		if( i != 0)
			printf("node%2d(%p) > ",i, temp);
		printf("Prev : %p,  \tNext : %p\n",  temp->pPrev, temp->pNext);
		temp = temp->pNext;
		i++;
	}
	printf("\n");
}
