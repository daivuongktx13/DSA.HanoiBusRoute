#include <stdio.h>
#include <stdlib.h>
typedef int element;
typedef struct dllist_t{
    element data;
    struct dllist_t *next;
    struct dllist_t *prev;
}*node;

typedef struct Queue_t{
    node front;
    node rear;
}Queue;

Queue* initQueue(){
    Queue* queue=(Queue*) malloc(sizeof(struct Queue_t));
    queue->front=NULL;
    queue->rear=NULL;
    return queue;
}
void makeNullQueue(Queue* queue){
    node p=queue->front;
    while(p!=NULL){
        node temp;
        temp=p;
        p=p->next;
        free(temp);
    }
}

int isEmptyQueue(Queue* queue){
    if(queue->front==NULL) return 1;
    return 0;
}

node makeNewNode(element elec){
    node newNode=(node) malloc(sizeof(struct dllist_t));
    newNode->data=elec;
    newNode->next=NULL;
    newNode->prev=NULL;
    return newNode;
}
void enqueue(Queue* queue,element e){
    node newNode=makeNewNode(e);
    if(queue->front==NULL){
        queue->front=newNode;
        queue->rear=newNode;
    }
    queue->rear->next=newNode;
    newNode->prev=queue->rear;
    queue->rear=newNode;
}

void traverseList(Queue* queue){
    node p=queue->front;
    while(p!=NULL){
        //Display node
        p=p->next;
    }
}

element dequeue(Queue* queue){
    if(isEmptyQueue(queue)) {
        printf("Empty queue!\n");
        return -99999;
    }
    node temp=queue->front;
    element data=temp->data;
    if(queue->front==queue->rear) {
        queue->rear=NULL;
        queue->front=NULL;
        return data;
    }
    queue->front=queue->front->next;
    queue->front->prev=NULL;
    free(temp);
    return data;
}




