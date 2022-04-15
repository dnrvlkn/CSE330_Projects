// volkan Doner

#include<unistd.h>
#include "threads.h"




int global = 0;
int local_var;
int global_var;
int thread_id=1;




void function1() {
	int local1 = 1;
	
	

	int j=1;

	while(j<=global_var)
	{	if(local_var==1){thread_id=1;}
		global=global+thread_id;
		printf("\n This is %d th execution of thread %d with global var value %d \n", j, thread_id, global);
		
		thread_id++;
		if(thread_id%local_var==1)
		{		
		thread_id=1;
		}
		yield();

		j++;
		
	}
	
	
	



}



int main() {
	char comma[1];
	scanf("%d%c%d",&local_var,comma,&global_var);

	if(local_var==0){
	printf("No Threads\n");
	exit(0);
	}
	
	RunQ = (struct queue*) malloc(sizeof(struct queue));
	initQueue(RunQ);

	for(int i=0; i<local_var;i++){

	start_thread(function1);


	}	

	run();
	return 0;
}
