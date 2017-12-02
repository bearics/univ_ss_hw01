#include "Init.h"
#include "Thread.h"
#include <stdlib.h>

void Init(void)
{
	pthread_mutex_init(&mainMutex, NULL);
	pthread_cond_init(&mainCond, NULL);

	runStop = 0;
}
