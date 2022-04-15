#include <ucontext.h>
#include <string.h>
#include "threads.h"



typedef struct semaphore {
  struct queue *s_queue;
  int value;
} semaphore;

void initSem(semaphore *s, int val) {
  s->s_queue = (struct queue*) malloc(sizeof(struct queue));
  initQueue(s->s_queue);
  s->value = val;
}

void P(semaphore *s, int threadId) {
  struct TCB_t *tcb;
  
  while (s->value <= 0) {
    tcb = delQueue(RunQ);
    

     if(threadId<0){
    printf("\n Consumer %d is waiting \n", threadId*-1);    
    }
    else{       
        printf("\n Producer %d is waiting \n", threadId);    
    }
                 
        addQueue(s->s_queue, tcb); 
    if(RunQ->head==NULL){
      exit(0);
    }

             
        swapcontext(&(tcb->context), &(RunQ->head->context));   
        yield();
    
}


    


  s->value = s->value - 1;
}


void V(semaphore *s) {
  struct TCB_t *tcb;

  if (s->s_queue->head !=NULL){

	  struct TCB_t *semThread=delQueue(s->s_queue);
	   addQueue(RunQ, semThread);
    s->value = s->value + 1;
	  yield();
  }
  else{
  s->value = s->value + 1;
           
            yield();
            

  }

}

/*
void V(semaphore *s) {
  struct TCB_t *tcb;
  s->value = s->value + 1;
  //printf("%d ----\n",s->value);
  if (s->value < 0) {
    tcb = delQueue(s->s_queue);
    if (tcb != NULL){
      addQueue(RunQ, tcb);
    }
  }
  yield();
}*/
  
  
