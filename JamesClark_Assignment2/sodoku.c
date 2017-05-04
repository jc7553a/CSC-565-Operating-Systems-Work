#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 9
#define NUM_THREADS 11

int sodoku[SIZE][SIZE] = {{6,2,4,5,3,9,1,8,7},{5,1,9,7,2,8,6,3,4},{8,3,7,6,1,4,2,9,5},
		{1,4,3,8,6,5,7,2,9},{9,5,8,2,4,7,3,6,1},{7,6,2,3,9,1,4,5,8},
		{3,7,1,9,5,6,8,4,2},{4,9,6,1,8,2,5,7,3},{2,8,5,4,7,3,9,1,6}};
int flagArray[NUM_THREADS];

struct data
{
	int row;
	int column;
	int arrayPos;
};

struct data dataArray[NUM_THREADS];
void *checkColumns(void *param);
void *checkRows(void *param);
void *checkSquares(void *param);

int main(int argc, char *argv[])
{
	int z;
	
	/*Set up Flag with 0's*/
	for (z = 0; z < NUM_THREADS; ++z)
	{
		flagArray[z] = 0;
	}

	int val;
	srand(time(NULL));
	int i, j;

	/* Create Random Sodoku With Digits 1-9 */
	/*
	for (i =0; i <SIZE; ++i)
	{
		j = 0;
		while (j < SIZE)
		{
			val = rand()%10;
			if (val ==0)
			{
				--j;
			}
			else
			{
				sodoku[i][j] = val;
				++j;
			}
		}
	}
	*/

	/*PRINTING OUT THE SODOKU PUZZLE*/
	printf("\n\n");
	printf("Your Sodoku Puzzle Looks Like:\n");
	printf("\n\n");
	for (i =0; i <SIZE; ++i)
	{
		printf("\t");
		for (j =0; j <SIZE; ++j)
		{
		printf("%d ", sodoku[i][j]);
		}
	printf("\n");
	}
		

	/*SETTING UP ARRAY OF Threads*/
	pthread_attr_t attr;
	pthread_t workers[NUM_THREADS];
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
	

	/*CREATE INITIAL 2 THREADS*/
	/*ONE WITH DO ROWS OTHER WILL DO COLUMNS*/
	pthread_create(&workers[0], &attr, checkColumns, (void*)0);
	pthread_create(&workers[1], &attr, checkRows, (void*)1);

	int x;
	int rows = 0;
	int columns = 0;
 	int weir = 0;

	/*CREATING THREADS THAT WILL CHECK THE SQUARES*/
	for (x = 2; x < NUM_THREADS; ++x)
	{

		dataArray[weir].row = rows;
		dataArray[weir].column =columns;
		dataArray[weir].arrayPos = x-2;
		weir = weir +1;
		pthread_create(&workers[x], &attr, checkSquares,(void *) &dataArray[weir]);
		if (x ==3)
		{
			columns = 3;
		}
		columns = columns + 3;
		if (columns ==9)
		{
			columns = 0;
			rows = rows+3;
		}	
	}
	

	/*WAITING FOR ALL THREADS TO BE DONE AND JOIN BACK*/
	int a;
	for (a = 0; a <NUM_THREADS; ++a)
	{
		pthread_join(workers[a], NULL);
	}



	/*SUM THE FLAG ARRAY*/
	/*IF FLAG ARRAY = -11 WE KNOW EVERYTHING PASSED THE TEST*/

	int b;
	int sumFlag=0;
	printf("\n\n");
	for(b = 0; b< NUM_THREADS; ++b)
	{
		sumFlag = sumFlag + flagArray[b];
	}

	if(sumFlag == -11)
	{
		printf("\tSODOKU!");
	}
	else
	{
		printf("\tNOT SODOKU!");
	}		
	printf("\n");

return 0;
}


/*FUNCTION FOR 1 THREAD TO CHECK COLUMNS*/
void *checkColumns(void *param)
{
	int checkArray[SIZE];
	int tempArray[SIZE];
	int i, j, temp, k, t, q, w;
	for (k = 0; k < SIZE; ++k)
	{
		tempArray[k] = 0;
		checkArray[k] = 0;
	}

	/*GOING THROUGH COLUMNS MAKING SURE ALL VALUES THERE*/
	/*WE PUT -1 INTO CORRESPONDING INDEX OF TEMPARRAY FOR NUMBER*/
	int sum = 0;
	for (i = 0; i <SIZE; ++i)
	{
		for (j=0; j<SIZE; ++j)
		{
			temp = sodoku[j][i];
			switch(temp)
			{
				case(1):
					tempArray[0] = -1;
				break;
				case(2):
					tempArray[1] = -1;
				break;
				case(3):
					tempArray[2] = -1;
				break;
				case(4):
					tempArray[3] = -1;
				break;
				case(5):
					tempArray[4] = -1;
				break;
				case(6):
					tempArray[5] = -1;
				break;
				case(7):
					tempArray[6] = -1;
				break;
				case(8):
					tempArray[7] = -1;
				break;
				case(9):
					tempArray[8] = -1;
				break;

			}//end switch
		}//end row

	/*IF AT THE END SUM OF TEMPARRAY = -9*/
	/*THEN WE KNOW THE COLUMN HAD ALL DIGITS NEEDED*/	
		for (t = 0; t <SIZE; ++t)
		{
			sum = sum + tempArray[t];
			tempArray[t] = 0;
		}
	/*IF PREVIOUS PASSES WE PUT -1 IN CORRESPONDING ROW INDEX OF checkArray*/
		if(sum == -9)
		{
			checkArray[i] = -1;
		}
		sum = 0;
	}//end column
	
	for(q = 0; q < SIZE; ++q)
	{
		sum = sum + checkArray[q];
	}


	/*IF PASSES ALL THE TESTS PUT -1 IN THREAD NUMBER INDEX FOR FLAG ARRAY*/
	/*I.E. THREAD 1 GOES TO FLAGARRAY 1ST POSITION */
	if (sum == -9)
	{
		flagArray[0] = -1;
	}


}// end Check Column


/*START OF CHECKING THE ROWS*/
/*ESSENTIALY SAME ALGORITHM AS CHECK COLUMN*/
void *checkRows(void *args)
{
	int checkArray[SIZE];
	int tempArray[SIZE];
	int i, j, temp, k, t, q, w;
	for (k = 0; k < SIZE; ++k)
	{
		tempArray[k] = 0;
		checkArray[k] = 0;
	}
	int sum = 0;
	for (i = 0; i <SIZE; ++i)
	{
		for (j=0; j<SIZE; ++j)
		{
			temp = sodoku[i][j];
			switch(temp)
			{
				case(1):
					tempArray[0] = -1;
				break;
				case(2):
					tempArray[1] = -1;
				break;
				case(3):
					tempArray[2] = -1;
				break;
				case(4):
					tempArray[3] = -1;
				break;
				case(5):
					tempArray[4] = -1;
				break;
				case(6):
					tempArray[5] = -1;
				break;
				case(7):
					tempArray[6] = -1;
				break;
				case(8):
					tempArray[7] = -1;
				break;
				case(9):
					tempArray[8] = -1;
				break;

			}//end switch
		}//end row
			
			for (t = 0; t <SIZE; ++t)
			{
				sum = sum + tempArray[t];
				tempArray[t] = 0;
			}
			if(sum == -9)
			{
				checkArray[i] = -1;
			}
			sum = 0;
	}//end column
	
	for(q = 0; q < SIZE; ++q)
	{
		sum = sum + checkArray[q];
	}

	if (sum == -9)
	{
		flagArray[1] = -1;
	}


}// end Check Row

/*START OF CHECKING ALL 9 SQUARES*/
void *checkSquares(void *dataPassed)
{
	/*BRING IN PASSED ARGUMENTS*/
	struct data *dataGiven;
	dataGiven = (struct data *) dataPassed;
	int checkNum = 0;
	int rowPassed;
	int tempArray[SIZE];
	int i, j, temp, k, t, q, w;

	/*THIS IS HOW WE KNOW WHICH SQUARE TO CHECK*/
	rowPassed = dataGiven->row;
	int columnPassed = dataGiven->column;
	int arrayPos = dataGiven->arrayPos;
	
	for (k = 0; k < SIZE; ++k)
	{
		tempArray[k] = 0;
	}

	int sum = 0;
	
	
	/*SIMILAR ALGORITHM TO CHECK COLUMNS*/

	for (i = rowPassed; i <rowPassed+3; ++i)
	{
		for (j=columnPassed; j<columnPassed+3; ++j)
		{
			temp = sodoku[i][j];
			switch(temp)
			{
				case(1):
					tempArray[0] = -1;
				break;
				case(2):
					tempArray[1] = -1;
				break;
				case(3):
					tempArray[2] = -1;
				break;
				case(4):
					tempArray[3] = -1;
				break;
				case(5):
					tempArray[4] = -1;
				break;
				case(6):
					tempArray[5] = -1;
				break;
				case(7):
					tempArray[6] = -1;
				break;
				case(8):
					tempArray[7] = -1;
				break;
				case(9):
					tempArray[8] = -1;
				break;

			}//end switch
	}//end row
			
			
	}//end column
	
	
	
	for (t = 0; t <SIZE; ++t)
	{
		sum = sum + tempArray[t];
	}

	/*NEED TO BE SURE TO ADD 2 TO ARRAY POSITION*/
	/*KEEP IN MIND OF CHECK ROW AND CHECK COLUMN THREADS*/
	if (sum == -9)
	{
		flagArray[arrayPos+2] = -1;
	}

}//end check squares
