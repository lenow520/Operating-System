#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define MINPID 0
#define MAXPID 99

int pid[10];

void SetBit(int A[], int k){
	A[k/32] |= 1<<(k%32);
}
void ClearBit(int A[], int k){
	A[k/32] &= ~(1<<(k%32));
}
int TestBit(int A[], int k){
	return((A[k/32]) & (1<<(k%32)));
}
int allocate_map(void){
int i;
for(i=MINPID ;i<=MAXPID ;i++){
pid[i]=0;
if(i==MAXPID){
return 1;
}
}
 return -1;}


int allocate_pid(void){
int current=0,i;

for(i=MINPID;i<=MAXPID;i++){
if(TestBit(pid,i)==0){
SetBit(pid,i);
current=i;
break;
}
else if(i==MAXPID){return -1;}
}
return current;
}

void release_pid(int id){
 ClearBit(pid,id);
}

void *function(void *arg){
	int i = *(int *) arg;
	int n=allocate_pid();
	printf("pid of #%lu is %d\n",pthread_self(),n);
	if(n==-1){pthread_exit(NULL);}
	else{
	srand(time(NULL));
	sleep(rand()%3+1);
	release_pid(i);	
}

	pthread_exit(NULL);
}

int main(){
int map =allocate_map();
if(map==1){
printf("#####allocating bitmap#####\n");
}
printf("-----------------------------\n");
pthread_t id[100];
for(int i=MINPID;i<=MAXPID;i++){
pthread_create(&id[i],NULL,function,&i);
}
for(int i=MINPID;i<=MAXPID;i++){
pthread_join(id[i],NULL);
}

return 0;
}
