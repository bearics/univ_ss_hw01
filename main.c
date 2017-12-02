#include "Init.h"
#include "Scheduler.h"
#include "Thread.h"
#include "App.h"
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

#define pthread_mutex_t  mainMutex (PTHREAD_MUTEX_INITIALIZER);

int main(void)
{
 	thread_t tid;
 	int arg;

 	Init();

 	pthread_create(&tid, NULL, AppTask, &arg);

 	RunScheduler();
 	sleep(1000);
	

}

