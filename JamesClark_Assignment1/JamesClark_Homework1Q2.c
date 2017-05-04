#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>



/* Main*/

int main()
{
int PID = fork();
int parentPID;
int parentPPID;
char * const parmList [] = {"ps"};

/*Error Handling For Child Creation*/
if (PID == -1)
	{
	printf("Error");
	}
	
/*Child Process Code*/
if (PID==0)
	{
	int myPID = getpid();
	int myPPID = getppid();
	printf("My Pid = %d my parent PID = %d\n", myPID, myPPID);
	execl("/bin/ps", "ps", 0,0);
	}

/*Parents Code*/
if (PID > 0)
	{
	wait(0);
	parentPID = getpid();
	parentPPID = getppid();
	printf("\nThe Child Process has finished\n");
	printf("Child Pid = %d, my PID = %d, parent PID = %d\n", PID, parentPID, parentPPID);
	}

return 0;
}//end program