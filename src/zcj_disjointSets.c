#include<stdio.h>
#include<stdlib.h>

#include "../include/zcj_disjointSets.h"

void initSet(struct disjointSet *ds,int capacity,TID (*getNodeID)(T t),int (*node_compare)(const TID, const TID)){
  if(capacity>CAPACITY)
    capacity=CAPACITY;
  ds->capacity=capacity;
  ds->len=0;

  ds->heads=(struct ds_head*)malloc(sizeof(struct ds_head)*ds->capacity);
  ds->tails=(struct ds_node**)malloc(sizeof(struct ds_node*)*ds->capacity);
  
  int i;
  for(i=0;i<ds->capacity;i++){
    ds->heads[i].len=0;
    /* heads[i].node=NULL; */
  }

  if(node_compare==NULL || getNodeID==NULL){
    perror("参数中的函数指针不能为空");
  }
  ds->node_compare=node_compare;
  ds->getNodeID=getNodeID;
  
}

struct ds_node * findSetNode(struct disjointSet *ds,TID tid){
  int i;

  for(i=0;i<ds->len;i++){
    if(ds->heads[i].len>0){
      struct ds_node *node=ds->heads[i].node;
      while(node!=NULL){
        if(((*ds->node_compare)(tid,(*ds->getNodeID)(node->elem)))==0)
          return node;
        node=node->next;
      }
    }
  }
  return NULL;
}

int newSet(struct disjointSet *ds,T t){
  int i;
  
  for(i=0;i<ds->len;i++){
    if(ds->heads[i].len==0)
      break;
  }
  if(i==ds->len){
    if(ds->len+1>ds->capacity)
      return -1;
    ++ds->len;
  }
  
  struct ds_node *node1=(struct ds_node *)malloc(sizeof(struct ds_node));

  ds->heads[i].len++;
  ds->heads[i].node=node1;
    
  node1->elem=t;
  node1->next=NULL;
  ds->tails[i]=node1;
  node1->headID=i;
  
  return i;
}

int sameSet(struct disjointSet *ds,TID tid1,TID tid2){
  struct ds_node *node1=findSetNode(ds,tid1);
  struct ds_node *node2=findSetNode(ds,tid2);
  if(node1==NULL || node2==NULL)
    return 0;
  int index1=node1->headID;
  int index2=node2->headID;
  
  if(index1>=0 && index1==index2)
    return 1;
  return 0;
}

/*
  把 小集合 合并到 大集合 中
  成功返回1；失败返回0
*/
int unionSet(struct disjointSet *ds,TID tid1,TID tid2){
  int n1,n2,max,min;
  
  struct ds_node *node1=findSetNode(ds,tid1);
  struct ds_node *node2=findSetNode(ds,tid2);
  if(node1==NULL || node2==NULL)
    return 0;
  n1=node1->headID;
  n2=node2->headID;

  if(n1<0 || n2<0)
    return 0;
  
  if(n1!=n2){
    //把小集合的合并到大集合中
    if(ds->heads[n1].len>=ds->heads[n2].len){
      max=n1;
      min=n2;
    }else{
      max=n2;
      min=n1;
    }
    
    struct ds_node *node=ds->heads[min].node;
    ds->tails[max]->next=node;
    while(node!=NULL){
      node->headID=max;
      node=node->next;
    }
    ds->tails[max]=ds->tails[min];
    
    ds->heads[max].len+=ds->heads[min].len;
    ds->heads[min].len=0;
  }
  
  return 1;
}

void releaseSets(struct disjointSet *ds){
  int i;
  struct ds_node *p,*node;
  for(i=0;i<ds->len;i++){
    if(ds->heads[i].len!=0){
      node=ds->heads[i].node;
      while(node!=NULL){
        p=node;
        node=node->next;
        
        free(p);
      }
      ds->heads[i].len=0;
    }
  }
  free(ds->heads);
  free(ds->heads);
}

