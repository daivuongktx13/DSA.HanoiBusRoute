#include <gtk/gtk.h>
#include "../Reader/reader.h"


typedef struct{
    char ver1[15];
    char ver2[15];
    char routeName[20][7];
    int size;
    double weight;
}MinRoad;


void getMinimumTour(Graph graph,JRB line,char* src,char* des);
//State1
void searchForInfo1(GtkWidget* entry,GtkComboBox* combobox);
void printInfo1(GtkComboBox* combobox,GtkLabel* label);

//State2


//State3





