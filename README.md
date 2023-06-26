# posix-pthreads

To compile:
$ gcc <file-name.c> -o <file-name.exe> -lpthread

To run:
$ ./<file-name.exe>

#include <unistd.h>
========================
- pid_t
- pid_t  getpid()  // returns the process ID
- pid_t  getppid() // returns the parent process ID

#include <sys/sysinfo.h>
===============================
- int get_nprocs_conf(void); // gets the number of processors configured in the OS
- int get_nprocs(void);	     // gets the number of processors available 

#include <semaphore.h>	
=============================================
- #include <fcntl.h> // Semaphores O_* constants
- sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value);
- int sem_wait(sem_t *sem);
- int sem_post(sem_t *sem);

#include <pthread.h>
==========================
- PTHREAD_SCOPE_PROCESS, PTHREAD_SCOPE_SYSTEM
- SCHED FIFO, SCHED OTHER, SCHED RR // scheduling policy thread_attr_t
- int pthread_attr_getscope () // gets thread scope (PTHREAD_SCOPE_SYSTEM, PTHREAD_SCOPE_PROCESS)

#include <sched.h>
========================
- struct sched_param { 
   ...
   int  sched_priority;
   ...
}
- int sched_get_priority_max(int policy)  // returns the lowest absolute priority (0 for SCHED_OTHERS and 1 for all others)
- int sched_get_priority_min(int policy)   // returns the highwest absolute priority (0 for SCHED_OTHERS and 99 for all others)
- int sched_setparam(pid_t pid, const struct sched_param *param);  // set process scheduler parameter (priority) 
- int sched_getparam(pid_t pid, struct sched_param *param);            // get process scheduler parameter (priority)
- int sched_setscheduler(pid_t pid, int policy, const struct sched_param *param);   // set scheduling policy and parameters
- int sched_getscheduler()	// gets scheduling type (SCHED_FIFO, SCHED_RR, SCHED_OTHER)

CPUs sets
=========
- "cpu_set_t" data structure represents a set of CPUs.
- CPU sets are used by sched_setaffinity(2) and similar interfaces.
- "cpu_set_t" data type is implemented as a bitset. However, the data structure treated as considered opaque: all manipulation of CPU sets should be done via the following macros:
- CPU_ZERO() // Clears set, so that it contains no CPUs.
- CPU_SET() // Add CPU cpu to set.
- CPU_CLR() // Remove CPU cpu from set.
- CPU_ISSET() // Test to see if CPU cpu is a member of set.
- CPU_COUNT() // Return the number of CPUs in set

REFERENCES
=====================
https://opensource.com/article/19/2/fair-scheduling-linux

https://embarcados.com.br/threads-posix/

https://en.wikipedia.org/wiki/Completely_Fair_Scheduler

https://pubs.opengroup.org/onlinepubs/9699919799/

https://linux.die.net