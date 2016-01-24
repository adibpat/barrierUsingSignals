#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mybarrier.h"
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 10

pthread_t threadc[NUM_THREADS];
int count[NUM_THREADS];
int fcount[NUM_THREADS];
int iter = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
mythread_barrier_t mybarrier;

void *barrierTest(void* arg){
  
  int temp, mycount;
  
  pthread_mutex_lock(&lock);
  mycount = iter;
  iter = iter + 1;
  printf("Setting Array element %d with value %d\n",mycount,mycount);
  pthread_mutex_unlock(&lock);

  count[mycount] = mycount;

  mybarrier_wait(&mybarrier);   /* Wait till all threads complete */

  pthread_mutex_lock(&lock);
  for(temp=0;temp<iter;temp++){
    fcount[mycount]+=count[temp];
  }

  printf("Thread with ID %ld summed the elements of array and moving towards next barrier\n",pthread_self());

  pthread_mutex_unlock(&lock);

  mybarrier_wait(&mybarrier);

  pthread_mutex_lock(&lock);
  printf("Thread with ID %ld is exiting\n", pthread_self());
  pthread_mutex_unlock(&lock);


  pthread_exit(NULL);
}

int main(void){
  
  int err1, err2;
  int i,j,sum;
   
  printf("This test program calculates the sum of all elements of an array.\n");
  printf("If all elements of the array have equal value, the test is successful.\n");

  if (mybarrier_init(&mybarrier, NULL, NUM_THREADS) != 0){
    printf("Barrier Test Fail\n");
    return 1;
  }

  for(i=0;i<NUM_THREADS;i++){
    err1 = pthread_create(&threadc[i],NULL,barrierTest,NULL);
    if (err1 != 0) printf("Barrier Test Fail\n");
  }
    
  for(j=0;j<NUM_THREADS;j++){
    err2 = pthread_join(threadc[j],NULL);
    if (err1 != 0) printf("Barrier Test Fail\n");
  }

  for(i=0;i<NUM_THREADS;i++){
    sum+=i;
  }

  printf("sum :%d\n",sum);

  for(i=0;i<NUM_THREADS;i++){
    if(sum!=fcount[i]){
      printf("Barrier test: FAIL\n");
      return 1;
    }
  }

  printf("Sum computed by threads equals expected sum.\n");
  
  if (mybarrier_destroy(&mybarrier) != 0){
        printf("Barrier Test Fail\n");
        return 1;
    }

  printf("Barrier Test PASS\n");

  return 0;

}
