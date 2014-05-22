#include<stdio.h>

#include "zcj_queue.h"

int main(int argc, char *argv[])
{
  struct queue q;
  int t,op;

  /*
  initQueue(&q);

  while(scanf("%d",&op)==1 && op!=0){
    switch(op){
      case 1://enqueue
        scanf("%d",&t);
        if(enqueue(&q,t)){
          printf("enqueue:%d\n",t);
        }else{
          printf("enqueue(%d):error\n",t);
        }
        break;
      case 2:
        if(dequeue(&q,&t)){
          printf("dequeue:%d\n",t);
        }else{
          printf("dequeue:no elem dequeue\n");
        }
        break;
      default:
        printf("error operator\n");
        break;
    }
  }
  
  releaseQueue(&q);
  */
  return 0;
}
