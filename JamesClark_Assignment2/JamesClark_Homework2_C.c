#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE_ROW 50
#define SIZE_COLUMN 10
#define NUM_THREADS 4

int primeMatrix [50][10];

void *modByTwo(void *param);
void *modByThree(void *param);
void *modByFive(void *param);
void *modBySeven(void *param);

int main(int argc, char *argv[])
{
	void *status;
	
	/*VARIABLES*/
	int i;
	int j;
	int myNum; 
	int x;
	int val = 1;
	int stopRow, stopColumn;

	/*GETTING USER INPUT*/

	printf("Enter Number You want all the primes before, Max Number is 500\n");
	scanf("%d",&myNum);

	
	printf("You entered %d\n", myNum);
	
	/*MUST FIND THE VALUE INPUTTED IN OUT MATRIX*/
	/*DO THIS TO KNOW WHEN TO STOP PRINTING VALUES LATER*/
	stopRow = myNum/10;
	stopColumn = myNum%10;
		

	/*Fill up Matrix with Values*/
	for (i = 0; i < SIZE_ROW; ++i)
	{
		for(j = 0; j <SIZE_COLUMN; ++j)
		{
			primeMatrix[i][j] = val;
			val +=1;
		}
	}

	/*Create Threads*/
	pthread_attr_t attr;
	pthread_t workers [NUM_THREADS];

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

	/*
	if (argc != 2)
		{
			printf("Error");
			return -1;
		}

	if (atoi(argv[1]) < 0)
	{
		printf("Error");
		return -1;
	}
	*/


	/*Create Multiple Threads To Mod Matrix by Different Values*/
	pthread_create(&workers[0], &attr, modByTwo, (void*)0);
	pthread_create(&workers[1], &attr, modByThree, (void*)1);
	pthread_create(&workers[2], &attr, modByFive, (void*)2);
	pthread_create(&workers[3], &attr, modBySeven, (void*)3);
	
	int t;
	
	pthread_attr_destroy(&attr);
	
	/*WAITING FOR ALL THREADS TO BE DONE WORKING AND TO JOIN BACK*/
	for(t = 0; t< NUM_THREADS; t++)
	{
		pthread_join(workers[t], &status);
	}
	
	/*PRINTING OUT THE LIST OF PRIME NUMBERS BEFORE THE GIVEN VALUE*/
	/*MUST BE USE THE STOP ROW AND STOP COLUMN VARIABLES TO MAKE SURE WE END*/

	printf("List of Primes: \n");
	int y;

	/*WE DO THIS BY SETTING A FLAG EQUAL TO -1 WHEN WE KNOW WE ARE FINISHED*/
	
	int flag = 0;
	for (t = 0; t < SIZE_ROW; ++t)
	{
		for(y = 0; y < SIZE_COLUMN; ++y)
		{
			if (t == stopRow && y == stopColumn)
			{
				flag = -1;
			}
			if(primeMatrix[t][y] != 1 && flag != -1)
			{
				printf("%d ", primeMatrix[t][y]);
			}
		}
	}
	printf("\n");

}//END MAIN

/*FUNCTION TO USE TEMP IS CONGRUENT TO 0(MOD2)*/
/*NO NUMBER CAN BE PRIME IF IT IS DIVISIBLE BY 2*/

void *modByTwo( void *param)
{
	int l, k;
	int temp;
	/*SETTING NUMBERS THAT ARE DIVISIBLE BY 2 TO 1*/
	/*DO THIS BECAUSE IN THE END THE NUMBER 1 IS ALSO NOT PRIME*/


	for (l = 0; l < SIZE_ROW ; ++l)
	{
		for(k = 0; k <SIZE_COLUMN; ++k)
		{
			temp = primeMatrix[l][k];
			if (temp != 2 & temp%2 == 0)
			{
				primeMatrix[l][k] = 1;
			}
		}
	}
}// END MOD BY 2


/*FUNCTION TO SEE IF VALUE IS CONGRUENT TO 0(MOD3)*/
/*ALL IDEAS SIMILAR TO MOD2*/
void *modByThree( void *param)
{
	int p, o;
	int temp;
	for (p = 0; p < SIZE_ROW; ++p)
	{
		for(o = o; o <SIZE_COLUMN; ++o)
		{
			temp = primeMatrix[p][o];
			if (temp != 3 & temp%3 == 0)
			{
				primeMatrix[p][o] = 1;
			}
		}
	}
}

/*FUNCTION TO SEE IF VALUE IS CONGRUENT TO 0(MOD5)*/
void *modByFive( void *param)
{
	int q, w;
	int temp;
	for (q = 0; q < SIZE_ROW; ++q)
	{
		for(w = 0; w < SIZE_COLUMN; ++w)
		{
			temp = primeMatrix[q][w];
			if (temp != 5 & temp%5 == 0)
			{
				primeMatrix[q][w] = 1;
			}
		}
	}
}

/*FUNCTION TO SEE IF VALUE IS CONGRUENT TO 0(MOD7)*/
void *modBySeven( void *param)
{
	int e, r;
	int temp;
	for (e = 0; e < SIZE_ROW; ++e)
	{
		for(r = 0; r <SIZE_COLUMN; ++r)
		{
			temp = primeMatrix[e][r];
			if (temp != 7 & temp%7 == 0)
			{
				primeMatrix[e][r] = 1;
			}
		}
	}
}



