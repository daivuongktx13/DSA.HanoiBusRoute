#include <stdio.h>
#include "../Reader/reader.h"
#include <time.h> 
// Lệnh compile nầy
// Gcc -o Main/test Main/test.c JVAL_JRB/jrb.c JVAL_JRB/jval.c QandS/Queue/pqueue.c -w
//Lệnh chạy nầy
// ./Main/test

typedef struct{
    char ver1[15];
    char ver2[15];
    char routeName[20][7];
    int size;
    double weight;
}MinRoad;
void getMinimumTour(Graph graph,JRB line){
    int i,size;
    output* out=(output*) malloc(sizeof(output));
    double distance;
    clock_t start=clock();
    distance=shortestPath(graph,"4251886989","738815106",out,&size);
    clock_t end=clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time to find: %.2f seconds\n",time_spent);
    printf("Shortest time: %lf minutes\n",distance/60);
    printf("Path: \n");
    int j;
    MinRoad* minroad=(MinRoad*) malloc((size-1)*sizeof(MinRoad));
    for(i=0;i<size-1;i++){
        printf("%s %s: ",out->s[i],out->s[i+1]);
        strcpy(minroad[i].ver1,out->s[i]);
        strcpy(minroad[i].ver2,out->s[i+1]);
        Road* temp=getEdgeValue(graph,out->s[i],out->s[i+1]);
        int size2=temp->size;
        minroad[i].size=size2;
        if(size2!=0){
            for(j=0;j<size2;j++){
                JRB temp2=jrb_find_str(line,temp->routeID[j]);
                Route* tempRoute=(Route*) temp2->val.v;
                printf("%s ",tempRoute->routeName);
                strcpy(minroad[i].routeName[j],tempRoute->routeName);
            }
            printf("|%lf",temp->weight);
        }else printf("Walk |%lf",temp->weight);
        printf("\n");
        minroad[i].weight=temp->weight;
    }
    //Find minumum route
    printf("Minimum Path: \n");
    int sizeMinRoad=size-1;
    int currentIndex=0;
    do{
        if(currentIndex>=sizeMinRoad) break;
        int indexMax=currentIndex;
        char busMax[7];
        int max=-1;
        if(minroad[currentIndex].size!=0){
        for(i=0;i<minroad[currentIndex].size;i++){
            int count=0;
            int tempIndex=currentIndex+1;
            do{
                if(tempIndex>=sizeMinRoad) break;
                if(minroad[tempIndex].size==0) break;
                int state=0;
                for(j=0;j<minroad[tempIndex].size;j++){
                    if(strcmp(minroad[currentIndex].routeName[i],minroad[tempIndex].routeName[j])==0){
                        count+=1;
                        state=1;
                        break;
                    }
                }
                if(state==0) break;
                tempIndex++;
            }while(1);
            if(count>max) {
                indexMax=tempIndex-1;
                max=count;
                strcpy(busMax,minroad[currentIndex].routeName[i]);
            }
        }
            printf("%s %s: %s\n",minroad[currentIndex].ver1,minroad[indexMax].ver2,busMax);
            currentIndex=indexMax+1;
        }
        else{
            //Do sthing
            printf("%s %s: Walking\n",minroad[currentIndex].ver1,minroad[currentIndex].ver2);
            currentIndex++;
        }
    }while(1);
}
int main(){
    JRB line=read_lineNameANDroute();
    Graph graph=read_graph();
    
    getMinimumTour(graph,line);

    // JRB busStop=read_busStop_Routes();
}

