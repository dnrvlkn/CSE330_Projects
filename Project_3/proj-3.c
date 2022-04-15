/*
Volkan Doner

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sem.h"

semaphore *empty, *full;

int  B, Pr, C, N;
int input;
int *buff;
int numb_of_lines;
int threadID;
int *PplusC;
int numofEle=0;
 

int in = 0, out = 0 ;
int prod_id, cons_id;


  
     

void prod(int PId)
{

  int i = 1;
while( i<=N ){

	
  	
	P(empty,PId);

	buff[in] = PId;		
	
	printf("\n Producer %d is producing item number %d \n", PId, i);
	in = (in+1) % B;

	i++;	
	V(full);
	if (B==0){
	printf("\n Producer %d is waiting \n", PId);


	}
yield();
	}
	

for (int m = 0; m < 1000; m++) {yield();}
  }




void cons(int CId)
{
int i = 1;
while( i<=N ){
  	
	P(full,CId);
	printf("\n Consumer %d is consuming item generated by Producer %d \n", (-1*CId), buff[out]);
	
	out = (out+1) % B;
	

 	i++;	
	V(empty);
	
		

	
 	if (B==0){
	printf("\n Producer %d is waiting \n", (-1*CId));


	}
		yield();
 	}
for (int m = 0; m < 1000; m++) {yield();}
  }



int main()
{
    
    char comma[1];
    scanf("%d,%d,%d,%d",&B,&Pr,&C,&N);
  
    
    numb_of_lines=Pr+C;

 
  
    
    
    	
    RunQ = (struct queue *) malloc(sizeof(struct queue));
    empty = (struct semaphore *) malloc(sizeof(struct semaphore));
    full = (struct semaphore *) malloc(sizeof(struct semaphore));
    
    buff= (int*) malloc(B*sizeof(int));


    initQueue(RunQ);
    
    initSem(full, 0);
    initSem(empty, B);
    
     for(int l=1; l<=numb_of_lines; l++){    
   
    scanf("%d",&input);
    
    
    if(input>0){
     int PId=input;

    start_thread(prod,PId);}
    else{
     int CId=input;

    start_thread(cons,CId);
    }
    
    
        
    }
    	
    
    run();


    return 0;
}
