/* Single Author Info:
 *  abpatwar Aditya B Patwardhan
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include "mybarrier.h"

pthread_t *q;
int qiter;
int SLEEP = 3600;

void bar_handler(int signal){
	
}

/* Initialize barrier and allocate memory */
int mybarrier_init(mythread_barrier_t* barrier, const mythread_barrierattr_t * mybarrattr, unsigned count){
	
	
	*barrier = (mythread_barrier_t)malloc(sizeof(struct mythread_barrier));
	
	
	/* Initialize the barrier attributes */
	pthread_mutex_init(&((*barrier)->barrier_mutex),NULL); 	/* Initialize mutex */
	(*barrier)->alive = 1;								
	(*barrier)->num_threads = count;
	(*barrier)->num_threads_init = count;

	q = (pthread_t*)malloc(sizeof(pthread_t)*count);		/* Queue to hold values of tid */
	qiter = 0;												/* Queue iterator */

	return 0;
}

int mybarrier_destroy(mythread_barrier_t * mybarrier){
	
	if(mybarrier == NULL){		
    	return -EINVAL;										/* Return Invalid if no memory was allocated for the barrier */
  	}

  	if ((*mybarrier)->alive == 0){
    	return -EINVAL; 									/* Return Invalid if trying to destroy an already destroyed barrier */
  	}

  	pthread_mutex_destroy(&((*mybarrier)->barrier_mutex));	/* Destroy the mutex */
  
  	(*mybarrier)->alive = 0;								/* Destroy the barrier */

  	free(*mybarrier);										/* Free memory allocated to the barrier */
  	free(q);												/* Free memory allocated to the queue */

  	return 0;
}

int mybarrier_wait(mythread_barrier_t * mybarrier){
	

	sigset_t bar_mask,old_mask;
	sigemptyset(&bar_mask);
	sigaddset(&bar_mask,SIGUSR1);
	pthread_sigmask(SIG_UNBLOCK,&bar_mask,&old_mask);			/* Process responds to SIGUSR1 now */
	
	/* Set sigaction structure and function */	
	struct sigaction bar_action,old_action;
	bar_action.sa_handler = bar_handler;					
	bar_action.sa_mask = bar_mask;
	bar_action.sa_flags = 0;

	if((sigaction(SIGUSR1,&bar_action,&old_action))<0){ 		/* Install the user signal handler */
			return -1;
	}
	
	pthread_mutex_lock(&((*mybarrier)->barrier_mutex));
	
	((*mybarrier)->num_threads)--;
	q[qiter] = pthread_self();									/* Store the tid in the queue */
	
	qiter++;													/* Increment the iterator */
										
	
	pthread_mutex_unlock(&((*mybarrier)->barrier_mutex));
	
	if((*mybarrier)->num_threads!=0){							/* If the thread is not the last thread */
		
		sleep(SLEEP);	
		
		pthread_mutex_lock(&((*mybarrier)->barrier_mutex));
		pthread_mutex_unlock(&((*mybarrier)->barrier_mutex));
													
	}
	else{														/* If the thread is the last thread */
		
		int i;
		pthread_mutex_lock(&((*mybarrier)->barrier_mutex));
		
		for(i=0;i<qiter;i++){
			
			pthread_kill(q[i],SIGUSR1);
			
		}
		
		(*mybarrier)->num_threads = (*mybarrier)->num_threads_init;
		qiter = 0;
		pthread_mutex_unlock(&((*mybarrier)->barrier_mutex));
		
		return PTHREAD_BARRIER_SERIAL_THREAD;

	}
	
	return 0;
}