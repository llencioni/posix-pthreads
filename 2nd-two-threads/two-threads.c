/*
 * simple-rt-pthread.c
 *
 *  Created on: Jun 17, 2023
 *      Author: luizlencioni
 *
 *  Pthread application with 2 threads
 *
 *  To compile: $ gcc two-threads.c -o two-threads.exe -lpthread
 *  To run:     $ ./two-threads.exe
 *
 *	OBS:
 *	 1) To prove POSIX compatibility, this program may run on Linux or macOS
 *	 2) Threads are not synchronized !!!
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/*
 * Thread A routine
 */
void * threadA_function(void *arg)
{
    int counter = 0;

	printf("Running %s ... \n", (char *)arg);

    while(++counter < 10)
    {
        printf("%s: %i\n", (char *)arg, counter);
        sched_yield();
    }

	/* Ends routine with an argument */
	pthread_exit(arg);
}

/*
 * Thread B routine
 */
void * threadB_function(void *arg)
{
    int counter = 0;

	printf("Running %s ... \n", (char *)arg);

    while(++counter < 10)
    {
        printf("%s: %i\n", (char *)arg, counter);
        sched_yield();
    }

	/* Ends routine with an argument */
	pthread_exit(arg);
}

/*
 * Main routine
 */
int main (int argc, char *argv[])
{
	pthread_t threadA_id;
	pthread_t threadB_id;
	void * threadA_exit;
	void * threadB_exit;
	int status;

	/* Create Thread A */
	status = pthread_create ( &threadA_id,
							  NULL,
							  threadA_function,
							  (void*)("Thread A"));

	/* Check for errors */
	if(status != 0)
	{
		printf ("Thread A create error\n");
		exit(EXIT_FAILURE);
	}
	else
		printf ("\nThread A created!\n");

	/* Create Thread B */
	status = pthread_create ( &threadB_id,
							  NULL,
							  threadB_function,
							  (void*)("Thread B"));

	/* Check for errors */
	if(status != 0)
	{
		printf ("Thread B create error\n");
		exit(EXIT_FAILURE);
	}
	else
		printf ("Thread B created!\n");

	/* Wait for Thread to end, and save its return */
	status = pthread_join (threadA_id, &threadA_exit);

	/* Check for errors */
	if(status != 0)
	{
		printf ("Thread join error\n");
		exit(EXIT_FAILURE);
	}
	else
		printf ("\n%s ended !\n", (char *)threadA_exit);

	/* Wait for Thread to end, and save its return */
	status = pthread_join (threadB_id, &threadB_exit);

	/* Check for errors */
	if(status != 0)
	{
		printf ("Thread join error\n");
		exit(EXIT_FAILURE);
	}
	else
		printf ("\n%s ended !\n\n\n", (char *)threadB_exit);

	return 0;
}

