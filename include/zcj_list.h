#ifndef _ZCJ_LIST_H_
#define _ZCJ_LIST_H_

#define TL int

struct listNode{
  TL value;
  struct listNode *next;
};

struct list{
  struct listNode *head;
  struct listNode *tail;
};

void initList(struct list *l);
int insertListNode(struct list *l,TL t);
int deleteListNode(struct list *l,TL t);
struct listNode *getListNodeByValue(struct list *l,TL t);
struct listNode *getListNodeByIndex(struct list *l,int index);
void releaseList(struct list *l);
  
#endif /* _ZCJ_LIST_H_ */
