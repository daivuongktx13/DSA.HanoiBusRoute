#include "state_ults.h"

JRB line=NULL;
Graph graph;
JRB busStop=NULL;
double getDistance(MinRoad* minRoad,int index1,int index2){
  int i;
  double distance=0;
  for(i=index1;i<=index2;i++){
    distance+=minRoad[i].weight;
  }
  return distance;
}
char* getMinimumTour(Graph graph,JRB line,char* src,char* des){
    char minRoute[5000];
    char tempConcat[1000];
    char* ver1=strdup(getVertex(graph,src));
    ver1[strlen(ver1)-1]='\0';
    char* ver2=strdup(getVertex(graph,des));
    ver2[strlen(ver2)-1]='\0';
    sprintf(minRoute,"Tuyến đường thời gian ngắn nhất giữa 2 điểm <b>%s</b> và <b>%s</b>:\n",ver1,ver2);
    int i,size;
    output* out=(output*) malloc(sizeof(output));
    double distance;
    clock_t start=clock();
    distance=shortestPath(graph,src,des,out,&size);
    clock_t end=clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nTime to find: %.2f seconds\n",time_spent);
    printf("Shortest time: %lf minutes\n",distance/60);
    sprintf(tempConcat,"Thời gian: <b>%.1lf</b> phút\n",distance/60);
    strcat(minRoute,tempConcat);
    double realDistance=0;
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
            realDistance+=(temp->weight)*6;
            printf("|%lf",temp->weight);
        }else {
          realDistance+=(temp->weight)*1.3;
          printf("Walk |%lf",temp->weight);
        }
        printf("\n");
        
        minroad[i].weight=temp->weight;
    }
    sprintf(tempConcat,"Khoảng cách: <b>%.lf</b> mét\n",realDistance);
    strcat(minRoute,tempConcat);
    strcat(minRoute,"Lộ trình: \n");
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
            double disTemp=getDistance(minroad,currentIndex,indexMax);
            sprintf(tempConcat,"\t+ <b>%s</b> --> <b>%s</b> đi chuyến <b>%s</b>. Khoảng cách: <b>%.lf</b> mét\n",
                  minroad[currentIndex].ver1,minroad[indexMax].ver2,busMax,disTemp*6);
            strcat(minRoute,tempConcat);
            printf("%s %s: %s\n",minroad[currentIndex].ver1,minroad[indexMax].ver2,busMax);
            currentIndex=indexMax+1;
        }
        else{
            //Do sthing
            double disTemp=getDistance(minroad,currentIndex,indexMax);
            sprintf(tempConcat,"\t+ <b>%s</b> --> <b>%s</b> đi bộ. Khoảng cách: <b>%.lf</b> mét\n",
                  minroad[currentIndex].ver1,minroad[indexMax].ver2,disTemp*1.3);
            strcat(minRoute,tempConcat);
            printf("%s %s: Walking\n",minroad[currentIndex].ver1,minroad[currentIndex].ver2);
            currentIndex++;
        }
    }while(1);
    return strdup(minRoute);
}

//
//
// State 1
void searchForInfo1(GtkWidget* entry,GtkComboBox* combobox){
  gchar* text=gtk_entry_get_text(entry);
  int i;
  gtk_combo_box_text_remove_all(combobox);
  JRB temp;
  int count=0;
  if(graph.vertexes==NULL) {
    graph =  read_graph();
  }
  jrb_traverse(temp,graph.vertexes){
    char* find=strstr(temp->val.s,text);
    if(count>25) break;
    if(find!=NULL){
      //Strdup later
      gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combobox),temp->key.s,temp->val.s);
      count++;
    }
  }
}
void printInfo1(GtkComboBox* combobox,GtkLabel* label){
  gchar* textID=gtk_combo_box_get_active_id(combobox);
  gchar* textName=gtk_combo_box_text_get_active_text(combobox);
  if(textID==NULL||textName==NULL) return;
  if(busStop==NULL) busStop=read_busStop_Routes();
  JRB find=jrb_find_str(busStop,textID);
  BusStop* tempBS=(BusStop*)find->val.v;
  char tempS[1000];
  sprintf(tempS,"Mã số điểm xe buýt: %s\nTên điểm: %sSố tuyến xe đi qua: %d\n",textID,textName,tempBS->size);
  strcat(tempS,"Các tuyến xe đi qua: ");
  int i;
  for(i=0;i<tempBS->size;i++){
    strcat(tempS,tempBS->routeName[i]);
    strcat(tempS," ");
  }
  strcat(tempS,"\n");
  gtk_label_set_text(label,tempS);
}

//
// Work with JRB line and Graph graph;
// State 2
void printdata2(GtkWidget* box,GtkWidget* text){
  gchar* textID=gtk_combo_box_get_active_id(box);
  int i;
  gchar* textName=gtk_combo_box_text_get_active_text(box);
  if(textID==NULL||textName==NULL) return;
  char displayText[10000];
  JRB find=jrb_find_str(line,textID);
  Route* routeTemp=(Route*)find->val.v;
  sprintf(displayText,"<b>%s</b> đi qua <b>%d</b> điểm dừng.\n",textName,routeTemp->size);
  for(i=0;i<routeTemp->size;i++){
    char* name=getVertex(graph,routeTemp->busStop[i]);
    strcat(displayText,"\t+ ");
    strcat(displayText,name);
  }
  gtk_label_set_markup(text,displayText);
}
void searchData2(GtkEntry* entry,GtkComboBox* combobox){
  gchar* text=gtk_entry_get_text(entry);
  JRB temp;
  if(line==NULL) line=read_lineNameANDroute();
  if(graph.vertexes==NULL) graph=read_graph();
  int count=0;
  gtk_combo_box_text_remove_all(combobox);
  jrb_traverse(temp,line){
    char tempString[100]="Tuyến ";
    if(count>30) break;
    Route* tempRoute=(Route*) temp->val.v;
    if(strstr(tempRoute->routeName,text)!=NULL){
      strcat(tempString,tempRoute->routeName);
      gtk_combo_box_text_append(combobox,strdup(temp->key.s),strdup(tempString));
      count++;
    }
  }
}
//
//
// State3
extern char srcID[15];
extern char desID[15];

void searchForInfo3(GtkWidget* entry,GtkComboBox* combobox){
  gchar* text=gtk_entry_get_text(entry);
  int i;
  gtk_combo_box_text_remove_all(combobox);
  JRB temp;
  int count=0;
  if(graph.vertexes==NULL)  graph=read_graph();
  jrb_traverse(temp,graph.vertexes){
    char* find=strstr(temp->val.s,text);
    if(count>25) break;
    if(find!=NULL){
      //Strdup later
      gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combobox),temp->key.s,temp->val.s);
      count++;
    }
  }
}

void srcBoxChange(GtkWidget* box){
  gchar* text=gtk_combo_box_get_active_id(box);
  if(text!=NULL) strcpy(srcID,text);
}
void desBoxChange(GtkWidget* box){
  gchar* text=gtk_combo_box_get_active_id(box);
  if(text!=NULL) strcpy(desID,text);
}

void findRoute(GtkWidget* button, GtkWidget* text){
  if(graph.vertexes==NULL) graph=read_graph();
  if(line==NULL) line=read_lineNameANDroute();
  if(strlen(srcID)<3||strlen(desID)<3) return;
  char* MinRoute=getMinimumTour(graph,line,srcID,desID);
  gtk_label_set_markup(text,MinRoute);
}
  

