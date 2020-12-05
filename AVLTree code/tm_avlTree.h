#ifndef __TM__AVL_TREE_H
#define __TM__AVL_TREE_H 123;
#include<tm_stack.h>
#include<tm_queue.h>
typedef struct __$_tm_Avl_tree_node
{
void*ptr;
struct __$_tm_Avl_tree_node *left,*right;
}AvlTreeNode;

typedef struct __$_tm_Avl_tree
{
int (*predicate)(void *,void*);
struct __$_tm_Avl_tree_node *start;
int size;
}AvlTree;

typedef struct __$_tm_Avl_tree_InOrder_Iterator
{
AvlTreeNode* node;
Stack *stack;
}AvlTreeInOrderIterator;

typedef struct __$_tm_Avl_tree_PreOrder_Iterator
{
AvlTreeNode* node;
Stack *stack;
}AvlTreePreOrderIterator;

typedef struct __$_tm_Avl_tree_PostOrder_Iterator
{
AvlTreeNode* node;
Stack *stack;
}AvlTreePostOrderIterator;

typedef struct __$_tm_Avl_tree_LevelOrder_Iterator
{
AvlTreeNode* node;
Queue *queue;
}AvlTreeLevelOrderIterator;

AvlTree* createAvlTree(int (*predicate)(void *,void*),bool*success);
void insertInToAvlTree(AvlTree*avlTree,void*ptr,bool*success);
void* removeFromAvlTree(AvlTree*avlTree,void *ptr,bool*success);
void* getFromAvlTree(AvlTree*avlTree,void* ptr,bool*success);
AvlTreeInOrderIterator getAvlTreeInOrderIterator(AvlTree*avlTree,bool *success);
bool hasNextInOrderElementInAvlTree(AvlTreeInOrderIterator*avlTreeInOrderIterator);
void* getNextInOrderElementFromAvlTree(AvlTreeInOrderIterator*avlTreeInOrderIterator,bool*success);
AvlTreePreOrderIterator getAvlTreePreOrderIterator(AvlTree*avlTree,bool *success);
bool hasNextPreOrderElementInAvlTree(AvlTreePreOrderIterator*avlTreePreOrderIterator);
void* getNextPreOrderElementFromAvlTree(AvlTreePreOrderIterator*avlTreePreOrderIterator,bool*success);
AvlTreePostOrderIterator getAvlTreePostOrderIterator(AvlTree*avlTree,bool *success);
bool hasNextPostOrderElementInAvlTree(AvlTreePostOrderIterator*avlTreePostOrderIterator);
void* getNextPostOrderElementFromAvlTree(AvlTreePostOrderIterator*avlTreePostOrderIterator,bool*success);
int getSizeOfAvlTree(AvlTree*avlTree);
int getHeightOfAvlTree(AvlTree*avlTree);
void clearAvlTree(AvlTree*avlTree);
void destroyAvlTree(AvlTree*avlTree);
void balanceAvlTree(AvlTree*avlTree,Stack*stack);
int heightOfAvlTree(AvlTreeNode*avlTreeNode);
void* getNextLevelOrderElementFromAvlTree(AvlTreeLevelOrderIterator*avlTreeLevelOrderIterator,bool*success);
bool hasNextLevelOrderElementInAvlTree(AvlTreeLevelOrderIterator*avlTreeLevelOrderIterator);
AvlTreeLevelOrderIterator getAvlTreeLevelOrderIterator(AvlTree *avlTree,bool *success);
#endif