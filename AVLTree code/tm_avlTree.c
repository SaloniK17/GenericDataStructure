#ifndef __TM__AVL_TREE_C
#define __TM__AVL_TREE_C 123
#include<stdio.h>
#include<tm_stack.h>
#include<tm_queue.h>
#include<tm_avlTree.h>
#include<stdlib.h>
AvlTree* createAvlTree(int(*predicate)(void*,void*),bool*success)
{
AvlTree*avlTree;
if(success)*success=false;
avlTree=(AvlTree*)malloc(sizeof(AvlTree));
if(avlTree==NULL)return NULL;
avlTree->start=NULL;
avlTree->size=0;
avlTree->predicate=predicate;
if(success)*success=true;
return avlTree;
}
int heightOfAvlTree(AvlTreeNode*avlTreeNode)
{
int leftHeight,rightHeight;
if(avlTreeNode==NULL)return 0;
leftHeight=heightOfAvlTree(avlTreeNode->left);
rightHeight=heightOfAvlTree(avlTreeNode->right);
if(leftHeight>rightHeight)return leftHeight+1;
return rightHeight+1;
}
void balanceAvlTree(AvlTree*avlTree,Stack*stack)
{
int success;
int lh,rh,diff;
AvlTreeNode *lc,*rc,*rclc,*lcrc,*root,**p2p,*parent;
if(stack==NULL)return;
if(isStackEmpty(stack))return;
while(!isStackEmpty(stack))
{
root=(AvlTreeNode*)popFromStack(stack,&success);
if(!success)return;
lh=heightOfAvlTree(root->left);
rh=heightOfAvlTree(root->right);
diff=lh-rh;
if(diff>=-1&&diff<=1)continue;
if(isStackEmpty(stack))p2p=&(avlTree->start);
else
{
parent=(AvlTreeNode*)elementAtTopOfStack(stack,&success);
if(!success)return;
if(parent->left==root)p2p=&(parent->left);
else p2p=&(parent->right);
}
if(rh>lh)
{
rc=root->right;
if(heightOfAvlTree(rc->left)>heightOfAvlTree(rc->right))
{
rclc=rc->left;
rc->left=rclc->right;
rclc->right=rc;
root->right=rclc;
rc=root->right;
}
root->right=rc->left;
rc->left=root;
*p2p=rc;
}
else
{
lc=root->left;
if(heightOfAvlTree(lc->left)<heightOfAvlTree(lc->right))
{
lcrc=lc->right;
lc->right=lcrc->left;
lcrc->left=lc;
root->left=lcrc;
lc=root->left;
}
root->left=lc->right;
lc->right=root;
*p2p=lc;
}
}//stack empty loop end here
return;
}
void insertInToAvlTree(AvlTree*avlTree,void*ptr,bool *success)
{
int weight;
AvlTreeNode *node,*j;
Stack *stack;
if(success)*success=false;
node=(AvlTreeNode*)malloc(sizeof(AvlTreeNode));
if(node==NULL)return;
node->ptr=ptr;
node->left=NULL;
node->right=NULL;
if(avlTree->start==NULL)
{
avlTree->start=node;
avlTree->size++;
if(success)*success=true;
return;
}
stack=createStack(success);
if(*success==false) return;
j=avlTree->start;
while(1)
{
weight=avlTree->predicate(ptr,j->ptr);
if(weight==0)
{
if(success)*success=false;
destroyStack(stack);
free(node);
return;
}
pushOnStack(stack,(void*)j,success);
if(*success==false)
{
destroyStack(stack);
return;
}
if(weight<0)
{
if(j->left==NULL)
{
j->left=node;
break;
}
else j=j->left;
}
else
{
if(j->right==NULL)
{
j->right=node;
break;
}
else j=j->right;
}
}
avlTree->size++;
if(success)*success=true;
balanceAvlTree(avlTree,stack);
destroyStack(stack);
return;
}
void* removeFromAvlTree(AvlTree*avlTree,void*ptr,bool *success)
{
void*element,*foundptr;
Queue*queue;
Stack*stack;
int weight;
AvlTreeNode *t,*j,*e,*f;
if(success)*success=false;
if(avlTree==NULL||avlTree->start==NULL)return NULL;
if(avlTree->size==0)return NULL;
t=avlTree->start;
stack=createStack(success);
if(success==false)return NULL;
while(t!=NULL)
{
weight=avlTree->predicate(ptr,t->ptr);
if(weight==0)break;
pushOnStack(stack,(void*)t,success);
if(success==false)
{
destroyStack(stack);
return NULL;
}
j=t;
if(weight<0)t=t->left;
else t=t->right;
}
if(t==NULL)
{
destroyStack(stack);
return NULL;
}
foundptr=t->ptr;
if(t->right==NULL&&t->left==NULL)
{
if(t==avlTree->start)avlTree->start=NULL;
else if(j->left==t)j->left=NULL;
else j->right=NULL;
}
else
{
queue=createQueue(success);
if(success==false)
{
destroyStack(stack);
return NULL;
}
if(t->right!=NULL)
{
for(e=t->right;e->left!=NULL;e=e->left)
{
f=e;
addInToQueue(queue,(void*)e,success);
if(success==false)
{
destroyStack(stack);
destroyQueue(queue);
return NULL;
}
}
pushOnStack(stack,(void*)e,success);
if(success==false)
{
destroyStack(stack);
destroyQueue(queue);
return NULL;
}
if(e==t->right)
{
e->left=t->left;
}
else
{
f->left=e->right;
e->right=t->right;
e->left=t->left;
}
if(avlTree->start==t)avlTree->start=e;
else if(j->left==t)j->left=e;
else j->right=e;
}
else 
{
for(e=t->left;e->right!=NULL;e=e->right)
{
f=e;
addInToQueue(queue,(void*)e,success);
if(success==false)
{
destroyStack(stack);
destroyQueue(queue);
return NULL;
}
}
pushOnStack(stack,(void*)e,success);
if(success==false)
{
destroyStack(stack);
destroyQueue(queue);
return NULL;
}
if(e!=t->left)
{
f->right=e->left;
e->left=t->left;
}
if(avlTree->start==t)avlTree->start=e;
else if(j->left==t)j->left=e;
else j->right=e;
}
while(!isQueueEmpty(queue))
{
element=removeFromQueue(queue,success);
if(success==false)
{
destroyStack(stack);
destroyQueue(queue);
return NULL;
}
pushOnStack(stack,element,success);
if(success==false)
{
destroyStack(stack);
destroyQueue(queue);
return NULL;
}
}
}
free(t);
avlTree->size--;
balanceAvlTree(avlTree,stack);
destroyStack(stack);
if(success)*success=true;
return foundptr;
}
void* getFromAvlTree(AvlTree*avlTree,void* ptr,bool*success)
{
void* element;
AvlTreeNode *j;
int weight;
if(success)*success=false;
if(avlTree==NULL||avlTree->start==NULL)return NULL;
j=avlTree->start;
while(j!=NULL)
{
weight=avlTree->predicate(ptr,j->ptr);
if(weight==0)
{
if(success)*success=true;
return j->ptr;
}
if(weight<0)j=j->left;
else j=j->right;
}
return NULL;
}
AvlTreeInOrderIterator getAvlTreeInOrderIterator(AvlTree*avlTree,bool *success)
{
AvlTreeInOrderIterator avlTreeInOrderIterator;
AvlTreeNode *j,*t;
avlTreeInOrderIterator.node=NULL;
avlTreeInOrderIterator.stack=NULL;
if(success)*success=false;
if(avlTree==NULL) return avlTreeInOrderIterator;
if(avlTree->start==NULL)
{
if(success)*success=true;
return avlTreeInOrderIterator;
}
avlTreeInOrderIterator.stack=createStack(success);
if(success==false) return avlTreeInOrderIterator;
t=avlTree->start;
while(t!=NULL)
{
pushOnStack(avlTreeInOrderIterator.stack,(void*)t,success);
if(success==false)
{
destroyStack(avlTreeInOrderIterator.stack);
avlTreeInOrderIterator.stack=NULL;
return avlTreeInOrderIterator;
}
t=t->left;
}
avlTreeInOrderIterator.node=(AvlTreeNode*)popFromStack(avlTreeInOrderIterator.stack,success);
if(success==false)
{
destroyStack(avlTreeInOrderIterator.stack);
avlTreeInOrderIterator.stack=NULL;
return avlTreeInOrderIterator;
}
return avlTreeInOrderIterator;
}
bool hasNextInOrderElementInAvlTree(AvlTreeInOrderIterator*avlTreeInOrderIterator)
{
if(avlTreeInOrderIterator==NULL||avlTreeInOrderIterator->node==NULL)return false;
return true;
}
void* getNextInOrderElementFromAvlTree(AvlTreeInOrderIterator* avlTreeInOrderIterator,bool*success)
{
void* element;
AvlTreeNode*j,*t;
if(success)*success=false;
if(avlTreeInOrderIterator==NULL||avlTreeInOrderIterator->node==NULL)return NULL;
j=avlTreeInOrderIterator->node;
t=j->right;
while(t!=NULL)
{
pushOnStack(avlTreeInOrderIterator->stack,(void*)t,success);
if(success==false)
{
destroyStack(avlTreeInOrderIterator->stack);
avlTreeInOrderIterator->node=NULL;
avlTreeInOrderIterator->stack=NULL;
if(success)*success=true;
return j->ptr;
}
t=t->left;
}
if(isStackEmpty(avlTreeInOrderIterator->stack))
{
destroyStack(avlTreeInOrderIterator->stack);
avlTreeInOrderIterator->node=NULL;
avlTreeInOrderIterator->stack=NULL;
}
else
{
avlTreeInOrderIterator->node=(AvlTreeNode*)popFromStack(avlTreeInOrderIterator->stack,success);                                                        
if(success==false)
{
destroyStack(avlTreeInOrderIterator->stack);
avlTreeInOrderIterator->node=NULL;
avlTreeInOrderIterator->stack=NULL;
if(success)*success=true;
return j->ptr;
}
}
if(success)*success=true;
return j->ptr;
}
int getSizeOfAvlTree(AvlTree*avlTree)
{
if(avlTree==NULL||avlTree->start==NULL)return 0;
return avlTree->size;
}
int getHeightOfAvlTree(AvlTree*avlTree)
{
int x;
x=heightOfAvlTree(avlTree->start);
return x;
}
void clearAvlTree(AvlTree*avlTree)
{
int succ;
void*x;
AvlTreeInOrderIterator iterator;
if(avlTree==NULL||avlTree->start==NULL)return;
iterator=getAvlTreeInOrderIterator(avlTree,&succ);
while(hasNextInOrderElementInAvlTree(&iterator))
{
x=getNextInOrderElementFromAvlTree(&iterator,&succ);
if(succ==false)return;
removeFromAvlTree(avlTree,x,&succ);
}
avlTree->start=NULL;
return;
}
void destroyAvlTree(AvlTree*avlTree)
{
if(avlTree==NULL)return;
clearAvlTree(avlTree);
free(avlTree);
return;
}
AvlTreePreOrderIterator getAvlTreePreOrderIterator(AvlTree *avlTree,bool *success)
{
AvlTreePreOrderIterator avlTreePreOrderIterator;
avlTreePreOrderIterator.node=NULL;
avlTreePreOrderIterator.stack=NULL;
if(success)*success=false;
if(avlTree==NULL)return avlTreePreOrderIterator;
if(avlTree->start==NULL)
{
if(success)*success=true;
return avlTreePreOrderIterator;
}
avlTreePreOrderIterator.stack=createStack(success);
if(!success)return avlTreePreOrderIterator;
avlTreePreOrderIterator.node=avlTree->start;
if(success)*success=true;
return avlTreePreOrderIterator;
}
bool hasNextPreOrderElementInAvlTree(AvlTreePreOrderIterator*avlTreePreOrderIterator)
{
if(avlTreePreOrderIterator==NULL||avlTreePreOrderIterator->node==NULL)return false;
return true;
}
void* getNextPreOrderElementFromAvlTree(AvlTreePreOrderIterator*avlTreePreOrderIterator,bool*success)
{
AvlTreeNode *t;
if(success)*success=false;
if(avlTreePreOrderIterator==NULL||avlTreePreOrderIterator->node==NULL)return NULL;
t=avlTreePreOrderIterator->node;
if(t->right!=NULL)
{
pushOnStack(avlTreePreOrderIterator->stack,(void*)t->right,success);
if(*success==false)
{
destroyStack(avlTreePreOrderIterator->stack);
avlTreePreOrderIterator->stack=NULL;
avlTreePreOrderIterator->node=NULL;
if(success)*success=true;
return t->ptr;
}
}
if(t->left!=NULL)
{
pushOnStack(avlTreePreOrderIterator->stack,(void*)t->left,success);
if(*success==false)
{
destroyStack(avlTreePreOrderIterator->stack);
avlTreePreOrderIterator->stack=NULL;
avlTreePreOrderIterator->node=NULL;
if(success)*success=true;
return t->ptr;
}
}
if(isStackEmpty(avlTreePreOrderIterator->stack))
{
destroyStack(avlTreePreOrderIterator->stack);
avlTreePreOrderIterator->stack=NULL;
avlTreePreOrderIterator->node=NULL;
}
else
{
avlTreePreOrderIterator->node=(AvlTreeNode*)popFromStack(avlTreePreOrderIterator->stack,success);
if(*success==false)
{
destroyStack(avlTreePreOrderIterator->stack);
avlTreePreOrderIterator->stack=NULL;
avlTreePreOrderIterator->node=NULL;
}
}
if(success)*success=true;
return t->ptr;
}
AvlTreePostOrderIterator getAvlTreePostOrderIterator(AvlTree*avlTree,int*success)
{
AvlTreePostOrderIterator avlTreePostOrderIterator;
AvlTreeNode*j;
avlTreePostOrderIterator.node=NULL;
avlTreePostOrderIterator.stack=NULL;
if(success)*success=false;
if(avlTree==NULL)return avlTreePostOrderIterator;
if(avlTree->start==NULL)
{
if(success)*success=true;
return avlTreePostOrderIterator;
}
avlTreePostOrderIterator.stack=createStack(success);
if(!success)
{
if(success)*success=true;
return avlTreePostOrderIterator;
}
j=avlTree->start;
while(1)
{
while(j!=NULL)
{
if(j->right!=NULL)
{
pushOnStack(avlTreePostOrderIterator.stack,(void*)j->right,success);
if(!success)
{
if(success)*success=true;
return avlTreePostOrderIterator;
}
}
pushOnStack(avlTreePostOrderIterator.stack,(void*)j,success);
if(!success)
{
if(success)*success=true;
return avlTreePostOrderIterator;
}
j=j->left;
}
j=(AvlTreeNode*)popFromStack(avlTreePostOrderIterator.stack,success);
if(!success)
{
if(success)*success=true;
return avlTreePostOrderIterator;
}
if(!isStackEmpty(avlTreePostOrderIterator.stack)&&j->right!=NULL&&(AvlTreeNode*)elementAtTopOfStack(avlTreePostOrderIterator.stack,success)==j->right)
{
popFromStack(avlTreePostOrderIterator.stack,success);
if(!success)
{
if(success)*success=true;
return avlTreePostOrderIterator;
}
pushOnStack(avlTreePostOrderIterator.stack,(void*)j,success);
if(!success)
{
if(success)*success=true;
return avlTreePostOrderIterator;
}
j=j->right;
}
else break;
}
avlTreePostOrderIterator.node=j;
if(success)*success=true;
return avlTreePostOrderIterator;
}
bool hasNextPostOrderElementInAvlTree(AvlTreePostOrderIterator*avlTreePostOrderIterator)
{
if(avlTreePostOrderIterator==NULL||avlTreePostOrderIterator->node==NULL)return false;
return true; 
}
void* getNextPostOrderElementFromAvlTree(AvlTreePostOrderIterator*avlTreePostOrderIterator,bool* success)
{
AvlTreeNode*t,*j;
if(success)*success=false;
if(avlTreePostOrderIterator==NULL)return NULL;
if(avlTreePostOrderIterator->node==NULL)return NULL;
j=avlTreePostOrderIterator->node;
if(isStackEmpty(avlTreePostOrderIterator->stack))
{
destroyStack(avlTreePostOrderIterator->stack);
avlTreePostOrderIterator->node=NULL;
avlTreePostOrderIterator->stack=NULL;
if(success)*success=true;
return j->ptr;
}
t=NULL;
while(1)
{
while(t!=NULL)
{
if(t->right!=NULL)
{
pushOnStack(avlTreePostOrderIterator->stack,(void*)t->right,success);
if(!success)
{
destroyStack(avlTreePostOrderIterator->stack);
avlTreePostOrderIterator->node=NULL;
avlTreePostOrderIterator->stack=NULL;
if(success)*success=true;
return j->ptr;
}
}
pushOnStack(avlTreePostOrderIterator->stack,(void*)t,success);
if(!success)
{
destroyStack(avlTreePostOrderIterator->stack);
avlTreePostOrderIterator->node=NULL;
avlTreePostOrderIterator->stack=NULL;
if(success)*success=true;
return j->ptr;
}
t=t->left;
}
t=(AvlTreeNode*)popFromStack(avlTreePostOrderIterator->stack,success);
if(!success)
{
destroyStack(avlTreePostOrderIterator->stack);
avlTreePostOrderIterator->node=NULL;
avlTreePostOrderIterator->stack=NULL;
if(success)*success=true;
return j->ptr;
}
if(!isStackEmpty(avlTreePostOrderIterator->stack)&&t->right!=NULL&&(AvlTreeNode*)elementAtTopOfStack(avlTreePostOrderIterator->stack,success)==t->right)
{
popFromStack(avlTreePostOrderIterator->stack,success);
if(!success)
{
destroyStack(avlTreePostOrderIterator->stack);
avlTreePostOrderIterator->node=NULL;
avlTreePostOrderIterator->stack=NULL;
if(success)*success=true;
return j->ptr;
}
pushOnStack(avlTreePostOrderIterator->stack,t,success);
if(!success)
{
destroyStack(avlTreePostOrderIterator->stack);
avlTreePostOrderIterator->node=NULL;
avlTreePostOrderIterator->stack=NULL;
if(success)*success=true;
return j->ptr;
}
t=t->right;
}
else 
{
break;
}
}
avlTreePostOrderIterator->node=t;
if(success)*success=true;
return j->ptr;
}
AvlTreeLevelOrderIterator getAvlTreeLevelOrderIterator(AvlTree *avlTree,bool *success)
{
AvlTreeLevelOrderIterator avlTreeLevelOrderIterator;
avlTreeLevelOrderIterator.queue=NULL;
avlTreeLevelOrderIterator.node=NULL;
if(success)*success=false;
if(avlTree==NULL)return avlTreeLevelOrderIterator;
if(avlTree->start==NULL)
{
if(success)*success=true;
return avlTreeLevelOrderIterator;
}
avlTreeLevelOrderIterator.queue=createQueue(success);
if(!success)return avlTreeLevelOrderIterator;
avlTreeLevelOrderIterator.node=avlTree->start;
if(success)*success=true;
return avlTreeLevelOrderIterator;
}
bool hasNextLevelOrderElementInAvlTree(AvlTreeLevelOrderIterator*avlTreeLevelOrderIterator)
{
if(avlTreeLevelOrderIterator==NULL||avlTreeLevelOrderIterator->node==NULL)return false;
return true;
}
void* getNextLevelOrderElementFromAvlTree(AvlTreeLevelOrderIterator*avlTreeLevelOrderIterator,bool*success)
{
AvlTreeNode *t,*j;
if(success)*success=false;
if(avlTreeLevelOrderIterator==NULL||avlTreeLevelOrderIterator->node==NULL)return NULL;
t=avlTreeLevelOrderIterator->node;
if(t->left!=NULL)
{
addInToQueue(avlTreeLevelOrderIterator->queue,(void*)t->left,success);
if(!success)
{
destroyQueue(avlTreeLevelOrderIterator->queue);
avlTreeLevelOrderIterator->queue=NULL;
avlTreeLevelOrderIterator->node=NULL;
if(success)*success=true;
return t->ptr;
}
}
if(t->right!=NULL)
{
addInToQueue(avlTreeLevelOrderIterator->queue,(void*)t->right,success);
if(!success)
{
destroyQueue(avlTreeLevelOrderIterator->queue);
avlTreeLevelOrderIterator->queue=NULL;
avlTreeLevelOrderIterator->node=NULL;
if(success)*success=true;
return t->ptr;
}
}
if(isQueueEmpty(avlTreeLevelOrderIterator->queue))
{
destroyQueue(avlTreeLevelOrderIterator->queue);
avlTreeLevelOrderIterator->queue=NULL;
avlTreeLevelOrderIterator->node=NULL;
if(success)*success=true;
return t->ptr;
}
avlTreeLevelOrderIterator->node=(AvlTreeNode*)removeFromQueue(avlTreeLevelOrderIterator->queue,success);
if(!success)
{
destroyQueue(avlTreeLevelOrderIterator->queue);
avlTreeLevelOrderIterator->queue=NULL;
avlTreeLevelOrderIterator->node=NULL;
if(success)*success=true;
return t->ptr;
}
return t->ptr;
}
#endif