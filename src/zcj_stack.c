#include<stdlib.h>

#include "zcj_stack.h"

void initStack(struct stack *s,int capacity){
  s->elem=(T*)malloc(sizeof(T)*capacity);
  if(s->elem==NULL){
    perror("内存空间不够，无法给栈分配内存空间");
    capacity=0;
  }
  s->capacity=capacity;
  s->index=s->capacity;
}

int top(struct stack *s,T *t){
  if(s->index>=0 && s->index<s->capacity){
    *t=s->elem[s->index];
    return 1;
  }
  return 0;
}

int pop(struct stack *s,T *t){
  if(top(s,t)){
    s->index++;
    return 1;
  }
  return 0;
}

int push(struct stack *s,T t){
  if(s->index>0){
    s->index--;
    s->elem[s->index]=t;
    return 1;
  }
  return 0;
}

void releaseStack(struct stack *s){
  if(s->elem){
    free(s->elem);
  }
}
