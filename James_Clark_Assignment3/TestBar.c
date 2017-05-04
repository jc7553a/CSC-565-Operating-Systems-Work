#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "barrier.h"


int main (int argc, char *argv[])
{
	
	if (argc != 2) 
	{
	fprintf(stderr, "Usage: ./testbarrier<numberofThreads>\n");
	}
	
	int i;
	

	/* Hardcore for Number of Threads*/		
	int number = 5;
	
	pthread_t workers[number];
	
	/* Initializing Barrier Size*/
	if(barrier_init(number) !=0)
	{
		return -1;
	}
	
	/* Creating 5 Threads */
	for ( i = 0; i < number; ++i)
	{
		pthread_create(&workers[i], 0, worker, (void*)0);
	}

	
	/*Joining threads back to complete Program */
	for (i =0; i< number; ++i)
	{
		pthread_join(workers[i], 0);
	}
	
	getchar();
	return 0;
}


