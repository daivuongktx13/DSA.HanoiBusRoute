#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../JVAL_JRB/jrb.h"
#include "../QandS/Stack/stack.h"
#define INFINITIVE_VALUE 10000000
#include "../QandS/Queue/pqueue.h"
#define MAX 40000
typedef struct{
    double weight;
    char routeID[20][15];
    int size;
}Road;

typedef struct{
    char s[4000][15];
}output;

typedef struct Vertex_DT{
    char vertex[15];
    double distance;
    char parent[15];
}vertex_dt;

typedef struct{
    JRB vertexes;
    JRB edges;
}Graph;

typedef struct node_t
{
	pqueue_pri_t pri;
	char vertex[15];
	size_t pos;
} node_t;

Road* initRoad();

Graph createGraph();
void addVertex(Graph graph,char* id, char *name);
char* getVertex(Graph graph, char* id);
void addEdge(Graph graph,char* id1,char* id2,Road* road);
Road* getEdgeValue(Graph graph,char* v1, char* v2);


int indegree(Graph graph,char* v,output* out);
int outdegree(Graph graph, char* v,output* out);
void dropGraph(Graph graph);

//May be useful function
vertex_dt* findVerDT(JRB root,char* s);
node_t* findNodeT(JRB root,char* s);
int getIsVisited(JRB root,char* s);
void setIsVisited(JRB root,char* s);
/* 
Return the total weight of the path and the path is 
given via path and its length. Return INFINITIVE_VALUE if no 
path is found 
*/
double shortestPath(Graph graph, char* s, char* t, output* path, int*length);


