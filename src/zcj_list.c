#include<stdlib.h>

#include"zcj_list.h"

void initList(struct list *l){
  l->head=NULL;
#ifndef CLIST
  l->tail=NULL;
#endif
}

int insertListNode(struct list *l,TL t){
  
#if defined(DLIST) /*double list*/
  struct listNode *pnode=(struct listNode*)malloc(sizeof(struct listNode));
  if(pnode==NULL){
    return 0;
  }
  pnode->value=t;
  pnode->next=NULL;
  pnode->pre=NULL;

  if(l->head==NULL){
    l->head=pnode;
    l->tail=pnode;
  }else{
    l->tail->next=pnode;
    pnode->pre=l->tail;
    l->tail=pnode;
  }
  
  return 1;
#elif defined(CLIST) /*circular list*/
  struct listNode *pnode=(struct listNode*)malloc(sizeof(struct listNode));
  if(pnode==NULL){
    return 0;
  }
  pnode->value=t;
  pnode->next=NULL;
  pnode->pre=NULL;
  if(l->head==NULL){
    l->head=pnode;
    pnode->next=pnode;
    pnode->pre=pnode;
  }else{
    pnode->pre=l->head->pre;
    pnode->next=l->head;

    l->head->pre->next=pnode;
    l->head->pre=pnode;
  }
  
  return 1;
#else /*common list*/
  struct listNode *pnode=(struct listNode*)malloc(sizeof(struct listNode));
  if(pnode==NULL){
    return 0;
  }
  pnode->value=t;
  pnode->next=NULL;
  if(l->head==NULL){
    l->head=pnode;
    l->tail=pnode;
  }else{
    l->tail->next=pnode;
    l->tail=pnode;
  }
  
  return 1;
#endif
}

int deleteListNode(struct list *l,TL t){
#if defined(DLIST)
  struct listNode *node;
  node=l->head;

  while(node!=NULL){
    if(node->value == t){
      if(l->head==node){
        l->head=node->next;
        if(l->head!=NULL){
          l->head->pre=NULL;
        }
      }

      if(l->tail==node){
        l->tail=node->pre;
        if(l->tail!=NULL){
          l->tail->next=NULL;
        }
      }

      if(node->pre!=NULL){
        node->pre->next=node->next;
        
      }
      if(node->next!=NULL){
        node->next->pre=node->pre;
      }

      free(node);
      node=NULL;
        
      return 1;
    }else{
      node=node->next;
    }
  }
  
  return 0;
#elif defined(CLIST)  
  struct listNode *node;
  node=l->head;

  if(node==NULL){
    return 0;
  }
  
  do{
    if(node->value == t){
      if(l->head==l->head->next && l->head==node){
        l->head=NULL;
      }else{
        if(l->head==node){
          l->head=node->next;
        }

        node->pre->next=node->next;
        node->next->pre=node->pre;
      }        
      free(node);
      node=NULL;
        
      return 1;
    }else{
      node=node->next;
    }
  }while(node!=l->head);
  
  return 0;
#else
  //int dc=0;//记录删除节点的个数
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
      
      //++dc;
      //node=(prenode==NULL)?l->head:prenode->next;
        
      return 1;
    }else{
      prenode=node;
      node=node->next;
    }
    
  }
 
  return 0;
#endif
}

struct listNode *getListNodeByValue(struct list *l, TL t){
  if(l->head==NULL){
    return NULL;
  }else{
    struct listNode *pnode=l->head;
  
    do{
      if(pnode->value==t){
        return pnode;
      }else{
        pnode=pnode->next;
      }
    }while(pnode!=NULL && pnode!=l->head);
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
#if defined(DLIST)
  struct listNode *pnode1,*pnode2;

  pnode1=l->head;
  while(pnode1){
    pnode2=pnode1->next;

    free(pnode1);
    pnode1=pnode2;
  }
  l->head=NULL;
  l->tail=NULL;
#elif defined(CLIST)
  if(l->head==NULL){
    return;
  }else{
    struct listNode *pnode1,*pnode2;

    pnode1=l->head->next;

    while(pnode1!=l->head){// 把 l->head 作为标记
      pnode2=pnode1->next;
      
      free(pnode1);
      pnode1=pnode2;
    }
    free(l->head);
      
    l->head=NULL;
  }
#else
  struct listNode *pnode1,*pnode2;

  pnode1=l->head;
  while(pnode1){
    pnode2=pnode1->next;

    free(pnode1);
    pnode1=pnode2;
  }
  l->head=NULL;
  l->tail=NULL;
#endif

}
