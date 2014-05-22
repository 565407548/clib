#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"zcj_queue.h"

/*
跳马步问题：
通过跳马步，从一个点跳到另一个点
 */

#define N 12

static char map[N][N];

/*
struct point{
  int x;
  int y;
};

struct node{
  struct point *p;
  int level;
  struct node *parent;
};
*/
int comparePoint(struct point *p1,struct point *p2){
  return (p1->x==p2->x) && (p1->y==p2->y);
}

void printLoop(struct node *n){
  if(n->parent){
    printLoop(n->parent);
  }
  printf("(%d,%d) ",n->p->x,n->p->y);
}

struct point *nextPoint(struct point *p,int dx,int dy){
  int x,y;
  struct point *np=NULL;
      
  x=p->x+dx;
  y=p->y+dy;
  
  if(x>=0 && x<N && y>=0 && y<N && map[x][y]==0){
    map[x][y]=1;
    np=(struct point*)malloc(sizeof(struct point));
    np->x=x;
    np->y=y;
  }
  return np;
}

struct node *nextNode(struct node *parent,int dx,int dy){
  struct point *p=NULL;
  struct node *n1=NULL;
  
  if(p=nextPoint(parent->p,dx,dy)){
    n1=(struct node*)malloc(sizeof(struct node));
    n1->p=p;
    n1->level=parent->level+1;
    n1->parent=parent;
  }
  
  return n1;
}

void jumpHorse(struct point *start,struct point *end){
  int r,c;
  struct queue q1,q2;
  struct node *n1,*n2;
  
  for(r=0;r<N;r++){
    for(c=0;c<N;c++){
      map[r][c]=0;
    }
  }

  initQueue(&q1);
  initQueue(&q2);

  n1=(struct node*)malloc(sizeof(struct node));
  n1->p=start;
  n1->level=0;
  n1->parent=NULL;
  enqueue(&q1,n1);

  while(dequeue(&q1,&n2)){
    enqueue(&q2,n2);
    
    if(comparePoint(n2->p,end)){
      printLoop(n2);
      break;
    }else{
      if(n1=nextNode(n2,1,-2)){
        enqueue(&q1,n1);
      }
      if(n1=nextNode(n2,2,-1)){
        enqueue(&q1,n1);
      }
      if(n1=nextNode(n2,2,1)){
        enqueue(&q1,n1);
      }
      if(n1=nextNode(n2,1,2)){
        enqueue(&q1,n1);
      }
      if(n1=nextNode(n2,-1,2)){
        enqueue(&q1,n1);
      }
      if(n1=nextNode(n2,-2,1)){
        enqueue(&q1,n1);
      }
      if(n1=nextNode(n2,-1,-2)){
        enqueue(&q1,n1);
      }
      if(n1=nextNode(n2,-2,-1)){
        enqueue(&q1,n1);
      }
    }
  }

  while(dequeue(&q1,&n2)){
    free(n2);
  }
  while(dequeue(&q2,&n2)){
    free(n2);
  }
  releaseQueue(&q1);
  releaseQueue(&q2);
}

int main(int argc, char *argv[])
{
  struct point start,end;

  while(scanf("%d%d%d%d",&start.x,&start.y,&end.x,&end.y)==4){
    printf("(%d,%d)->(%d,%d):",start.x,start.y,end.x,end.y);
    jumpHorse(&start,&end);
    printf("\n");
  }
  
  return 0;
}







