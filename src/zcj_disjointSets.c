#include<stdio.h>
#include "zcj_disjointSets.h"

static int sets_capcity=SETS_CAPCITY;
static int sets_len=0;
static struct ds_head head[SETS_CAPCITY];
static struct ds_node *tail[SETS_CAPCITY];

void initSet(int capcity){
  sets_capcity=capcity;

  int i;
  for(i=0;i<sets_capcity;i++){
    head[i].len=0;
    head[i].node=NULL;
  }
}

struct ds_node findSet(T t){
  int i;

  for(i=0;i<sets_len;i++){
    if(head[i].len>0){
      struct ds_node *node=head[i].node;
      while(node!=NULL){
        if(node->elem == t)
          return head[i].node;
      }
    }
  }
  return NULL;
}


