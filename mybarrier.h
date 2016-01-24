/* Single Author Info:
 *  abpatwar Aditya B Patwardhan
 */

#include <pthread.h>

typedef struct mythread_barrier{
	pthread_mutex_t barrier_mutex;
	unsigned int num_threads;
	unsigned int num_threads_init;
	int alive;	
} *mythread_barrier_t;

typedef struct mythread_barrierattr{
	int dummy;
} mythread_barrierattr_t;

int mybarrier_init(mythread_barrier_t * mybarrier, const mythread_barrierattr_t *mybarrattr, unsigned count);

int mybarrier_wait(mythread_barrier_t * mybarrier);

int mybarrier_destroy(mythread_barrier_t * mybarrier);