#include "Thread.h"
#include "Init.h"
#include "Scheduler.h"

/* head and tail pointers for ready queue */ 
ReadyQHead = NULL;
ReadyQTail = NULL;

/* head and tail pointers for waiting queue */
WaitQHead = NULL;
WaitQTai = NULL;


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

void	insertAtTail(Thread* head, pthread_t tid)
{
	Thread* temp = head;
	Thread* newNode = createNode(tid);
	if(head == NULL)
	{
		head = newNode;
		return;
	}
	while(temp->next != NULL)
		temp=temp->next;
	temp->next = newNode;
	newNode->prev = temp;

}
