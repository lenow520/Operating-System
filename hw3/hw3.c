#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define MINPID 0
#define MAXPID 99
pthread_mutex_t mtx;
int pid[10];
static int counter=0;

void SetBit(int A[], int k){
	A[k/32] |= 1<<(k%32);
}
void ClearBit(int A[], int k){
	A[k/32] &= ~(1<<(k%32));
}
int TestBit(int A[], int k){
	return((A[k/32]) & (1<<(k%32)));
}
void release_pid(int id){
 ClearBit(pid,id);
}

int allocate_map(void){
int i;
for(i=MINPID ;i<=MAXPID ;i++){
pid[i]=0;
if(i==MAXPID){
printf("#####pid bitmap ready#####\n");
return 1;
}
}
 return -1;}


int allocate_pid(void){
counter++;
int current=0,i;
for(i=MINPID;i<=MAXPID;i++){
if(TestBit(pid,i)==0){
SetBit(pid,i);
current=i+300;
break;
}
else if(i==MAXPID){return -1;}
}
return current;
}



void *function(void *arg){
	int s,n;	
	int i = *(int *) arg;
	
	s=pthread_mutex_lock(&mtx);
	n=allocate_pid();
	s=pthread_mutex_unlock(&mtx);
	
	printf("%3d. pid of #%lu is %d\n",counter,pthread_self(),n);
	
	if(n==-1){pthread_exit(NULL);}
	else{
	srand(time(NULL));
	sleep(rand()%3+1);}
	
	s=pthread_mutex_lock(&mtx);
	release_pid(i);	
	s=pthread_mutex_unlock(&mtx);

	pthread_exit(NULL);
}

int main(){
int s= pthread_mutex_init(&mtx,NULL);
int map =allocate_map();
printf("-------------------------------------\n");
pthread_t id[100];
for(int i=MINPID;i<=MAXPID;i++){
pthread_create(&id[i],NULL,function,&i);
}
for(int i=MINPID;i<=MAXPID;i++){
pthread_join(id[i],NULL);}
s= pthread_mutex_destroy(&mtx);
return 0;
}
