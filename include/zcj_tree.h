#ifndef _ZCJ_TREE_H_
#define _ZCJ_TREE_H_

#define T int

#define LEFTCHILD 1
#define RIGHTCHILD 2

#define INORDER 1
#define PREORDER 2
#define POSTORDER 3

struct treeNode{
  T value;
  struct treeNode * left;
  struct treeNode *right;
};

struct tree{
  struct treeNode *root;
};

void initTree(struct tree *at);
struct treeNode *fineTreeNode(struct tree *at,T v);
int insertTreeNode(struct tree *at,T parent,int lr,T child);
void breadthFirstTraversal(struct tree *at);
void depthFirstTraversal(struct tree *at,int type);
void releaseTree(struct tree *at);

#endif /* _ZCJ_TREE_H_ */


