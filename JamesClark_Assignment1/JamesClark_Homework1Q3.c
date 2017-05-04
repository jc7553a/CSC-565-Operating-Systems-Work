#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define BUFFER_SIZE  25

int main(void)
{

/*CREATE FILE DESCRIPTORS*/
int fd[2];
int fd2[2];

/*CREATE STRINGS AND BUFFER*/
const char argToPass[BUFFER_SIZE] = "Hello";
char buffer[BUFFER_SIZE];
const char reverseArg[BUFFER_SIZE] = "hELLO";
char buffer2[BUFFER_SIZE];

/*CREATE PIPES*/
int ret = pipe(fd);
int ret2 = pipe(fd2);
/*CREATE FORK*/
int pid;
pid = fork();

/*ERROR HANDLING FOR PIPES*/
if (ret == -1 | ret2 == -1)
{
	printf("Pipes Failed");

}

/*ERROR HANDLING FOR CHILD CREATION*/
if(pid < 0)
{
	printf("Child Creation Failed!");
}

/* CHILD PROCESS CODE TO SEND INITIAL Hello AND RECIEVE REVERSE hELLO */
if (pid == 0)
{
	close(fd[0]);
	write(fd[1], argToPass, strlen(argToPass)+1);
	close(fd[1]);
	wait();
	close(fd2[1]);
	read(fd2[0], buffer2, BUFFER_SIZE);
	close(fd[0]);
	printf("Reverse: %s   ", buffer2);
	
}// end pid == 0


/*PARENT PROCESS CODE TO RECIEVE INTIAIL Hello  AND SEND REVERSE hELLO*/
if(pid > 0)
{
	close(fd[1]);
	read(fd[0], buffer, BUFFER_SIZE);
	close(fd[0]);
	printf("Initial: %s\n", buffer);
	printf("\n");
	close(fd[0]);
	write(fd2[1], reverseArg, strlen(reverseArg)+1);
}

return 0;
}// end program