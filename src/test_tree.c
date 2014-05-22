#include<stdio.h>

#include"zcj_tree.h"

int main(int argc, char *argv[])
{
  struct tree at;
  int op,lr,parent,child;

  initTree(&at);
  
  while(scanf("%d",&op)==1 && op!=0){
    switch(op){
      case 1://insert node
        scanf("%d%d%d",&parent,&lr,&child);
        printf("insert node(p=%d lr=%d c=%d):",parent,lr,child);
        if(insertTreeNode(&at,parent,lr,child)){
          printf("success\n");
        }else{
          printf("fail\n");
        }
        break;
      case 2://breadfirst traversal
        printf("breadthfirst:");
        breadthFirstTraversal(&at);
        printf("\n");
        break;
      case 3://pre order traversal
        printf("depth preorder:");
        depthFirstTraversal(&at,PREORDER);
        printf("\n");
        break;
      case 4://in order traversal
        printf("depth inorder:");
        depthFirstTraversal(&at,INORDER);
        printf("\n");
        break;
      case 5://post order traversal
        printf("depth postorder:");
        depthFirstTraversal(&at,POSTORDER);
        printf("\n");
        break;
      default:
        printf("error operator\n");
        break;
    }
  }
  
  releaseTree(&at);
  
  return 0;
}
