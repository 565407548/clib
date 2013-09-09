#ifndef _ZCJ_DISJOINTSETS_H_
#define _ZCJ_DISJOINTSETS_H_

/*
使用不交集时，需要先根据需求，重新定义的东西：
struct node_type
T
TID

还需要定义:
TID getNodeID(T t);//返回节点标识（注意：不是节点所在集合的标识）
int node_compare(const TID t1,const TID t2);//根据节点标识进行比较
这方面有待优化，如何可以动态指定呢？
 */
struct node_type{
  int id;
  char desc[10];
};
#define T struct node_type
#define TID int


#ifndef MAX
#define MAX(a,b) ((a>b)?(a):(b))
#endif

#ifndef MIN
#define MIN(a,b) ((a<b)?(a):(b))
#endif
#define CAPACITY 100

//不交集中的节点
struct ds_node{
  T elem;
  struct ds_node *next;
  int headID;
};
//不交集集合头部，所有相交的节点共用一个头部
struct ds_head{
  int len;
  struct ds_node *node;
};

void initSet(int capcity,TID (*getNodeID)(T t),int (*node_compare)(const TID, const TID));
//根据指定节点创建一个新不交集，返回不交集的标识（区别于节点标识）
int newSet(T t);
struct ds_node *findSetNode(TID tid);
int sameSet(TID tid1,TID tid2);
int unionSet(TID tid1,TID tid2);
int default_node_compare(const TID t1,const TID t2);

void releaseSets();

#endif /* _ZCJ_DISJOINTSETS_H_ */


