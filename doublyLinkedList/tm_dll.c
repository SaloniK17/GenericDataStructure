#ifndef __TM_DLL_C
#define __TM_DLL_C 123
#include<stdlib.h>
#include<tm_dll.h>
#include<stdio.h>
DoublyLinkedList*createDoublyLinkedList(bool* success)
{
if(success)*success=false;
DoublyLinkedList*doublyLinkedList;
doublyLinkedList=(DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
if(doublyLinkedList==NULL)return NULL;
doublyLinkedList->start=NULL;
doublyLinkedList->end=NULL;
doublyLinkedList->size=0;
if(success)*success=true;
return doublyLinkedList;
}
void addInToDoublyLinkedList(DoublyLinkedList*doublyLinkedList,void*ptr,bool* success)
{
DoublyLinkedListNode*node;
if(success)*success=false;
if(doublyLinkedList==NULL)return;
node=(DoublyLinkedListNode*)malloc(sizeof(DoublyLinkedListNode));
if(node==NULL)return;
node->ptr=ptr;
node->next=NULL;
node->privious=NULL;
if(doublyLinkedList->start==NULL)
{
doublyLinkedList->start=node;
doublyLinkedList->end=node;
}
else
{
node->privious=doublyLinkedList->end;
doublyLinkedList->end->next=node;
doublyLinkedList->end=node;
}
if(success)*success=true;
doublyLinkedList->size++;
return;
}
void insertInToDoublyLinkedList(DoublyLinkedList*doublyLinkedList,int index,void* ptr,bool* success)
{
DoublyLinkedListNode*p1,*t;
int x;
if(success)*success=true;
if(doublyLinkedList==NULL)return;
if(index<0||index>doublyLinkedList->size)return;
x=0;
p1=doublyLinkedList->start;
while(x<index)
{
p1=p1->next;
x++;
}
t=(DoublyLinkedListNode*)malloc(sizeof(DoublyLinkedListNode));
if(t==NULL)return;
t->ptr=ptr;
t->next=NULL;
t->privious=NULL;
if(p1==NULL)
{
addInToDoublyLinkedList(doublyLinkedList,ptr,success);
return;
}
if(p1==doublyLinkedList->start)
{
t->next=doublyLinkedList->start;
doublyLinkedList->start->privious=t;
doublyLinkedList->start=t;
if(success)*success=true;
doublyLinkedList->size++;
return;
}
t->next=p1;
t->privious=p1->privious;
p1->privious->next=t;
p1->privious=t;
if(success)*success=true;
doublyLinkedList->size++;
return;
}
void* removeFromDoublyLinkedList(DoublyLinkedList*doublyLinkedList,int index,bool* success)
{
void*ptr;
DoublyLinkedListNode *p1;
int x;
if(success)*success=false;
if(doublyLinkedList==NULL||doublyLinkedList->start==NULL)return NULL;
if(index<0&&index>=doublyLinkedList->size)return NULL;
x=0;
p1=doublyLinkedList->start;
while(x<index)
{
p1=p1->next;
x++;
}
ptr=p1->ptr;
if(p1==doublyLinkedList->start&&p1==doublyLinkedList->end)
{
doublyLinkedList->start=NULL;
doublyLinkedList->end=NULL;
}
else if(p1==doublyLinkedList->start)
{
doublyLinkedList->start=p1->next;
doublyLinkedList->start->privious=NULL;
}
else if(p1==doublyLinkedList->end)
{
doublyLinkedList->end=p1->privious;
doublyLinkedList->end->next=NULL;
}
else
{
p1->privious->next=p1->next;
p1->next->privious=p1->privious;
}
free(p1);
doublyLinkedList->size--;
if(success)*success=true;
return ptr;
}
void* getFromDoublyLinkedList(DoublyLinkedList*doublyLinkedList,int index,bool* success)
{
int x;
DoublyLinkedListNode*node;
if(success)*success=false;
if(doublyLinkedList==NULL||doublyLinkedList->start==NULL)return NULL;
if(index<0||index>=getSizeOfDoublyLinkedList(doublyLinkedList))return NULL;
x=0;
node=doublyLinkedList->start;
while(x<index&&node!=NULL)
{
node=node->next;
x++;
}
if(success)*success=true;
return node->ptr;
}
int getSizeOfDoublyLinkedList(DoublyLinkedList*doublyLinkedList)
{
if(doublyLinkedList==NULL)return 0;
return doublyLinkedList->size;
}
void destroyDoublyLinkedList(DoublyLinkedList*doublyLinkedList)
{
if(doublyLinkedList==NULL)return;
clearDoublyLinkedList(doublyLinkedList);
free(doublyLinkedList);
}
void clearDoublyLinkedList(DoublyLinkedList*doublyLinkedList)
{
DoublyLinkedListNode*node;
if(doublyLinkedList==NULL)return;
while(doublyLinkedList->start!=NULL)
{
node=doublyLinkedList->start;
doublyLinkedList->start=node->next;
if(doublyLinkedList->start!=NULL)doublyLinkedList->start->privious=NULL;
free(node);
}
doublyLinkedList->end=NULL;
doublyLinkedList->size=0;
return;
}
void appendInToDoublyLinkedList(DoublyLinkedList*targetDoublyLinkedList,DoublyLinkedList*sourceDoublyLinkedList,bool* success)
{
DoublyLinkedListNode *sp,*ed,*node,*t;
bool done;
if(success)*success=false;
if(targetDoublyLinkedList==NULL)return;
if(sourceDoublyLinkedList==NULL||sourceDoublyLinkedList->start==NULL)
{
if(success)*success=true;
return;
}
done=true;
sp=NULL;
ed=NULL;
t=sourceDoublyLinkedList->start;
while(t!=NULL)
{
node=(DoublyLinkedListNode*)malloc(sizeof(DoublyLinkedListNode));
if(node==NULL)
{
done=false;
break;
}
node->ptr=t->ptr;
node->privious=NULL;
node->next=NULL;
if(sp==NULL&&ed==NULL)
{
sp=node;
ed=node;
}
else
{
ed->next=node;
node->privious=ed;
ed=node;
}
t=t->next;
}
if(done==false)
{
while(sp!=NULL)
{
node=sp;
sp=sp->next;
free(node);
}
return;
}
if(targetDoublyLinkedList->start==NULL)
{
targetDoublyLinkedList->start=sp;
targetDoublyLinkedList->end-ed;
}
else
{
targetDoublyLinkedList->end->next=sp;
sp->privious=targetDoublyLinkedList->end;
targetDoublyLinkedList->end=ed;
}
targetDoublyLinkedList->size+=sourceDoublyLinkedList->size;
if(success)*success=true;
return;
}

DoublyLinkedListIterator getDoublyLinkedListIterator(DoublyLinkedList*doublyLinkedList,bool *success)
{
DoublyLinkedListIterator doublyLinkedListIterator;
doublyLinkedListIterator.node=NULL;
if(*success)*success=false;
if(doublyLinkedList==NULL)return doublyLinkedListIterator;
if(doublyLinkedList->start==NULL)
{
if(success)*success=true;
return doublyLinkedListIterator;
}
if(success)*success=true;
doublyLinkedListIterator.node=doublyLinkedList->start;
return doublyLinkedListIterator;
}
bool hasNextElementInDoublyLinkedList(DoublyLinkedListIterator*doublyLinkedListIterator)
{
if(doublyLinkedListIterator==NULL)return false;
if(doublyLinkedListIterator->node==NULL)return false;
return true;
}
void* getNextElementFromDoublyLinkedList(DoublyLinkedListIterator*doublyLinkedListIterator,bool *success)
{
void* ptr;
if(success)*success=false;
if(doublyLinkedListIterator==NULL)return NULL;
if(doublyLinkedListIterator->node==NULL)return NULL;
ptr=doublyLinkedListIterator->node->ptr;
doublyLinkedListIterator->node=doublyLinkedListIterator->node->next; 
if(success)*success=true;
return ptr;
}
DoublyLinkedListIterator getDoublyLinkedListReverseIterator(DoublyLinkedList*doublyLinkedList,bool *success)
{
DoublyLinkedListIterator doublyLinkedListIterator;
doublyLinkedListIterator.node=NULL;
if(success)*success=false;
if(doublyLinkedList==NULL)return doublyLinkedListIterator;
if(doublyLinkedList->end==NULL)
{
if(success)*success=true;
return doublyLinkedListIterator;
}
if(success)*success=true;
doublyLinkedListIterator.node=doublyLinkedList->end;
return doublyLinkedListIterator;
}
void* getNextElementFromReverseDoublyLinkedList(DoublyLinkedListIterator*doublyLinkedListIterator,bool *success)
{
void*ptr;
ptr=NULL;
if(success)*success=false;
if(doublyLinkedListIterator==NULL||doublyLinkedListIterator->node==NULL)return ptr;
ptr=doublyLinkedListIterator->node->ptr;
doublyLinkedListIterator->node=doublyLinkedListIterator->node->privious;
if(success)*success=true;
return ptr;
}
#endif
