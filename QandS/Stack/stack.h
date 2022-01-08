#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct{
    char s[15];
}element;

typedef struct stacknode_t{
    element data;
    struct stacknode_t *next;
}StackNode;

typedef struct stack_t{
    struct stacknode_t *top;
}Stack;

element makeData(char* i);
void initializeStack(Stack* stack);
Stack* init();
int isEmptyStack(Stack* stack);
int push(element elec,Stack* stack);
element pop(Stack* stack);
element peek(Stack* stack);
void freeStack(Stack* stack);