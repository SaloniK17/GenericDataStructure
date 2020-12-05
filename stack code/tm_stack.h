#ifndef __TM__STACK_H
#define __TM__STACK_H 123
#include<tm_sll.h>
#include<tm_common.h>
typedef struct __$_tm_stack
{
SinglyLinkedList*singlyLinkedList;
}Stack;
Stack* createStack(bool*success);
void pushOnStack(Stack *stack,void*ptr,bool *success);
void*popFromStack(Stack* stack,bool *success);
void*elementAtTopOfStack(Stack*stack,bool *success);
bool isStackEmpty(Stack*stack);
void clearStack(Stack*stack);
void destroyStack(Stack*stack);
int getSizeOfStack(Stack *stack);
#endif