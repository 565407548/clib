#include<stdlib.h>
#include<stdio.h>

#include"zcj_tree.h"
#include"zcj_queue.h"
#include"zcj_stack.h"

static void preorderTraversal(struct treeNode *tnode);
static void inorderTraversal(struct treeNode *tnode);
static void postorderTraversal(struct treeNode *tnode);


void initTree(struct tree *at){
  at->root=NULL;
}

struct treeNode *findTreeNode(struct tree *at,TT v){
  struct treeNode * pnode;
  struct queue q;

  initQueue(&q);
  
  if(at->root!=NULL){
    enqueue(&q,at->root);
  }

  while(dequeue(&q,&pnode)){
    if(pnode->value==v){
      return pnode;
    }
    if(pnode->left){
      enqueue(&q,pnode->left);
    }
    if(pnode->right){
      enqueue(&q,pnode->right);
    }
  }
  
  return NULL;
}

int insertTreeNode(struct tree *at,TT parent,int lr,TT child){
  struct treeNode *pnode;
  struct treeNode *cnode;

  cnode=(struct treeNode*)malloc(sizeof(struct treeNode));
  if(cnode==NULL){
    return 0;
  }
  cnode->value=child;
  cnode->left=NULL;
  cnode->right=NULL;

  //空树
  if(at->root==NULL){
    at->root=cnode;
    return 1;
  }
  
  pnode=findTreeNode(at,parent);
  if(pnode==NULL){
    return 0;
  }

  if(lr==LEFTCHILD && pnode->left==NULL){
    pnode->left=cnode;
    return 1;
  }
  else if(lr==RIGHTCHILD && pnode->right==NULL){
    pnode->right=cnode;
    return 1;
  }else{
    return 0;
  }
}

void breadthFirstTraversal(struct tree *at){
  struct treeNode * pnode;
  struct queue q;

  initQueue(&q);
  
  if(at->root!=NULL){
    enqueue(&q,at->root);
  }

  while(dequeue(&q,&pnode)){
    printf("%d ",pnode->value);
    if(pnode->left){
      enqueue(&q,pnode->left);
    }
    if(pnode->right){
      enqueue(&q,pnode->right);
    }
  }
}

void depthFirstTraversal(struct tree *at,int type){
  if(at!=NULL){
    switch(type){
      case PREORDER:
        preorderTraversal(at->root);
        break;
      case INORDER:
        inorderTraversal(at->root);
        break;
      case POSTORDER:
        postorderTraversal(at->root);
        break;
      default:
        printf("不存在这种遍历方式\n");
        break;
    }
  }
}

void releaseTree(struct tree *at){
  struct treeNode * pnode;
  struct queue q;

  initQueue(&q);
  
  if(at->root!=NULL){
    enqueue(&q,at->root);
  }

  while(dequeue(&q,&pnode)){
    if(pnode->left){
      enqueue(&q,pnode->left);
    }
    if(pnode->right){
      enqueue(&q,pnode->right);
    }
    free(pnode);
  }
  
  at->root=NULL;
}


static void preorderTraversal(struct treeNode *tnode){
#if defined(RECURSIVE)
  //递归
  if(tnode!=NULL){
    printf("%d ",tnode->value);

    preorderTraversal(tnode->left);
    preorderTraversal(tnode->right);
  }
#elif defined(NORECURSIVE)
  //非递归
  struct stack s;
  struct treeNode *tmp;
  initStack(&s);

  if(tnode!=NULL){
    push(&s,tnode);
  }

  while(pop(&s,&tmp)){
    printf("%d ",tmp->value);

    //注意此处左右子树入栈的顺序
    if(tmp->right!=NULL){
      push(&s,tmp->right);
    }
    if(tmp->left!=NULL){
      push(&s,tmp->left);
    }
  }
  
  releaseStack(&s);
#endif
}
static void inorderTraversal(struct treeNode *tnode){

#if defined(RECURSIVE)
  //递归
  if(tnode!=NULL){
    inorderTraversal(tnode->left);

    printf("%d ",tnode->value);

    inorderTraversal(tnode->right);
  }
#elif defined(NORECURSIVE)
  //非递归
  struct stack s;
  struct treeNode *tmp;
  initStack(&s);

  if(tnode!=NULL){
    tnode->stage=1;
    push(&s,tnode);
  }

  while(top(&s,&tmp)){
    if(tmp->stage==1){//左右孩子 未处理
      tmp->stage=2;

      if(tmp->left!=NULL){
        tmp->left->stage=1;
        push(&s,tmp->left);
      }
      
    }else{//左孩子已经处理
      printf("%d ",tmp->value);
      pop(&s,NULL);
      
      if(tmp->right!=NULL){
        tmp->right->stage=1;
        push(&s,tmp->right);
      }
    }
  }
  
  releaseStack(&s);
#endif
}
static void postorderTraversal(struct treeNode *tnode){
#if defined(RECURSIVE)
  //递归
  if(tnode!=NULL){
    postorderTraversal(tnode->left);
    postorderTraversal(tnode->right);

    printf("%d ",tnode->value);
  }
#elif defined(NORECURSIVE)
  //非递归
  struct stack s;
  struct treeNode *tmp;
  initStack(&s);

  if(tnode!=NULL){
    tnode->stage=1;
    push(&s,tnode);
  }

  while(top(&s,&tmp)){
    if(tmp->stage==1){//左右还是 未处理
      tmp->stage++;
      if(tmp->left!=NULL){
        tmp->left->stage=1;
        push(&s,tmp->left);
      }
    }else if(tmp->stage==2){//左孩子 已处理； 右孩子 未处理
      tmp->stage++;
      if(tmp->right!=NULL){
        tmp->right->stage=1;
        push(&s,tmp->right);
      }
    }else{//左右孩子 已处理
      printf("%d ",tmp->value);
      pop(&s,NULL);
    }
  }
  
  releaseStack(&s);
#endif
}
