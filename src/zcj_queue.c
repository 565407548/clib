#include<stdlib.h>

#include "zcj_queue.h"

void initQueue(struct queue *q){
  q->head=NULL;
  q->tail=NULL;
}

int enqueue(struct queue *q,TQ t){
  struct queueNode *node=(struct queueNode *)malloc(sizeof(struct queueNode));
  if(node==NULL)
    return 0;
  node->value=t;
  node->next=NULL;
  
  if(q->head==NULL){
    q->head=node;
    q->tail=node;
  }else{
    q->tail->next=node;
    q->tail=q->tail->next;
  }
  return 1;
}

int dequeue(struct queue *q,TQ *t){
  struct queueNode *node=q->head;
  if(node==NULL){
    return 0;
  }

  //当最后一个元素出队时，队尾指针置空。此处为了防止通过 q->tail==NULL 来判断队列是否为空而出错的情况
  if(q->head==q->tail){
    q->tail=NULL;
  }
  
  q->head=q->head->next;
  
  *t=node->value;
  free(node);

  return 1;
}

void releaseQueue(struct queue *q){
  struct queueNode *p1,*p2;
  p1=q->head;

  while(p1){
    p2=p1->next;
    free(p1);

    p1=p2;
  }
  q->head=NULL;
  q->tail=NULL;
}
