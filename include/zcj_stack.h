#ifndef _ZCJ_STACK_H_
#define _ZCJ_STACK_H_

#define T int

struct stack
{
  T *elem;
  int capacity;
  int index;
};

void initStack(struct stack *s,int capacity);
int top(struct stack *s,T *t);
T pop(struct stack *s, T *t);
int push(struct stack *s,T t);
void releaseStack(struct stack *s);

#endif /* _ZCJ_STACK_H_ */
