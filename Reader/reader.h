#include "../Main/DirectedGraph.h"
#include <locale.h>
#define lineName "BusStopInfo/lineName.txt"
#define busStop_Routes "BusStopInfo/busStop_Routes.txt"
#define busStopName "BusStopInfo/busStopName.txt"
#define route "BusStopInfo/route.txt"
#define routeDistance "BusStopInfo/routeDistance.txt"
#define walkingDistance "BusStopInfo/walkingDistance.txt"

//Qua bên test.c mà xem ví dụ bỏ con trỏ vô trong JRB

typedef struct{
    char routeName[7];
    char busStop[50][15];
    int size;
}Route;

// Dùng struct Route để chứa thông tin của tuyến xe buýt
// Cho struct Route vào trong Val của JRB với key là mã tuyến
// Cần dùng con trỏ của Route nếu k sẽ bị lỗi
JRB read_lineNameANDroute(){
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
    printf("Finished Read JRB 1");
    fclose(fi1);
    fclose(fi2);
    return newtree;
}
// Tạo một graph chứa:
// -Tên các bến
// -Đường đi từ 1 bến đến 1 bến có weight là distance/velocity(Chia cho)
// V người đi bộ 1.4m/s
// V xe buýt 8m/s
// Nhớ dùng cả struct Road ở bên graph. Dùng con trỏ Road nha.
// Qua bên test.c mà xem ví dụ bỏ con trỏ vô trong JRB
Graph read_graph(){
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
    return newgraph;
}

typedef struct{
    char routeName[20][7];
    int size;
}BusStop;

// Dùng struct BusStop để chứa thông tin của bến xe buýt
// Struct gồm số tuyến đi qua, tên các tuyến đi qua
// Chắc cụng cần dùng con trỏ BusStop đó
JRB read_busStop_Routes(){
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
    printf("Finished Read JRB 2");
    return newtree;
}



