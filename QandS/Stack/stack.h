#include <stdlib.h>
typedef int element;

typedef struct stacknode_t{
    element data;
    struct stacknode_t *next;
}StackNode;

typedef struct stack_t{
    struct stacknode_t *top;
}Stack;

element makeData(int n){
    element elec=n;
    return elec;
}
void initializeStack(Stack* stack){
    stack->top=NULL;
}
Stack* init(){
    Stack* stack= (Stack*)malloc(sizeof(Stack));
    initializeStack(stack);
    return stack;
}

int isEmptyStack(Stack* stack){
    return stack->top==NULL;
}
int push(element elec,Stack* stack){
    StackNode *node=(StackNode*)malloc(sizeof(StackNode));
    if(node==NULL){
        printf("Stack overflow!\n");
        return 0;
    }
    node->data=elec;
    node->next = stack->top;
    stack->top=node;
    return 1;
}
element pop(Stack* stack){
    if(isEmptyStack(stack)){
        printf("Stack is empty!\n");
        return -9999;
    }
    StackNode* node=stack->top;
    (stack->top)=(stack->top)->next;
    element elec=node->data;
    free(node);
    return elec;
}
element peek(Stack* stack){
    return stack->top->data;
}
void freeStack(Stack* stack){
    StackNode* node=stack->top;
    while(node!=NULL){
        StackNode* temp=node;
        node=node->next;
        free(temp);
    }
}
