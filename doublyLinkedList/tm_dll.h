#ifndef __TM_DLL_H
#define __TM_DLL_H
#include<tm_common.h>
typedef struct  __$_tm_dll_node
{
void* ptr;
struct __$_tm_dll_node *next;
struct __$_tm_dll_node *privious;
}DoublyLinkedListNode;
typedef struct __$_tm_dll
{
DoublyLinkedListNode*start;
DoublyLinkedListNode*end;
int size;
}DoublyLinkedList;
typedef struct __$_tm_dll_iterator
{
DoublyLinkedListNode*node;
}DoublyLinkedListIterator;

DoublyLinkedList*createDoublyLinkedList(bool* success);
void addInToDoublyLinkedList(DoublyLinkedList*doublyLinkedList,void*ptr,bool* success);
void insertInToDoublyLinkedList(DoublyLinkedList*doublyLinkedList,int index,void* ptr,bool* success);
void* removeFromDoublyLinkedList(DoublyLinkedList*doublyLinkedList,int index,bool* success);
void* getFromDoublyLinkedList(DoublyLinkedList*doublyLinkedList,int index,bool* success);
int getSizeOfDoublyLinkedList(DoublyLinkedList*doublyLinkedList);
void destroyDoublyLinkedList(DoublyLinkedList*doublyLinkedList);
void clearDoublyLinkedList(DoublyLinkedList*doublyLinkedList);
void appendInToDoublyLinkedList(DoublyLinkedList*targetDoublyLinkedList,DoublyLinkedList*sourceDoublyLinkedList,bool* success);
DoublyLinkedListIterator getDoublyLinkedListIterator(DoublyLinkedList*doublyLinkedList,bool*suucess);
bool hasNextElementInDoublyLinkedList(DoublyLinkedListIterator*doublyLinkedListIterator);
void* getNextElementFromDoublyLinkedList(DoublyLinkedListIterator*doublyLinkedListIterator,bool *success);
DoublyLinkedListIterator getDoublyLinkedListReverseIterator(DoublyLinkedList*doublyLinkedList,bool*suucess);
void* getNextElementFromReverseDoublyLinkedList(DoublyLinkedListIterator*doublyLinkedListIterator,bool *success);

#endif