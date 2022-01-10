#include <stdio.h>

#include "../GUI/state.h"
#include "../GUI/state1.h"
#include "../GUI/state2.h"
#include "../GUI/state3.h"
#include "../StateFunctions/state_ults.h"

GtkWidget *window=NULL;
GtkWidget *state1=NULL;
GtkWidget *state2=NULL;
GtkWidget *state3=NULL;


// Lệnh compile nầy
//Gcc `pkg-config --cflags gtk+-3.0` Main/main.c -o test  JVAL_JRB/jrb.c JVAL_JRB/jval.c QandS/Queue/pqueue.c Reader/reader.c QandS/Stack/stack.c GUI/state.c GUI/state1.c GUI/state2.c GUI/state3.c Graph/DirectedGraph.c Path/state_ults.c `pkg-config --libs gtk+-3.0` -w
//Lệnh chạy nầy
// ./test

int main(int argc, char *argv[]){
    GtkApplication *app = gtk_application_new ("com.example.GtkApplication",
                                             G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (on_activate), NULL);

    g_application_run (G_APPLICATION (app), argc, argv);
    return 0;
}
