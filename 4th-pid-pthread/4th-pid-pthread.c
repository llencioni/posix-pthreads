#define _GNU_SOURCE

#include <pthread.h>
#include <sys/types.h> 		// pid_t
#include <unistd.h> 		// getpid()
#include <sys/sysinfo.h> 	// get_nprocs_conf(), get_nprocs()
#include <stdio.h>
#include <sched.h>
//#include <stdlib.h>
//#include <time.h>

#define NUM_THREADS (4)
#define NUM_CPUS (4)

#define NSEC_PER_SEC (1000000000)
#define NSEC_PER_MSEC (1000000)
#define NSEC_PER_MICROSEC (1000)
#define DELAY_TICKS (1)
#define ERROR (-1)
#define OK (0)

/* Set the desired scheduler type */
//#define MY_SCHEDULER SCHED_FIFO
#define MY_SCHEDULER SCHED_RR
//#define MY_SCHEDULER SCHED_OTHER

int numberOfProcessors=NUM_CPUS;

unsigned int idx = 0, jdx = 1;
unsigned int seqIterations = 47;
unsigned int reqIterations = 10000000;
volatile unsigned int fib = 0, fib0 = 0, fib1 = 1;


// POSIX thread declarations and scheduling attributes
//
//pthread_t threads[NUM_THREADS];
//threadParams_t threadParams[NUM_THREADS];
//pthread_attr_t rt_sched_attr[NUM_THREADS];
int rt_max_prio, rt_min_prio;
//struct sched_param rt_param[NUM_THREADS];
struct sched_param main_param;
pthread_attr_t main_attr;
pid_t mainpid;


void print_scheduler(void)
{
   int schedType;
   int scope;
   int ret;

   printf("\nPthread scheduler parameters ...\n");

   /************************/
   /* Get scheduler policy */
   /************************/

   schedType = sched_getscheduler(getpid());

   switch(schedType)
   {
   	 case SCHED_FIFO:
    	 printf("Pthread Policy is SCHED_FIFO\n");
    	 break;
     case SCHED_OTHER:
    	 printf("Pthread Policy is SCHED_OTHER\n");
    	 break;
     case SCHED_RR:
    	 printf("Pthread Policy is SCHED_RR\n");
    	 break;
     default:
    	 printf("Pthread Policy is UNKNOWN\n");
    	 break;
   }

   /**********************************************************/
   /* Get priority min/max value according to scheduler type */
   /**********************************************************/

   rt_max_prio = sched_get_priority_max(schedType);
   rt_min_prio = sched_get_priority_min(schedType);

   printf("rt_max_prio = %d\n", rt_max_prio);
   printf("rt_min_prio = %d\n", rt_min_prio);

   /***************************/
   /* Get process scope value */
   /***************************/

   pthread_attr_getscope(&main_attr, &scope);

   if(scope == PTHREAD_SCOPE_SYSTEM)
     printf("PTHREAD SCOPE SYSTEM\n");
   else if (scope == PTHREAD_SCOPE_PROCESS)
     printf("PTHREAD SCOPE PROCESS\n");
   else
     printf("PTHREAD SCOPE UNKNOWN\n");

   /************************/
   /* get process priority */
   /************************/

   ret = sched_getparam(mainpid, &main_param);
   if(ret == 0)
	   printf("Process priority = %d\n", main_param.sched_priority);
   else
	   perror("***** ERROR: getting sched_getparam!");

}


int main (int argc, char *argv[])
{
   int rc, idx;
   int i;
//   cpu_set_t threadcpu;
   int coreid;

   printf("\nThis system has %d processors with %d available\n", get_nprocs_conf(), get_nprocs());
   printf("The test thread created will be run on a specific core based on thread index\n");

   /* get main process PID */
   mainpid=getpid();
   printf("Main PID = %d\n", mainpid);

   /* print scheduler parameters */
   print_scheduler();

   /* set process priority to max */
   main_param.sched_priority = 10;//rt_max_prio;

   if(MY_SCHEDULER != SCHED_OTHER)
   {
	   rc = sched_setscheduler(mainpid,
			   	   	   	   	   MY_SCHEDULER,
							   &main_param);
	   if(rc != 0)
		   perror("******** WARNING: sched_setscheduler");
   }

   print_scheduler();

   /*

   for(i=0; i < NUM_THREADS; i++)
   {
       CPU_ZERO(&threadcpu);

       coreid=i%numberOfProcessors;
       printf("Setting thread %d to core %d\n", i, coreid);

       CPU_SET(coreid, &threadcpu);

       rc=pthread_attr_init(&rt_sched_attr[i]);
       rc=pthread_attr_setinheritsched(&rt_sched_attr[i], PTHREAD_EXPLICIT_SCHED);
       rc=pthread_attr_setschedpolicy(&rt_sched_attr[i], MY_SCHEDULER);
       rc=pthread_attr_setaffinity_np(&rt_sched_attr[i], sizeof(cpu_set_t), &threadcpu);

       rt_param[i].sched_priority=rt_max_prio-i-1;
       pthread_attr_setschedparam(&rt_sched_attr[i], &rt_param[i]);

       threadParams[i].threadIdx=i;

       pthread_create(&threads[i],               // pointer to thread descriptor
                      &rt_sched_attr[i],         // use AFFINITY AND SCHEDULER attributes
                      workerThread,              // thread function entry point
                      (void *)&(threadParams[i]) // parameters to pass in
                     );

   }


   for(i=0;i<NUM_THREADS;i++)
       pthread_join(threads[i], NULL);

   printf("\nTEST COMPLETE\n");
*/
}
