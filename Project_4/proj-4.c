#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "sem.h"

/* Durmus Volkan Doner Project-4*/

semaphore * rsem;
semaphore * wsem;
semaphore * mutex;
int rwc = 0, wwc = 0, rc = 0, wc = 0;
int R, W, numb_of_lines,input, globalVar=0; 


void writerEntry()					
{
	if(rc>0||wc>0||rwc>0||wwc>0){
	wwc++;
	P(wsem);
	wwc--;
	}
	wc++;
	
}

void writerExit()						
{
	wc--;
	if(rwc>0){
	
	for(int i=0; i<rwc;i++){	
	V(rsem);	
	}
	}
	else if(wwc>0){	
	V(wsem);
	}
	
	}
	

void readerEntry(){				
	if(wwc>0||wc>0){
	rwc++;
	P(rsem);
	rwc--;
		
	}
	rc++;
		
}

void readerExit(){
	rc--;
	if(rc==0 && wwc>0){
	V(wsem);
	}
	

}


void reader(int readerID){

  	struct TCB_t *tcb;
  	
	readerEntry();

	printf("\n This is the %d th reader reading value i = %d for the first time \n", readerID, globalVar);
		
	yield();
		
	printf("\n This is the %d th reader reading value i = %d for the second time \n", readerID, globalVar);
	
	
	readerExit();	
	
	tcb=delQueue(RunQ);
	swapcontext(&(tcb->context), &(RunQ->head->context));
	
	
	}	

void writer(int writerID){
	struct TCB_t *tcb;
		
	writerEntry();
	
		globalVar++;
		
		printf("\n This is the %d th writer writing value i = %d \n", -1*writerID, globalVar);
		yield();
		
		printf("\n This is the %d th writer verifying value i = %d \n", -1*writerID, globalVar);
		
		
					
	writerExit();
	 tcb=delQueue(RunQ);
	 swapcontext(&(tcb->context), &(RunQ->head->context));
		
  	
}


int main(){
  	RunQ = (struct queue *) malloc(sizeof(struct queue));
	wsem = (struct semaphore *) malloc(sizeof(struct semaphore));
	rsem = (struct semaphore *) malloc(sizeof(struct semaphore));
	mutex = (struct semaphore *) malloc(sizeof(struct semaphore));
	initQueue(RunQ);
	initSem(rsem, 0);
	initSem(wsem, 0);
	initSem(mutex, 1);
	
	
	scanf("%d,%d",&R,&W);
      
        numb_of_lines=R+W;
 
	
	
    for(int l=1; l<=numb_of_lines; l++){    
   
    scanf("%d",&input);
    
	
    if(input>0){
     int readerID=input;
	
    start_thread(reader,readerID);
    
   
    }
    else{
     int writerID=input;
     	     
     start_thread(writer,writerID);      
         
    }
        
    }

	run();
    
}
