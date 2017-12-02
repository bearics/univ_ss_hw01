#include "TestCase.h"
#include "Thread.h"
#include "Init.h"
#include "Scheduler.h"
#include <stdio.h>


void* child1(void *arg) {
	int i=0;
	while(i<5){
		printf("child 1\n");
		sleep(1); 
		i++;
	}
	return NULL;
}

void* child2(void *arg) {
	int i=0;
	while(i<5){
		printf("child 2\n");
		sleep(1);
		i++;
	}
	return NULL;
}

void* child3(void *arg) {
	int i=0;
	while(i<5){
		printf("child 3\n");
		sleep(1);
		i++;
	}
	return NULL;
}


void TestCase(void)
{
	thread_t tid1, tid2, tid3;
	int arg1, arg2, arg3;
	
	printf("testcase main : %u\n", pthread_self());


	thread_create(&tid1, NULL, child1, &arg1);
	thread_create(&tid2, NULL, child2, &arg2);
	thread_create(&tid3, NULL, child3, &arg3);

	print(READY_QUEUE);
	sleep(2);
	printf("suspend!!!!!!!!\n");
	thread_suspend(tid1);
	sleep(2);
		print(READY_QUEUE);
	printf("suspend22!!!!!!!!\n");

	thread_suspend(tid2);
	sleep(2);
	print(READY_QUEUE);

	// printf("resume!!!!!!!!!!\n");	
	// thread_resume(tid1);

	// sleep(2);


	while(1)
	{
		print(READY_QUEUE);
		sleep(1);
	}
}