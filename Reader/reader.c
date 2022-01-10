#include "reader.h"
#include <time.h>
JRB read_lineNameANDroute(){
    clock_t start=clock();
    FILE* fi1=fopen(lineName,"r");
    FILE* fi2=fopen(route,"r");
    if(fi1==NULL){
        printf("Dm trung\n");
    }
    if(fi2==NULL){
        printf("Dm trung\n");
    }
    JRB newtree=make_jrb();
    int n,i;
    char c[15];
    char a[15];
    int d;
    char e[15];
    char b[10];
    fscanf(fi1,"%d%*c",&n);
    Route* newroute=(Route*) malloc(n*sizeof(Route));
    char** routeID=(char**) malloc(n*sizeof(char*));
    for(i=0;i<n;i++){
        routeID[i]=(char*) malloc(15*sizeof(char));
    }
    for (i=0;i<n;i++){
        fscanf(fi1,"%s%*c",a);
        fscanf(fi1,"%s%*c",b);
        strcpy(routeID[i],a);
        strcpy(newroute[i].routeName,b);
    }
    fscanf(fi2,"%d%*c",&n);
    int j;
    for(i=0;i<n;i++){
        fscanf(fi2,"%s%*c",c);
        fscanf(fi2,"%d%*c",&d);
        newroute[i].size=d;
        for(j=0;j<d;j++){
            fscanf(fi2,"%s%*c",e);
            strcpy(newroute[i].busStop[j],e);
        }
    }
    for(i=0;i<n;i++){
        jrb_insert_str(newtree,routeID[i],new_jval_v(&newroute[i]));
    }     
    printf("Finished Read JRB 1\n");
    fclose(fi1);
    fclose(fi2);
    clock_t end=clock();
    double time=(double)(end-start)/CLOCKS_PER_SEC;
    printf("Time need to read JRB 1: %lf seconds\n",time);
    return newtree;
}


Graph read_graph(){
    clock_t start=clock();
    setlocale(LC_ALL, "en_US.UTF-8");
    FILE* fi1=fopen(busStopName,"r");
    if(fi1==NULL){
        printf("Cannot open file!\n");
        exit(0);
    }
    FILE* fi2=fopen(routeDistance,"r");
    if(fi2==NULL){
        printf("Cannot open file!\n");
        exit(0);
    }
    FILE* fi3=fopen(walkingDistance,"r");
    if(fi3==NULL){
        printf("Cannot open file!\n");
        exit(0);
    }
    Graph newgraph =createGraph();
    char temp[15];
    int n1,n2,n3,i;
    int k,j;
    char a[15],c[15],d[15],f[15],b[500];
    double e;
    fgets(temp,20,fi1);
    fscanf(fi1,"%d",&n1);
    for(i=0;i<n1;i++){
        fscanf(fi1,"%s%*c",a);
        fgets(b,500,fi1);
        addVertex(newgraph,strdup(a),strdup(b));
    }
    printf("Finish part 1 Read Graph!\n");
    fscanf(fi2,"%d%*c",&n2);
    for(i=0;i<n2;i++){
        char temp;
        Road *road=initRoad();
        fscanf(fi2,"%s %s%*c",c,d);
        fscanf(fi2,"%lf%*c",&e);
        road->weight=e/6;
        fscanf(fi2,"%d%*c",&k);
        road->size=k;
        for(j=0;j<k;j++){
            fscanf(fi2,"%s%*c",f);
            strcpy(road->routeID[j],f);
        }
        temp=fgetc(fi2);
        addEdge(newgraph,strdup(c),strdup(d),road);
    }
    printf("Finish part 2 Read Graph!\n");
    fscanf(fi3,"%d%*c",&n3);
    for(i=0;i<n3;i++){
        Road *road=initRoad();
        fscanf(fi3,"%s %s%*c",c,d);
        fscanf(fi3,"%lf%*c",&e);
        road->weight=e/1.3;
        road->size=0;
        Road *road2=initRoad();
        road2->weight=e/1.3;
        road2->size=0;
        Road* tempFind=getEdgeValue(newgraph,c,d);
        if(tempFind==NULL) addEdge(newgraph,strdup(c),strdup(d),road);
    }
    printf("Finish part 3 Read Graph!\n");
    clock_t end=clock();
    double time=(double)(end-start)/CLOCKS_PER_SEC;
    printf("Time need to read Graph: %.2lf seconds\n",time);
    return newgraph;
}

JRB read_busStop_Routes(){
    clock_t start=clock();
    FILE* fi1=fopen(busStop_Routes,"r");
    JRB newtree=make_jrb();
    int n,b,i,j;
    char a[15];
    char c[7];
    fscanf(fi1,"%d%*c",&n);
    // BusStop newBS[n];
    BusStop* newBS=(BusStop*) malloc(n*sizeof(BusStop));
    for(i=0;i<n;i++){
        fscanf(fi1,"%s%*c",a);
        fscanf(fi1,"%d%*c",&b);
        newBS[i].size=b;
        for(j=0;j<b;j++){
            fscanf(fi1,"%s%*c",c);
            strcpy(newBS[i].routeName[j],c);
        }
        jrb_insert_str(newtree,strdup(a),new_jval_v(&newBS[i]));
    }
    printf("Finished Read JRB 2\n");
    clock_t end=clock();
    double time=(double)(end-start)/CLOCKS_PER_SEC;
    printf("Time need to read JRB 2: %.2lf seconds\n",time);
    return newtree;
}