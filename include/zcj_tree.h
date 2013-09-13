#ifndef _ZCJ_TREE_H_
#define _ZCJ_TREE_H_

//定义该宏，表示深度遍历树时采用递归方式，否则采用非递归方式
#define RECURSIVE
//#define NORECURSIVE

#define TT int

#define LEFTCHILD 1
#define RIGHTCHILD 2

#define INORDER 1
#define PREORDER 2
#define POSTORDER 3

struct treeNode{
  TT value;
  struct treeNode * left;
  struct treeNode *right;
#ifndef RECURSIVE
  int stage;
#endif
};

struct tree{
  struct treeNode *root;
};

void initTree(struct tree *at);
struct treeNode *fineTreeNode(struct tree *at,TT v);
int insertTreeNode(struct tree *at,TT parent,int lr,TT child);
void breadthFirstTraversal(struct tree *at);
void depthFirstTraversal(struct tree *at,int type);
void releaseTree(struct tree *at);

#endif /* _ZCJ_TREE_H_ */


