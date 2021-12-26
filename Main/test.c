#include <stdio.h>
#include "../Reader/reader.h"
// Lệnh compile nầy
// Gcc -o Main/test Main/test.c JVAL_JRB/jrb.c JVAL_JRB/jval.c QandS/Queue/pqueue.c -w
//Lệnh chạy nầy
// ./Main/test
int main(){
    Graph graph=createGraph();
    addVertex(graph,1,"1");
    addVertex(graph,2,"2");
    Road* road= initRoad();
    road->weight=1.2;
    road->routeID[road->size++]=1238123;
    addEdge(graph,1,2,road);
    Road* result=getEdgeValue(graph,1,2);
    printf("Weight: %.2lf\n",result->weight);
    printf("Number of route go to: %d\n",road->size);
    printf("Route id: %d\n",road->routeID[0]);
}

