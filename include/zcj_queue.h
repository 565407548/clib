#ifndef _ZCJ_QUEUE_H_
#define _ZCJ_QUEUE_H_

#include "zcj_tree.h"

#define TQ struct treeNode *

struct queueNode{
  TQ value;
  struct queueNode * next;
};

struct queue{
  struct queueNode *head;
  struct queueNode *tail;
};

void initQueue(struct queue *q);
int enqueue(struct queue *q,TQ t);
int dequeue(struct queue *q,TQ *t);
void releaseQueue(struct queue *q);

#endif /* _ZCJ_QUEUE_H_ */
