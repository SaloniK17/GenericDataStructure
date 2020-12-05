#ifndef __TM_STACK_C
#define __TM_STACK_C 123
#include<tm_stack.h>
#include<stdlib.h>
Stack* createStack(bool*success)
{
SinglyLinkedList*singlyLinkedList;
Stack *stack;
if(success)*success=false;
singlyLinkedList=createSinglyLinkedList(success);
if(*success==false)return NULL;
stack=(Stack*)malloc(sizeof(Stack));
if(stack==NULL)
{
destroySinglyLinkedList(singlyLinkedList);
if(success)*success=false;
return NULL;
}
stack->singlyLinkedList=singlyLinkedList;
if(success)*success=true;
return stack;
}
void pushOnStack(Stack *stack,void* ptr,bool *success)
{
if(success)*success=false;
if(stack==NULL||stack->singlyLinkedList==NULL)return;
insertInToSinglyLinkedList(stack->singlyLinkedList,0,ptr,success);
if(*success==false)
{
destroySinglyLinkedList(stack->singlyLinkedList);
return;
}
if(success)*success=true;
return;
}
void* popFromStack(Stack* stack,bool *success)
{
void* ptr;
if(success)*success=false;
if(isStackEmpty(stack))return NULL;
ptr=removeFromSinglyLinkedList(stack->singlyLinkedList,0,success);
return ptr;
}
void*elementAtTopOfStack(Stack*stack,bool *success)
{
void *ptr;
if(success)*success=false;
if(isStackEmpty(stack))return NULL;
ptr=getFromSinglyLinkedList(stack->singlyLinkedList,0,success);
return ptr;
}
bool isStackEmpty(Stack*stack)
{
if(stack==NULL||stack->singlyLinkedList==NULL)return true;
if(getSizeOfSinglyLinkedList(stack->singlyLinkedList)==0)return true;
return false;
}
void clearStack(Stack*stack)
{
if(stack==NULL)return;
if(stack->singlyLinkedList==NULL)return;
clearSinglyLinkedList(stack->singlyLinkedList);
}
void destroyStack(Stack*stack)
{
if(stack==NULL)return;
if(stack->singlyLinkedList==NULL)return;
destroySinglyLinkedList(stack->singlyLinkedList);
free(stack);
}
int getSizeOfStack(Stack *stack)
{
if(stack==NULL||stack->singlyLinkedList==NULL)return 0;
return getSizeOfSinglyLinkedList(stack->singlyLinkedList);
}
#endif