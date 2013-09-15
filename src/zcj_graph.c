#include<stdlib.h>

#include"zcj_graph.h"

void initGraph(struct Graph *g){
  g->head=NULL;
}

int addGraphVertex(struct Graph *g,TG id){
  struct GraphVertexNode *gVertex;
  
  if((gVertex=getGraphVertex(g,id))!=NULL){
    return 1;
  }

  gVertex=(struct GraphVertexNode *)malloc(sizeof(struct GraphVertexNode));
  if(gVertex==NULL){
    return 0;
  }
  gVertex->id=id;
  gVertex->graphEdge=NULL;
  gVertex->nextGraphVertex=g->head;
  g->head=gVertex;

  return 1; 
}

int deleteGraphVertex(struct Graph *g,TG id){
#if defined(DIRECT)
  //有向图
  //删除边
  //删除顶点
#else
  //无向图
  struct GraphVertexNode *gVertex,*preGVertex;
  struct GraphEdgeNode *gEdge,*nextGEdge;

  preGVertex=NULL;
  gVertex=g->head;
  while(gVertex!=NULL){
    if(gVertex->id==id){
      //删除边
      gEdge=gVertex->graphEdge;
      while(gEdge){
        nextGEdge=gEdge->nextGraphEdge;
        
        deleteGraphEdge(g,gEdge->graphVertex1->id,gEdge->graphVertex2->id);
        
        gEdge=nextGEdge;
      }
      //删除顶点
      if(preGVertex==NULL){
        g->head=gVertex->nextGraphVertex;
      }else{
        preGVertex->nextGraphVertex=gVertex->nextGraphVertex;
      }
      free(gVertex);
      
      break;
    }
    preGVertex=gVertex;
    gVertex=gVertex->nextGraphVertex;
  }
  return 1;
#endif
}

struct GraphVertexNode *getGraphVertex(struct Graph *g,TG id){
  struct GraphVertexNode *gVertex=g->head;

  while(gVertex!=NULL){
    if(gVertex->id==id){
      return gVertex;
    }
    gVertex=gVertex->nextGraphVertex;
  }

  return NULL;
}

#ifdef WEIGHT
//有权途
int addGraphEdge(struct Graph *g,TG id1,TG id2,double weight){
#if defined(DIRECT)
#else
  //无向图
  struct GraphVertexNode *gVertex1=getGraphVertex(g,id1);
  struct GraphVertexNode *gVertex2=getGraphVertex(g,id2);
  struct GraphEdgeNode *gEdge;
  
  if(gVertex1==NULL || gVertex2==NULL){
    return 0;
  }
  if((gEdge=getGraphEdge(g,id1,id2))!=NULL){
    return 1;
  }

  gEdge=(struct GraphEdgeNode*)malloc(sizeof(struct GraphEdgeNode));
  if(gEdge==NULL){
    return 0;
  }

  gEdge->graphVertex1=gVertex1;
  gEdge->graphVertex2=gVertex2;
  gEdge->weight=weight;
  gEdge->nextGraphEdge=gVertex1->graphEdge;
  gVertex1->graphEdge=gEdge;

  gEdge=(struct GraphEdgeNode*)malloc(sizeof(struct GraphEdgeNode));
  if(gEdge==NULL){
    return 0;
  }

  gEdge->graphVertex1=gVertex2;
  gEdge->graphVertex2=gVertex1;
  gEdge->weight=weight;
  gEdge->nextGraphEdge=gVertex2->graphEdge;
  gVertex2->graphEdge=gEdge;
  
  return 1;
#endif
}
#else
int addGraphEdge(struct Graph *g,TG id1,TG id2){
#if defined(DIRECT)
#else
  //无向图
  struct GraphVertexNode *gVertex1=getGraphVertex(g,id1);
  struct GraphVertexNode *gVertex2=getGraphVertex(g,id2);
  struct GraphEdgeNode *gEdge;
  
  if(gVertex1==NULL || gVertex2==NULL){
    return 0;
  }
  if((gEdge=getGraphEdge(g,id1,id2))!=NULL){
    return 1;
  }

  gEdge=(struct GraphEdgeNode*)malloc(sizeof(struct GraphEdgeNode));
  if(gEdge==NULL){
    return 0;
  }

  gEdge->graphVertex1=gVertex1;
  gEdge->graphVertex2=gVertex2;
  gEdge->nextGraphEdge=gVertex1->graphEdge;
  gVertex1->graphEdge=gEdge;

  gEdge=(struct GraphEdgeNode*)malloc(sizeof(struct GraphEdgeNode));
  if(gEdge==NULL){
    return 0;
  }

  gEdge->graphVertex1=gVertex2;
  gEdge->graphVertex2=gVertex1;
  gEdge->nextGraphEdge=gVertex2->graphEdge;
  gVertex2->graphEdge=gEdge;
  
  return 1;
#endif
}

#endif

int deleteGraphEdge(struct Graph *g,TG id1,TG id2){
#if defined(DIRECT)
#else
  struct GraphVertexNode *vertex1=getGraphVertex(g,id1);
  struct GraphVertexNode *vertex2=getGraphVertex(g,id2);
  if(vertex1==NULL || vertex2==NULL){
    return 1;
  }

  struct GraphEdgeNode *preedge,*edge;

  preedge=NULL;
  edge=vertex1->graphEdge;
  while(edge){
    if(edge->graphVertex2==vertex2 /*|| edge->vertex1==vertex2*/){
      if(preedge==NULL){
        vertex1->graphEdge=edge->nextGraphEdge;
      }else{
        preedge->nextGraphEdge=edge->nextGraphEdge;
      }
      free(edge);
      break;
    }
    preedge=edge;
    edge=edge->nextGraphEdge;
  }

  preedge=NULL;
  edge=vertex2->graphEdge;
  while(edge){
    if(edge->graphVertex2==vertex1 /*|| edge->vertex1==vertex1*/){
      if(preedge==NULL){
        vertex2->graphEdge=edge->nextGraphEdge;
      }else{
        preedge->nextGraphEdge=edge->nextGraphEdge;
      }
      free(edge);
      break;
    }
    preedge=edge;
    edge=edge->nextGraphEdge;
  }
 
  return 1;
#endif
}

struct GraphEdgeNode *getGraphEdge(struct Graph *g,TG id1,TG id2){
#if defined(DIRECT)
#else
  struct GraphVertexNode *vertex1=getGraphVertex(g,id1);
  struct GraphVertexNode *vertex2=getGraphVertex(g,id2);
  if(vertex1==NULL || vertex2==NULL){
    return NULL;
  }

  struct GraphEdgeNode *edge=vertex1->graphEdge;
  while(edge){
    if((edge->graphVertex2==vertex2 /*|| edge->vertex1==vertex2*/)
       /*|| (edge->vertex1==vertex1 && edge->vertex2==vertex2)*/){
      return edge;
    }
    edge=edge->nextGraphEdge;
  }
  return NULL;
#endif
}

void releaseGraph(struct Graph *g){
  if(g!=NULL){
    struct GraphVertexNode *vertex;
    struct GraphEdgeNode *edge;

    vertex=g->head;
    while(vertex){
      //删除点的对应边
      edge=vertex->graphEdge;
      while(edge){
        vertex->graphEdge=edge->nextGraphEdge;
        free(edge);
        edge=vertex->graphEdge;
      }
      
      //删除点
      g->head=vertex->nextGraphVertex;
      free(vertex);

      vertex=g->head;
    }
    g->head=NULL;
  }
}

