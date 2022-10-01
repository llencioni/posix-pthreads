/*
 *  Created on: Sep 29, 2022
 *
 *  Examples from the book: Programming with POSIX Threads
 */

#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


 void ChildProcess(void)
 {
	 printf("Hello from the child process!\n");
	 _exit(EXIT_SUCCESS);

 }

void ParentProcess(pid_t pid)
{
	int status;

	printf("Hello from the parent process!\n");
	(void)waitpid(pid, &status, 0);
	printf("Waiting for the child process to exit... now parent can exit too!\n");

}

int main (int argc, char *argv[])
{

    pid_t pid = fork();

	printf ("Fork ...\n");

    /*
     * If fork was successful, then there are now two processes, both executing the main function
     * from the point where fork has returned.
     *
     * To make the processes perform different tasks, the program
     * must branch on the return value of fork to determine whether it is executing as the child process
     * or the parent process.
     *
     * Minus one indicates an error in fork: no new process was created
     */

    if (pid == -1)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
	{
    	ChildProcess();
	}
    else
    {
    	ParentProcess(pid);
    }

    return EXIT_SUCCESS;
}

