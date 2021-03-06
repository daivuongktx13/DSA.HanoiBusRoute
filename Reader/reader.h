#include "../Graph/DirectedGraph.h"
#include <locale.h>
#define lineName "BusStopInfo/lineName.txt"
#define busStop_Routes "BusStopInfo/busStop_Routes.txt"
#define busStopName "BusStopInfo/busStopName.txt"
#define route "BusStopInfo/route.txt"
#define routeDistance "BusStopInfo/routeDistance.txt"
#define walkingDistance "BusStopInfo/walkingDistance.txt"


typedef struct{
    char routeName[7];
    char busStop[50][15];
    int size;
}Route;

// Dùng struct Route để chứa thông tin của tuyến xe buýt
// Cho struct Route vào trong Val của JRB với key là mã tuyến
// Cần dùng con trỏ của Route nếu k sẽ bị lỗi
JRB read_lineNameANDroute();
// Tạo một graph chứa:
// -Tên các bến
// -Đường đi từ 1 bến đến 1 bến có weight là distance/velocity(Chia cho)
// V người đi bộ 1.4m/s
// V xe buýt 8m/s
// Nhớ dùng cả struct Road ở bên graph. Dùng con trỏ Road nha.
// Qua bên test.c mà xem ví dụ bỏ con trỏ vô trong JRB
Graph read_graph();

typedef struct{
    char routeName[20][7];
    int size;
}BusStop;

// Dùng struct BusStop để chứa thông tin của bến xe buýt
// Struct gồm số tuyến đi qua, tên các tuyến đi qua
// Chắc cụng cần dùng con trỏ BusStop đó
JRB read_busStop_Routes();



