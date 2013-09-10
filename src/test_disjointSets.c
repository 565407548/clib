#include <stdio.h>
#include <stdlib.h>

#include "../include/zcj_disjointSets.h"

//返回节点标识
TID getNodeID(T t){
  return t.id;
}

//根据节点标识进行比较
int node_compare(const TID t1,const TID t2){
  return t1-t2;
}

int main(int argc, char *argv[])
{
  int i,t1,t2,capacity;
  struct disjointSet ds;
  
  scanf("%d",&capacity);
  
  initSet(&ds,capacity,getNodeID,node_compare);
  for(i=0;i<capacity;i++){
    T node;
    scanf("%d%s",&node.id,node.desc);
    newSet(&ds,node);
  }

  while(scanf("%d%d",&t1,&t2)==2 && t1>0 && t2>0){
    unionSet(&ds,t1,t2);
  }

  findSetNode(&ds,t1);
  sameSet(&ds,1,6);
  
  return 0;
}
