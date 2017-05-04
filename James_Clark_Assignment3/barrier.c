#include "barrier.h"
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/* Creating 2 Semaphores one for Blocking
	Another for Counting*/
sem_t mySem;
sem_t countSem;

void *worker (void *param);
void wait_for_others(void);

/* Initializing Semaphores*/
int barrier_init(int x){
	
	sem_init(&countSem, 0, 4);
	return sem_init(&mySem, 0, 0);
}

void wait_for_others(void){
	
	
	int value;
	
	/* Getting Value of Counting Semaphore*/
	sem_getvalue(&countSem, &value);

	/* Check Counting Semaphore Value if it has reached 0 then it's time to release Threads*/
	/* Threads are being Blocked on mySem until counting Semaphore has reached 0 */
	if (value >0)
	{
		sem_wait(&countSem);
		sem_wait(&mySem);
		
	}
	else
	{
		/* Incrementing countSemaphore back up and Releasing Blocked Threads from mySem */
		while (value < 5)
		{	
			sem_post(&mySem);
			sem_post(&countSem);
			sem_getvalue(&countSem, &value);
		}
	}

	
	

}

void *worker(void *param)
{
	/* Printing A going to the Barrier then Printing B */
	printf("A\n");
	//sleep(1);
	wait_for_others();	

	printf("B\n");
	
}

	
	
		