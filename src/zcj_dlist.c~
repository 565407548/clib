#include<stdlib.h>

#include"zcj_list.h"

void initList(struct list *l){
  l->head=NULL;
  l->tail=NULL;
}

int insertListNode(struct list *l,TL t){
  struct listNode *pnode=(struct listNode*)malloc(sizeof(struct listNode));
  if(pnode==NULL){
    return 0;
  }
  pnode->value=t;
  pnode->next=NULL;

  if(l->head==NULL){
    l->head=pnode;
    l->tail=pnode;
  }
  else{
    l->tail->next=pnode;
    l->tail=pnode;
  }
  return 1;
}

int deleteListNode(struct list *l,TL t){
  int dc=0;//统计删除节点的个数
  struct listNode *node,*prenode;
  prenode=NULL;
  node=l->head;
  
  while(node!=NULL){
    if(node->value == t){
      if(l->head==node){
        l->head=node->next;
      }

      if(l->tail==node){
        l->tail=prenode;
      }

      if(prenode!=NULL){
        prenode->next=node->next;
      }
      
      free(node);
      node=NULL;
      ++dc;

      node=(prenode==NULL)?l->head:prenode->next;
    }else{
      prenode=node;
      node=node->next;
    }
    
  }
  return dc;
}

struct listNode *getListNodeByValue(struct list *l, TL t){
  struct listNode *pnode=l->head;

  while(pnode!=NULL){
    if(pnode->value==t)
      return pnode;
    pnode=pnode->next;
  }
  return NULL;
}

struct listNode *getListNodeByIndex(struct list *l,int index){
  int i;
  struct listNode*pnode;

  i=0;
  pnode=l->head;
  while(i<index && pnode!=NULL){
    ++i;
    pnode=pnode->next;
  }

  if(i==index){
    return pnode;
  }else{
    return NULL;
  }
}

void releaseList(struct list *l){
  struct listNode *pnode1,*pnode2;

  pnode1=l->head;
  while(pnode1){
    pnode2=pnode1->next;

    free(pnode1);
    pnode1=pnode2;
  }
  l->head=NULL;
  l->tail=NULL;
}
