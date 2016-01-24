#include <stdio.h>
#include <signal.h>
#include <pthread.h>

unsigned long id;

void * myfunc();
void * myfunc2();
void handler(int signal);

int main(){
	pthread_t temp1,temp2;
	pthread_create(&temp1,NULL,myfunc,NULL);
	pthread_create(&temp2,NULL,myfunc2,NULL);

	pthread_join(temp1,NULL);
	pthread_join(temp2,NULL);
}

void * myfunc(){
	id = pthread_self();
	sigaction(SIGUSR1,&sig_handler,NULL);
	pthread_exit();

}

void * myfunc2(){
	pthread_kill(id,SIGUSR1);
	pthread_exit();
}

void handler(int signal){
	if(signal!=SIGUSR1){
		printf("Wrong Signal received\n");
	}
	
}