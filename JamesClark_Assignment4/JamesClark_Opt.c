#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define MAX_FRAMES 7
#define REFERENCE_SIZE 20

int numPageFaults = 0;

int findNextTime(int passedArray[], int startingIndex, int numPassed);
int findMaxIndex (int lookAheadPassed []);
int searchList (int framesPassed [], int valuePassed);
int startBegining (int framesPassed[], int referencePassed []);

int main (void)
{

	int i;
	int searchCheck;
	int h;
	int p;
	
	int frames[MAX_FRAMES];
	int finder;
	int myNum;
	int maxIndex;
	int lookAhead[MAX_FRAMES];

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
	int startingPoint = startBegining(frames, randomReference);

	printf("\nBegining\n");
	for(h = 0; h < MAX_FRAMES; ++h)
	{
		printf(" %d ", frames[h]);
	}

	/*Starting Loop through Random String after Frames has been Initialized*/	
	for (i = startingPoint ; i < REFERENCE_SIZE; ++i)
	{
			
			int indexCheck = -1;
			/*Searching if Value is already in the Frame*/
			searchCheck = searchList(frames, randomReference[i]);
			
			/*If it's not in Frame Then*/
			if (searchCheck == -1)
			{	
				++numPageFaults;
				/*Getting Values for Length for when Each Number Appears Again*/
				for(p = 0; p < MAX_FRAMES; ++p)
				{
					lookAhead[p] = findNextTime(randomReference, i, frames[p]);
					
					/*If the Value Doesn't appear again Then Might as well get rid of that*/	
					if (lookAhead[p] == -1)
					{
						maxIndex = p;
						indexCheck = 0;
					}
				}

				/*When All Values appear Again must choose the longest Distance*/	
				if (indexCheck != 0)
				{
					maxIndex = findMaxIndex(lookAhead);
					
				}
				frames[maxIndex] = randomReference[i];
			
			}// end if search check == -1
				
			
			printf("\nNew Frame List\n");
			for (h = 0; h < MAX_FRAMES; ++h)
			{
				printf(" %d ", frames[h]);
			}
		
		}
	

	printf("\n\nNUM PAGE FAULTS: %d\n", numPageFaults);
}//end main

/*Simple Sequential Search for if Values in Frames*/
/*No sense in Sorting Something this small*/
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

/*Finds Which Index holds the Maximum Index of Occuring again*/
int findMaxIndex (int lookAheadPassed [])
{
	int max = lookAheadPassed[0];
	int maxIndex = 0;
	int j;
	for (j = 0; j < MAX_FRAMES; ++j)
	{
		if (lookAheadPassed[j] > max)
		{
			max = lookAheadPassed[j];
 			maxIndex = j;
		}
	}
	return maxIndex;
}

/*Finds What Index of Reference String a Value Appears Again*/
/*Starting from It's Current Position*/
int findNextTime(int passedArray[], int startingIndex, int numPassed)
{
	int j = REFERENCE_SIZE;
	int k = startingIndex;
	int holder;
	while (k < j)
	{
		holder = passedArray[k];
		if (holder == numPassed)
		{
			return k;
		}
	++k;
	}
	return -1;
}

/*Routine to Deal with Initializing Frames*/
/*Want to Make sure Values don't Repeat in the Initial Frame*/
int startBegining(int framesPassed [], int referencePassed[])
{
	int i = 0;
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

