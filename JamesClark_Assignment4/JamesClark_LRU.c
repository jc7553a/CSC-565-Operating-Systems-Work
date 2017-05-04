#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define MAX_FRAMES 7
#define REFERENCE_SIZE 20

int numPageFaults = 0;

int findPreviousTime(int passedArray[], int tracker, int numPassed);
int findMinIndex (int lookBehindPassed []);
int searchList (int framesPassed [], int valuePassed);
int startBegining(int framesPassed [], int referencePassed[]);

int main (void)
{

	int i;
	int searchCheck;
	int h;
	int p;

	
	int frames[MAX_FRAMES];
	int finder;
	int myNum;
	int minIndex;
	int lookBehind[MAX_FRAMES];

	/*Using Time as a Seed for Random Number Generator*/
	time_t t;
	srand((unsigned)time(&t));
	

	static int  randomReference [REFERENCE_SIZE];

	/*Initializing Reference String with Values 0-9*/
	printf("Reference\n");
	for (i = 0; i < REFERENCE_SIZE; ++i)
	{
		randomReference[i] = (int)(rand()%10);
		printf(" %d ", randomReference[i]);

	}
		
	/*Making sure Frames has no garbage in it*/
	for (i =0; i < MAX_FRAMES; ++i)
	{
		frames[i] = -1;
	}

	/*Initializing Frames can be Tricky if Repititions at begining of Random String*/
	int startingPoint = startBegining (frames, randomReference);

	printf("\nBegining\n");
	for(h = 0; h < MAX_FRAMES; ++h)
	{
		printf(" %d ", frames[h]);
	}


	/*Starting Loop through Random String after Frames has been Initialized*/
	for (i = startingPoint; i < REFERENCE_SIZE; ++i)
	{	

			/*Searching if Value is already in the Frame*/
			searchCheck = searchList(frames, randomReference[i]);

			/*If it's not in Frame Then*/
			if (searchCheck == -1)
			{	
				++numPageFaults;

				/*Getting Values for Length for when Each Number Appeared Previously*/
				for(p = 0; p < MAX_FRAMES; ++p)
				{
					lookBehind[p] = findPreviousTime(randomReference, i, frames[p]);
					
				}
			
			/*Find Which Value was the Farthest Away*/
			minIndex = findMinIndex(lookBehind);
			
			frames[minIndex] = randomReference[i];
			
			}// end if search check == -1
				
			/*Printing Each Frame Every Step*/
			printf("\nNew Frame List\n");
			for (h = 0; h < MAX_FRAMES; ++h)
			{
				printf(" %d ", frames[h]);
			}
		
		
	}

	printf("\n\nNUM PAGE FAULTS: %d\n", numPageFaults);
}//end main

/*Simple Sequential Search */
int searchList (int framesPassed [], int valuePassed)
{
	int i;
	for (i = 0; i < MAX_FRAMES; ++i)
	{
		if (framesPassed[i] == valuePassed)
			{
				return 0;
			}
	}
	return -1;
}

/*Finding Which Value is Smallest Which means*/
/*That It Appeared At an Earlier Index of Reference String*/
int findMinIndex (int lookBehindPassed [])
{
	int min = lookBehindPassed[0];
	int minIndex = 0;
	int j;
	for (j = 0; j < MAX_FRAMES; ++j)
	{
		if (lookBehindPassed[j] < min)
		{
			min = lookBehindPassed[j];
 			minIndex = j;
		}
	}
	return minIndex;
}

/*Routine To Find How Far Away A Value had Previously Occured*/
int findPreviousTime(int referencePassed[], int tracker, int numPassed)
{
	int numFound = 0;
	int j = tracker -1;
	while (numFound == 0)
	{
		if(referencePassed [j] == numPassed)
		{
			numFound = 1;
			return j;
		} 	
		--j;
	}
	return -1;
}


/*Routine to Deal with Initializing Frames*/
/*Want to Make sure Values don't Repeat in the Initial Frame*/
int startBegining(int framesPassed [], int referencePassed[])
{
	int i = 0;
	int valToPassBack = 0;
	int mySearch;
	int movingVal = 0;
	while ( i< MAX_FRAMES)
	{
		/*Search if Value is already in Frames*/
		mySearch = searchList(framesPassed, referencePassed[movingVal]);

		/*If it's not then stick it in Frames*/
		if(mySearch == -1)
		{
			
			framesPassed[i] = referencePassed[movingVal];	
			++numPageFaults;
			++i;
			++movingVal;
		}
		else{
		/*If not then that means that value is already in Frames*/
		/*Don't want to have Same value Repeat in Frame Begining*/

		++movingVal;
		}
		
	}
	/*Return the Index Thats been Going through the Random String*/
	return movingVal;
}


