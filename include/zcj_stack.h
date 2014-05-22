#ifndef _ZCJ_STACK_H_
#define _ZCJ_STACK_H_

#define TS struct treeNode *

struct stackNode{
  TS elem;
  struct stackNode *next;
};

struct stack{
  struct stackNode *top;
};

void initStack(struct stack *s);
int top(struct stack *s,TS *t);
int pop(struct stack *s, TS *t);
int push(struct stack *s,TS t);
void releaseStack(struct stack *s);

#endif /* _ZCJ_STACK_H_ */
