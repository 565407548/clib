#include<stdio.h>

#include"zcj_stack.h"

int main(int argc, char *argv[])
{
  int i,op,capacity,t;
  struct stack s;
  
  scanf("%d",&capacity);
  initStack(&s,capacity);

  while(scanf("%d",&op)==1 && op!=0){
    switch(op){
      case 1://top
        if(top(&s,&t)){
          printf("top:%d\n",t);
        }
        else{
          printf("top:%s\n","no elem");
        }
        break;
      case 2://pop
        if(pop(&s,&t)){
          printf("pop:%d\n",t);
        }else{
          printf("%s\n","pop:no elem,can't pop");
        }
        break;
      case 3://push
        scanf("%d",&t);
        if(push(&s,t)){
          printf("push:%d\n",t);
        }else{
          printf("%s\n","push:no capacity for push");
        }
        break;
      default:
        printf("error operator\n");
    }
  }

  releaseStack(&s);
  
  return 0;
}
