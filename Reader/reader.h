#include "../Main/DirectedGraph.h"

#define lineName "../BusStopInfo/lineName.txt"
#define busStop_Routes "../BusStopInfo/busStop_Routes.txt"
#define busStopName "../BusStopInfo/busStopName.txt"
#define route "../BusStopInfo/route.txt"
#define routeDistance "../BusStopInfo/routeDistance.txt"
#define walkingDistance "../BusStopInfo/walkingDistance.txt"

typedef struct{
    char routeName[7];
    int busStop[50];
    int size=0;
}Route;


// Dùng struct Route để chứa thông tin của tuyến xe buýt
// Cho struct Route vào trong Val của JRB với key là mã tuyến
// Cần dùng con trỏ của Route nếu k sẽ bị lỗi
JRB read_lineNameANDroute(){
    FILE* fi1=fopen(lineName,"r");
    FILE* fi2=fopen(route,"r");

}
// Tạo một graph chứa:
// -Tên các bến
// -Đường đi từ 1 bến đến 1 bến có weight là distance/velocity(Chia cho)
// V người đi bộ 1.4m/s
// V xe buýt 8m/s
Graph read_graph(){
    FILE* fi1=fopen(busStopName,"r");
    FILE* fi2=fopen(routeDistance,"r");
    FILE* fi3=fopen(walkingDistance,"r");
}

typedef struct{
    char route[20][7];
    int size=0;
}BusStop;

// Dùng struct BusStop để chứa thông tin của bến xe buýt
// Struct gồm số tuyến đi qua, tên các tuyến đi qua
//
JRB read_busStop_Routes(){
    FILE* fi1=fopen(busStop_Routes,"r");

}



