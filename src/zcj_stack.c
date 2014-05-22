#include<stdlib.h>

#include "zcj_stack.h"

void initStack(struct stack *s){
  s->top=NULL;
}

int top(struct stack *s,TS *t){
  if(s->top!=NULL){
    if(t!=NULL)
      *t=s->top->elem;
    return 1;
  }
  return 0;
}

int pop(struct stack *s,TS *t){
  struct stackNode *sn;
  if(top(s,t)){
    sn=s->top;
    s->top=s->top->next;

    free(sn);
    return 1;
  }
  return 0;
}

int push(struct stack *s,TS t){
  struct stackNode *sn=(struct stackNode*)malloc(sizeof(struct stackNode));

  if(sn==NULL){
    return 0;
  }
  sn->elem=t;
  sn->next=s->top;
  s->top=sn;
  
  return 1;
}

void releaseStack(struct stack *s){
  while(pop(s,NULL));
}
