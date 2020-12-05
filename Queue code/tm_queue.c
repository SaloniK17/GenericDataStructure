#ifndef __TM_QUEUE_C
#define __TM_QUEUE_C 123
#include<tm_queue.h>
#include<stdlib.h>
Queue* createQueue(bool *success)
{
Queue*queue;
SinglyLinkedList*singlyLinkedList;
if(success)*success=false;
singlyLinkedList=createSinglyLinkedList(success);
if(*success==false)return NULL;
queue=(Queue*)malloc(sizeof(Queue));
if(queue==NULL)
{
destroySinglyLinkedList(singlyLinkedList);
if(success)*success=false;
return NULL;
}
queue->singlyLinkedList=singlyLinkedList;
if(success)*success=true;
return queue;
}
void addInToQueue(Queue*queue,void* ptr,bool* success)
{
if(success)*success=false;
if(queue==NULL||queue->singlyLinkedList==NULL)return;
addInToSinglyLinkedList(queue->singlyLinkedList,ptr,success);
return;
}
void* removeFromQueue(Queue*queue,bool* success)
{
void* ptr;
if(success)*success=false;
if(isQueueEmpty(queue))return NULL;
ptr=removeFromSinglyLinkedList(queue->singlyLinkedList,0,success);
return ptr;
}
void* elementAtFrontOfQueue(Queue*queue,bool* success)
{
void* ptr;
if(success)*success=false;
if(isQueueEmpty(queue))return NULL;
ptr=getFromSinglyLinkedList(queue->singlyLinkedList,0,success);
return ptr;
}
bool isQueueEmpty(Queue*queue)
{
if(queue==NULL||queue->singlyLinkedList==NULL||getSizeOfSinglyLinkedList(queue->singlyLinkedList)==0)return true;
return false;
}
void clearQueue(Queue*queue)
{
if(queue==NULL||queue->singlyLinkedList==NULL)return;
clearSinglyLinkedList(queue->singlyLinkedList);
}
void destroyQueue(Queue*queue)
{
if(queue==NULL)return;
if(queue->singlyLinkedList==NULL)
{
free(queue);
return;
}
destroySinglyLinkedList(queue->singlyLinkedList);
free(queue);
return;
}
int getSizeOfQueue(Queue*queue)
{
if(queue==NULL||queue->singlyLinkedList==NULL)return 0;
return getSizeOfSinglyLinkedList(queue->singlyLinkedList);
}
#endif