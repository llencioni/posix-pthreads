/*
 * simple-rt-pthread.c
 *
 *  Created on: Jun 17, 2023
 *      Author: luizlencioni
 *
 *  Simple pthread application
 *
 *  To compile: $ gcc simple-rt-pthread.c -o simple-rt-pthread.exe -lpthread
 *  To run: ./simple-rt-pthread.exe
 *
 *	OBS:
 *	 To prove POSIX compatibility, this program may run on Linux or macOS
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/*
 * Thread routine
 */
void * threadA_function(void *arg)
{

	printf("\nRunning Thread 1st ... argument received: %s\n", (char *)arg);

	/* Ends routine with an argument */
	pthread_exit(arg);
}


/*
 * Main routine
 */
int main (int argc, char *argv[])
{
	pthread_t thread_id;
	void * thread_res;
	int status;
	volatile int i = 0;

	/* Create 1st Thread */
	status = pthread_create ( &thread_id,
							  NULL,
							  threadA_function,
							  (void*)("It works!"));

	/* Check for errors */
	if(status != 0)
	{
		printf ("Thread create error\n");
		exit(EXIT_FAILURE);
	}
	else
		printf ("\n1st Thread created!\n");

	/* Wait for 1st Thread to end, and save its return */
	status = pthread_join (thread_id, &thread_res);

	/* Check for errors */
	if(status != 0)
	{
		printf ("Thread join error\n");
		exit(EXIT_FAILURE);
	}
	else
		printf ("\n1st Thread ended!!! It returned: %s\n\n\n", (char *)thread_res);

	return 0;
}

