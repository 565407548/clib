#include<stdio.h>

#include"zcj_list.h"

int main(int argc, char *argv[])
{
  struct list l;
  int op,t;

  initList(&l);
  
  while(scanf("%d",&op)==1 && op!=0){
    switch(op){
      case 1://insert
        scanf("%d",&t);
        printf("insert(%d):",t);
        if(insertListNode(&l,t)){
          printf("success\n",t);
        }else{
          printf("fail\n");
        }
        break;
      case 2://delete
        scanf("%d",&t);
        printf("delete(%d):",t);
        if(deleteListNode(&l,t)){
          printf("success\n");
        }else{
          printf("fail\n");
        }
        break;
      case 3://getByValue
        scanf("%d",&t);
        printf("getByValue(%d):",t);
        if(getListNodeByValue(&l,t)){
          printf("success\n");
        }else{
          printf("fail\n");
        }
        break;
      case 4://getByIndex
        scanf("%d",&t);
        printf("getByIndex(%d):",t);
        if(getListNodeByIndex(&l,t)){
          printf("success\n");
        }else{
          printf ("fail\n");
        }
        break;
      default:
        printf("error operator\n");
        break;
    }
  }

  releaseList(&l);
  
  return 0;
}
