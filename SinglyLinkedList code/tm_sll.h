#ifndef __TM__SLL_H
#define __TM__SLL_H 123
#include<tm_common.h>
typedef struct __$_tm_sll_node
{
void *ptr;
struct __$_tm_sll_node *next;
}SinglyLinkedListNode;

typedef struct __$_tm_sll
{
struct __$_tm_sll_node *start;
struct __$_tm_sll_node *end;
int size;
}SinglyLinkedList;

typedef struct __$_tm_sll_iterator
{
SinglyLinkedListNode *node;
}SinglyLinkedListIterator;

SinglyLinkedList*createSinglyLinkedList(bool *success);
void addInToSinglyLinkedList(SinglyLinkedList*singlylinkedlist,void*ptr,bool *success);
void insertInToSinglyLinkedList(SinglyLinkedList*singlylinkedlist,int index,void*ptr,bool* success);
void* removeFromSinglyLinkedList(SinglyLinkedList*singLylinkedList,int index,bool* success);
int getSizeOfSinglyLinkedList(SinglyLinkedList*singlylinkedlist);
void* getFromSinglyLinkedList(SinglyLinkedList*singlylinkedlist,int index,bool *success);
void destroySinglyLinkedList(SinglyLinkedList*singlylinkedlist);
void clearSinglyLinkedList(SinglyLinkedList*singlylinkedlist);
void appendInToSinglyLinkedList(SinglyLinkedList*targetSinglyLinkedList,SinglyLinkedList*sourceSinglyLinkedList,bool *success);
SinglyLinkedListIterator getSinglyLinkedListIterator(SinglyLinkedList *singlyLinkedList,bool* success);
bool hasNextElementInSinglyLinkedList(SinglyLinkedListIterator* singlyLinkedListIterator);
void* getNextElementFromSinglyLinkedList(SinglyLinkedListIterator *singlyLinkedListIterator,bool*success);
#endif