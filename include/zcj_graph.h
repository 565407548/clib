#ifndef _ZCJ_GRAPH_H_
#define _ZCJ_GRAPH_H_

//有向图
//#define DIRECT
//有权图
#define WEIGHT

#define TG int

struct GraphVertexNode{
  TG id;
  struct GraphEdgeNode *graphEdge;
  struct GraphVertexNode *nextGraphVertex;
};

struct GraphEdgeNode{
#ifdef DIRECT
  struct GraphVertexNode *sGraphVertex;
  struct GraphVertexNode *eGraphVertex;
#else
  struct GraphVertexNode *graphVertex1;
  struct GraphVertexNode *graphVertex2;
#endif
#ifdef WEIGHT
  double weight;
#endif
  
  struct GraphEdgeNode *nextGraphEdge;
};

struct Graph{
  struct GraphVertexNode *head;
};

void initGraph(struct Graph *g);

int addGraphVertex(struct Graph *g,TG id);
int deleteGraphVertex(struct Graph *g,TG id);
struct GraphVertexNode *getGraphVertex(struct Graph *g,TG id);

#ifdef WEIGHT
int addGraphEdge(struct Graph *g,TG id1,TG id2,double weight);
#else
int addGraphEdge(struct Graph *g,TG id1,TG id2);
#endif
int deleteGraphEdge(struct Graph *g,TG id1,TG id2);
struct GraphEdgeNode * getGraphEdge(struct Graph *g,TG id1,TG id2);

void releaseGraph(struct Graph *g);

#endif /* _ZCJ_GRAPH_H_ */
