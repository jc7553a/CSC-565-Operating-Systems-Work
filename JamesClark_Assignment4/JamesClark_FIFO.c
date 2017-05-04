#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define MAX_FRAMES 7
#define REFERENCE_SIZE 20

int numPageFaults = 0;

int searchList (int framesPassed [], int valuePassed);
int startBegining(int framesPassed [], int referencePassed[]);

int main (void)
{
	int i;
	int h;
	int searchCheck;
	int frames[MAX_FRAMES];
	
	/*FIFO Looper*/
	int myLooper =0;
	/* Using Time as a Seed for Random Generator*/
	time_t t;
	srand((unsigned)time(&t));

	static int  randomReference [REFERENCE_SIZE];

	/*Filling up Random String */
	for (i = 0; i < REFERENCE_SIZE; ++i)
	{
		randomReference[i] = (int)(rand()%10);
		printf(" %d ", randomReference[i]);
	}

	/*Making sure no Garbage in Frames*/
	for (i =0; i < MAX_FRAMES; ++i)
	{
		frames[i] = -1;
	}
		
	/*Initializing Frames can Be Tricky if there is Repititions in Random String*/
	int startingPoint = startBegining(frames, randomReference);

	/*Printing out Frames Once it has been Initialy Filled*/
	printf("\nBegining\n");
	for(h = 0; h < MAX_FRAMES; ++h)
	{
		printf(" %d ", frames[h]);
	}
	
	/*Start Loop Through Random String*/
	for (i = startingPoint ; i < REFERENCE_SIZE; ++i)
	{
		/*Make Sure Value is not already in the Frame*/
		searchCheck = searchList(frames, randomReference[i]);
		if (searchCheck == -1)
			{	
				++numPageFaults;
				/*Make Sure to reset Looper when it's reached it's max*/
				if (myLooper == MAX_FRAMES)
				{
					myLooper = 0;
				}
				frames[myLooper] = randomReference[i];
				++myLooper;
			}

		/*Printing out the Frames at each Step*/
		printf("\nNew Frame List\n");
		for (h = 0; h < MAX_FRAMES; ++h)
		{
			printf(" %d ", frames[h]);
		}
	}


printf("\n\nNUM PAGE FAULTS: %d\n", numPageFaults);


}//end main


/*Sequential Search to see if a Value Exists in Frames Already*/
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

/*To Make Sure Initialization of Frames is done without Error*/

int startBegining(int framesPassed [], int referencePassed[])
{
	int i = 0;
	int mySearch;
	int movingVal = 0;
	while ( i< MAX_FRAMES)
	{	
		/*Making sure there is not already that Val in the Frames*/
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