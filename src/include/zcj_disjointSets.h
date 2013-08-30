#define SETS_CAPCITY 100
#define T int

struct ds_node{
  T elem;
  struct ds_node *next;
  struct ds_node *id;
};

struct ds_head{
  int len;
  struct ds_node *node;
};

void initSet(int sets_len);
void makeSet(T t);
struct ds_node findSet(T t);
int sameSet(T t1,T t2);
void unionSet(T t1,T t2);
