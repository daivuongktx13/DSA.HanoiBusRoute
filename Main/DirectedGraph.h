#include <stdio.h>
//stdalign.h Mô ra đây biết
#include "../JVAL_JRB/jrb.h"
#include "../QandS/Stack/stack.h"
#define INFINITIVE_VALUE 10000000

#include "../QandS/Queue/pqueue.h"
typedef struct Vertex_DT{
    int vertex;
    int distance;
    int parent;
}vertex_dt;

typedef struct node_t
{
	pqueue_pri_t pri;
	int    vertex;
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
void addVertex(Graph graph,int id, char *name){
    JRB node = jrb_find_int(graph.vertexes,id);
    if(node!=NULL){
        printf("Vertex exist!\n");
        return;
    }
    Jval id_jval=new_jval_s(strdup(name));
    jrb_insert_int(graph.vertexes,id,id_jval);
}
char* getVertex(Graph graph, int id){
    JRB node = jrb_find_int(graph.vertexes,id);
    if(node==NULL){
        printf("Vertex does not exist!\n");
        return NULL;
    }
    return node->val.s;
}
void addEdge(Graph graph,int id1,int id2,double weight){
    JRB node1 = jrb_find_int(graph.vertexes,id1);
    if(node1==NULL){
        printf("Vertex 1 does not exist!\n");
        return;
    }
    JRB node2 = jrb_find_int(graph.vertexes,id2);
    if(node2==NULL){
        printf("Vertex 2 does not exist!\n");
        return;
    }
    JRB temp=jrb_find_int(graph.edges,id1);
    if(temp==NULL) {
        JRB new_tree=make_jrb();
        jrb_insert_int(graph.edges,id1,new_jval_v(new_tree));
        jrb_insert_int(new_tree,id2,new_jval_d(weight));
    }
    else{
        JRB tree=(JRB) jval_v(temp->val);
        jrb_insert_int(tree,id2,new_jval_d(weight));
    }
}
double getEdgeValue(Graph graph,int v1, int v2){
    JRB v1Node=jrb_find_int(graph.edges,v1);
    if(v1Node==NULL) return INFINITIVE_VALUE;
    JRB tree=(JRB) jval_v(v1Node->val);
    JRB v2Node=jrb_find_int(tree,v2);
    if(v2Node==NULL) return INFINITIVE_VALUE;
    return jval_d(v2Node->val);
}
int indegree(Graph graph,int v,int* output){
    JRB temp;
    int count=0;
    jrb_traverse(temp,graph.edges){
        JRB tree=(JRB) jval_v(temp->val);
        JRB temp2;
        jrb_traverse(temp2,tree) {
            if(jval_i(temp2->key)==v){
                output[count]=jval_i(temp->key);
                count++;
            }
        }
    }
    return count;
}
int outdegree(Graph graph, int v,int* output){
    int count=0;
    JRB find_v=jrb_find_int(graph.edges,v);
    if(find_v==NULL) return 0;
    JRB tree=(JRB) jval_v(find_v->val);
    JRB temp;
    jrb_traverse(temp,tree){
        output[count]=jval_i(temp->key);
        count++;
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
 
/* 
Return the total weight of the path and the path is 
given via path and its length. Return INFINITIVE_VALUE if no 
path is found 
*/
double shortestPath(Graph graph, int s, int t, int* path, int*length){
    pqueue_t *pq;
    node_t   *ns;
	node_t   *n;

	ns = (node_t*)malloc(MAX * sizeof(node_t));
	pq = pqueue_init(MAX, cmp_pri, get_pri, set_pri, get_pos, set_pos);
	if (!(ns && pq)) return -1;
    int i;
    vertex_dt arrayOfVertex[MAX];
    JRB temp_jrb;
    jrb_traverse(temp_jrb,graph.vertexes){
        int i=temp_jrb->key.i;
        arrayOfVertex[i].vertex=i;
        arrayOfVertex[i].parent=-1;
        arrayOfVertex[i].distance=INFINITIVE_VALUE;
        ns[i].pri=INFINITIVE_VALUE;
        ns[i].vertex=i;
        pqueue_insert(pq,&ns[i]);
    }
    arrayOfVertex[s].distance=0;
    pqueue_change_priority(pq,0,&ns[s]);
    int isVisited[MAX]={0};
    while((n=(node_t*)pqueue_pop(pq))){
        int output[100];
        int count=outdegree(graph,n->vertex,output);
        int u=n->vertex;
        isVisited[u]=1;
        for(i=0;i<count;i++){
            int v=output[i];
            if(isVisited[v]==1) continue;
            if(arrayOfVertex[v].distance > (arrayOfVertex[u].distance+getEdgeValue(graph,u,v))){
                arrayOfVertex[v].distance=arrayOfVertex[u].distance+getEdgeValue(graph,u,v);
                arrayOfVertex[v].parent=u;
            }
            pqueue_change_priority(pq,arrayOfVertex[v].distance,&ns[v]);
        }
    }
    int temp=t;
    Stack* stack=init();
    while(arrayOfVertex[temp].parent!=-1){
        push(arrayOfVertex[temp].parent,stack);
        temp=arrayOfVertex[temp].parent;
    }
    int count2=0;
    while(!isEmptyStack(stack)){
        path[count2++]=pop(stack);
    }
    path[count2++]=t;
    *length=count2;
    return arrayOfVertex[t].distance;
}
