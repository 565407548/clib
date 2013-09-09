#include<stdio.h>
#include<stdlib.h>

#include "../include/zcj_disjointSets.h"

static int _capacity=CAPACITY;
static int _len=0;
static struct ds_head _heads[CAPACITY];
static struct ds_node *_tails[CAPACITY];
static int (*_node_compare)(const TID , const TID);
static TID (*_getNodeID)(T t);

void initSet(int capacity,TID (*getNodeID)(T t),int (*node_compare)(const TID, const TID)){
  if(capacity>CAPACITY)
    capacity=CAPACITY;
  _capacity=capacity;
  _len=0;
  
  int i;
  for(i=0;i<_capacity;i++){
    _heads[i].len=0;
    /* heads[i].node=NULL; */
  }

  if(_node_compare==NULL || _getNodeID==NULL){
    perror("参数中的函数指针不能为空");
  }
  _node_compare=node_compare;
  _getNodeID=getNodeID;
  
}

struct ds_node * findSetNode(TID tid){
  int i;

  for(i=0;i<_len;i++){
    if(_heads[i].len>0){
      struct ds_node *node=_heads[i].node;
      while(node!=NULL){
        if(((*_node_compare)(tid,(*_getNodeID)(node->elem)))==0)
          return node;
        node=node->next;
      }
    }
  }
  return NULL;
}

int newSet(T t){
  int i;
  
  for(i=0;i<_len;i++){
    if(_heads[i].len==0)
      break;
  }
  if(i==_len){
    if(_len+1>_capacity)
      return -1;
    ++_len;
  }
  
  struct ds_node *node1=(struct ds_node *)malloc(sizeof(struct ds_node));

  _heads[i].len++;
  _heads[i].node=node1;
    
  node1->elem=t;
  node1->next=NULL;
  _tails[i]=node1;
  node1->headID=i;
  
  return i;
}

int sameSet(TID tid1,TID tid2){
  int index1=findSetNode(tid1)->headID;
  int index2=findSetNode(tid2)->headID;
  if(index1>=0 && index1==index2)
    return 1;
  return 0;
}

/*
  把 小集合 合并到 大集合 中
  成功返回1；失败返回0
*/
int unionSet(TID tid1,TID tid2){
  int n1,n2,max,min;
  n1=findSetNode(tid1)->headID;
  n2=findSetNode(tid2)->headID;

  if(n1<0 || n2<0)
    return 0;
  
  if(n1!=n2){
    //把小集合的合并到大集合中
    if(_heads[n1].len>=_heads[n2].len){
      max=n1;
      min=n2;
    }else{
      max=n2;
      min=n1;
    }
    
    struct ds_node *node=_heads[min].node;
    _tails[max]->next=node;
    while(node!=NULL){
      node->headID=max;
      node=node->next;
    }
    _tails[max]=_tails[min];
    
    _heads[max].len+=_heads[min].len;
    _heads[min].len=0;
  }
  
  return 1;
}

void releaseSets(){
  int i;
  struct ds_node *p,*node;
  for(i=0;i<_len;i++){
    if(_heads[i].len!=0){
      node=_heads[i].node;
      while(node!=NULL){
        p=node;
        node=node->next;
        
        free(p);
      }
      _heads[i].len=0;
    }
  }
}

