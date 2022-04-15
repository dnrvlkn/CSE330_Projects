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

void P(semaphore *s) {
  struct TCB_t *tcb;

  while (s->value <= 0) {
    tcb = delQueue(RunQ);
    addQueue(s->s_queue, tcb);
   
    if(RunQ->head==NULL){
      exit(0);
    }
    swapcontext(&(tcb->context), &(RunQ->head->context));
    //yield();
  }
    s->value = s->value - 1;
}

void V(semaphore *s) {
  struct TCB_t *tcb;

  if (s->s_queue->head !=NULL){

	  struct TCB_t *semThread=delQueue(s->s_queue);
	   addQueue(RunQ, semThread);
    s->value = s->value + 1;
	  //yield();
  }
  else{
  s->value = s->value + 1;
           
            //yield();
            

  }

}
