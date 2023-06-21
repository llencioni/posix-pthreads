/*
 * 3rd-semaphores.c
 *
 *  Created on: Jun 21, 2023
 *      Author: luizlencioni
 *
 *  Pthread application with semaphores
 *
 *  To compile: $ gcc 3rd-semaphores.c -o 3rd-semaphores.exe -lpthread
 *  To run:     $ ./3rd-semaphores.exe
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include <semaphore.h>	/* POSIX semaphores */
#include <fcntl.h>      /* Semaphores O_* constants */


/* Semaphore Handle */
sem_t* semHandleThreadA;
sem_t* semHandleThreadB;


/*
 * Thread A routine
 */
void * threadA_function(void *arg)
{
    int counter = 0;

	printf("Running %s ... \n", (char *)arg);
	sem_wait(semHandleThreadA);

    while(++counter < 10)
    {
        printf("%s: %i\n", (char *)arg, counter);
		sem_post(semHandleThreadB);
		sem_wait(semHandleThreadA);
    }

	/* Ends routine with an argument */
	sem_post(semHandleThreadB);
	pthread_exit(arg);
}

/*
 * Thread B routine
 */
void * threadB_function(void *arg)
{
    int counter = 0;

	printf("Running %s ... \n", (char *)arg);
	sem_post(semHandleThreadA);
	sem_wait(semHandleThreadB);

    while(++counter < 10)
    {
        printf("%s: %i\n", (char *)arg, counter);
		sem_post(semHandleThreadA);
		sem_wait(semHandleThreadB);
		//sched_yield();
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

	/* Create a semaphore for Thread A */
	semHandleThreadA = sem_open("SemThreadA", 
								 O_RDWR | O_CREAT, 
								 S_IRWXU | S_IRWXG | S_IRWXO, 
								 0);

	/* Create a semaphore for Thread B */
	semHandleThreadB = sem_open("SemThreadB", 
								 O_RDWR | O_CREAT, 
								 S_IRWXU | S_IRWXG | S_IRWXO, 
								 0);

	if((semHandleThreadA!= 0) || (semHandleThreadB!=0) )
		printf ("\nSemaphores Created!\n");
	else
		printf ("Semaphores Error!");
		

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

