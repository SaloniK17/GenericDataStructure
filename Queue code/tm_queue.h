#ifndef __TM__QUEUE_H
#define __TM__QUEUE_H
#include<tm_common.h>
#include<tm_sll.h>
typedef struct __$_tm_queue
{
SinglyLinkedList*singlyLinkedList;
}Queue;
Queue* createQueue(bool *success);
void addInToQueue(Queue*queue,void* ptr,bool* success);
void* removeFromQueue(Queue*queue,bool* success);
void* elementAtFrontOfQueue(Queue*queue,bool* success);
bool isQueueEmpty(Queue*queue);
void clearQueue(Queue*queue);
void destroyQueue(Queue*queue);
int getSizeOfQueue(Queue*queue);
#endif