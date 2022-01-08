#include <stdio.h>
#include <string.h>
#include <time.h>
//stdalign.h Mô ra đây biết
#include "../JVAL_JRB/jrb.h"
#include "../QandS/Stack/stack.h"
#define INFINITIVE_VALUE 10000000

typedef struct{
    double weight;
    char routeID[20][15];
    int size;
}Road;

Road* initRoad(){
    Road* road=(Road*) malloc(sizeof(Road));
    road->weight=0.0;
    road->size=0;
    return road;
}
#include "../QandS/Queue/pqueue.h"

typedef struct Vertex_DT{
    char vertex[15];
    double distance;
    char parent[15];
}vertex_dt;

typedef struct node_t
{
	pqueue_pri_t pri;
	char vertex[15];
	size_t pos;
} node_t;


static int
cmp_pri(pqueue_pri_t next, pqueue_pri_t curr)
{
	return (next > curr);
}


static pqueue_pri_t
get_pri(void *a)
{
	return ((node_t *) a)->pri;
}


static void
set_pri(void *a, pqueue_pri_t pri)
{
	((node_t *) a)->pri = pri;
}


static size_t
get_pos(void *a)
{
	return ((node_t *) a)->pos;
}


static void
set_pos(void *a, size_t pos)
{
	((node_t *) a)->pos = pos;
}

typedef struct{
    JRB vertexes;
    JRB edges;
}Graph;
#define MAX 20
Graph createGraph(){
    Graph graph;
    graph.vertexes=make_jrb();
    graph.edges=make_jrb();
    return graph;
}
void addVertex(Graph graph,char* id, char *name){
    JRB node = jrb_find_str(graph.vertexes,id);
    if(node!=NULL){
        printf("Vertex exist!\n");
        return;
    }
    jrb_insert_str(graph.vertexes,id,new_jval_s(name));
}
char* getVertex(Graph graph, char* id){
    JRB node = jrb_find_str(graph.vertexes,id);
    if(node==NULL){
        printf("Vertex does not exist!\n");
        return NULL;
    }
    return node->val.s;
}
void addEdge(Graph graph,char* id1,char* id2,Road* road){
    JRB node1 = jrb_find_str(graph.vertexes,id1);
    if(node1==NULL){
        printf("Vertex 1 does not exist!\n");
        return;
    }
    JRB node2 = jrb_find_str(graph.vertexes,id2);
    if(node2==NULL){
        printf("Vertex 2 does not exist!\n");
        return;
    }
    JRB temp=jrb_find_str(graph.edges,id1);
    if(temp==NULL) {
        JRB new_tree=make_jrb();
        jrb_insert_str(graph.edges,id1,new_jval_v(new_tree));
        jrb_insert_str(new_tree,id2,new_jval_v(road));
    }
    else{
        JRB tree=(JRB) jval_v(temp->val);
        jrb_insert_str(tree,id2,new_jval_v(road));
    }
}
Road* getEdgeValue(Graph graph,char* v1, char* v2){
    JRB v1Node=jrb_find_str(graph.edges,v1);
    if(v1Node==NULL) return NULL;
    JRB tree=(JRB) jval_v(v1Node->val);
    JRB v2Node=jrb_find_str(tree,v2);
    if(v2Node==NULL) return NULL;
    return (Road*)jval_v(v2Node->val);
}
typedef struct{
    char s[4000][15];
}output;

int indegree(Graph graph,char* v,output* out){
    JRB temp;
    int count=0;
    jrb_traverse(temp,graph.edges){
        JRB tree=(JRB) jval_v(temp->val);
        JRB temp2;
        jrb_traverse(temp2,tree) {
            if(strcmp(temp2->key.s,v)==0){
                strcpy(out->s[count],temp->key.s);
                count++;
            }
        }
    }
    return count;
}
int outdegree(Graph graph, char* v,output* out){
    int count=0;
    JRB find_v=jrb_find_str(graph.edges,v);
    if(find_v==NULL) return 0;
    JRB tree=(JRB) jval_v(find_v->val);
    JRB temp;
    jrb_traverse(temp,tree){
        strcpy(out->s[count++],temp->key.s);
    }
    return count;
}
void dropGraph(Graph graph){
    jrb_free_tree(graph.vertexes);
    JRB temp;
    jrb_traverse(temp,graph.edges){
        jrb_free_tree((JRB)jval_v(temp->val));
    }
    jrb_free_tree(graph.edges);
}

//May be useful function
vertex_dt* findVerDT(JRB root,char* s){
    JRB node=jrb_find_str(root,s);
    if(node==NULL) {
        printf("VerDT");
        exit(0);
    }
    return (vertex_dt*) node->val.v;
}

node_t* findNodeT(JRB root,char* s){
    JRB node=jrb_find_str(root,s);
    if(node==NULL) {
        printf("NodeT");
        exit(0);
    }
    return (node_t*) node->val.v;
}
int getIsVisited(JRB root,char* s){
    JRB node=jrb_find_str(root,s);
    if(node==NULL) {
        printf("isVisited");
        exit(0);
    }
    return node->val.i;
}
void setIsVisited(JRB root,char* s){
    JRB node=jrb_find_str(root,s);
    if(node==NULL) {
        printf("SisVisited");
        exit(0);
    }
    node->val.i=1;
}
/* 
Return the total weight of the path and the path is 
given via path and its length. Return INFINITIVE_VALUE if no 
path is found 
*/
double shortestPath(Graph graph, char* s, char* t, output* path, int*length){
    pqueue_t *pq;
    node_t   *ns;
	node_t   *n;
	ns = (node_t*)malloc(MAX * sizeof(node_t));
	pq = pqueue_init(MAX, cmp_pri, get_pri, set_pri, get_pos, set_pos);
	if (!(ns && pq)) return -1;
    int i;
    // vertex_dt arrayOfVertex[MAX];
    JRB arrayOfVertex=make_jrb();
    JRB arrayOfPri=make_jrb();
    JRB temp_jrb;
    JRB isVisited=make_jrb();
    jrb_traverse(temp_jrb,graph.vertexes){
        char ver[15];
        strcpy(ver,temp_jrb->key.s);
        vertex_dt* tempVer=(vertex_dt*) malloc(sizeof(vertex_dt));
        strcpy(tempVer->parent,"-1");
        strcpy(tempVer->vertex,ver);
        tempVer->distance=INFINITIVE_VALUE;
        node_t* priTemp=(node_t*) malloc(sizeof(node_t));
        priTemp->pri=INFINITIVE_VALUE;
        strcpy(priTemp->vertex,ver);
        jrb_insert_str(arrayOfVertex,strdup(ver),new_jval_v(tempVer));
        jrb_insert_str(arrayOfPri,strdup(ver),new_jval_v(priTemp));
        jrb_insert_str(isVisited,strdup(ver),new_jval_i(0));
        pqueue_insert(pq,priTemp);
    }
    //Find vertex 's'
    vertex_dt* tempfind1=findVerDT(arrayOfVertex,s);
    tempfind1->distance=0;
    node_t* tempfind2=findNodeT(arrayOfPri,s);
    pqueue_change_priority(pq,0,tempfind2);
    //
    while((n=(node_t*)pqueue_pop(pq))){
        output out;
        int count=outdegree(graph,n->vertex,&out);
        char u[15];
        strcpy(u,n->vertex);
        setIsVisited(isVisited,u);
        for(i=0;i<count;i++){
            char v[15];
            strcpy(v,out.s[i]);
            if(getIsVisited(isVisited,v)==1) continue;
            //For v
            vertex_dt* tempV=findVerDT(arrayOfVertex,v);
            node_t* nodeV=findNodeT(arrayOfPri,v);
            //For u
            vertex_dt* tempU=findVerDT(arrayOfVertex,u);
            //
            if(tempV->distance > (tempU->distance+getEdgeValue(graph,u,v)->weight)){
                tempV->distance = tempU->distance + getEdgeValue(graph,u,v)->weight;
                strcpy(tempV->parent,u);
            }
            pqueue_change_priority(pq,tempV->distance,nodeV);
        }
    }
    char temp[15];
    strcpy(temp,t);
    Stack* stack=init();
    while(strcmp(findVerDT(arrayOfVertex,temp)->parent,"-1")!=0){
        char tempString[15];
        strcpy(tempString,findVerDT(arrayOfVertex,temp)->parent);
        push(makeData(tempString),stack);
        strcpy(temp,tempString);
    }
    int count2=0;
    while(!isEmptyStack(stack)){
        element elec=pop(stack);
        strcpy(path->s[count2++],elec.s);
    }
    strcpy(path->s[count2++],t);
    *length=count2;
    return findVerDT(arrayOfVertex,t)->distance;
}


