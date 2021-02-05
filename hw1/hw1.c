#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MINPID 0
#define MAXPID 5

int pid[1];

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

int main(){
int map =allocate_map();
if(map==1){
printf("#####allocating bitmap#####\n");
printf("[ Bitmap ]\n");
for(int i=MINPID ;i<=MAXPID ;i++){
printf("bitmap[%d]=%d\n",i,(pid[i/32]/32));
}
}
printf("-----------------------------\n");
int n;
for(int i=0;i<7;i++){
	n=allocate_pid();
	printf("process%d pid=%d\n",i,n);
}
printf("[ Bitmap ]\n");
for(int i=MINPID ;i<=MAXPID ;i++){
printf("bitmap[%d]=%d\n",i,(pid[i/32]/32));
}

printf("-----------------------------\n");
for(int i=MINPID ;i<=MAXPID ;i++){
	release_pid(i);
	printf("released pid%d\n",i);
}
printf("[ Bitmap ]\n");
for(int i=MINPID ;i<=MAXPID ;i++){
printf("bitmap[%d]=%d\n",i,(pid[i/32]/32));
}


return 0;
}
