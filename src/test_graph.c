#include<stdio.h>

#include"zcj_graph.h"

int main(int argc, char *argv[])
{
  int op,v1,v2;
  double w;
  struct Graph g;

  initGraph(&g);
  
  while(scanf("%d",&op)==1 && op!=0){
    switch(op){
      case 1://add vertex
        scanf("%d",&v1);
        printf("add vertex(%d):",v1);
        if(addGraphVertex(&g,v1)){
          printf("success\n");
        }else{
          printf("fail\n");
        }
        
        break;
      case 2://delete vertex
        scanf("%d",&v1);
        printf("delete vertex(%d):",v1);
        if(deleteGraphVertex(&g,v1)){
          printf("success\n");
        }else{
          printf("fail\n");
        }
        
        break;
      case 3://get vertex
        scanf("%d",&v1);
        printf("get vertex(%d):",v1);
        if(getGraphVertex(&g,v1)){
          printf("success\n");
        }else{
          printf("fail\n");
        }
        break;
      case 4://add edge
        scanf("%d%d%lf",&v1,&v2,&w);
        printf("add edge(%d-%d:%lf):",v1,v2,w);
        if(addGraphEdge(&g,v1,v2,w)){
          printf("success\n");
        }else{
          printf("fail\n");
        }
        break;
      case 5://delete edge
        scanf("%d%d",&v1,&v2);
        printf("delete edge(%d-%d):",v1,v2);
        if(deleteGraphEdge(&g,v1,v2)){
          printf("success\n");
        }else{
          printf("fail\n");
        }
        break;
      case 6://get edge
        scanf("%d%d",&v1,&v2);
        printf("get edge(%d-%d):",v1,v2);
        if(getGraphEdge(&g,v1,v2)){
          printf("success\n");
        }else{
          printf("fail\n");
        }
        break;
      default:
        printf("error operator\n");
        break;
    }
  }

  releaseGraph(&g);
  
  return 0;
}
