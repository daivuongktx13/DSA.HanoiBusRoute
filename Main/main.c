#include <stdio.h>


#include "../Main/path_minimizer.h"

#include <gtk/gtk.h>
#include "../GUI/state1.h"
#include "../GUI/state2.h"
#include "../GUI/state3.h"
#include "../GUI/state.h"
#include <unistd.h>
JRB line=NULL;
Graph graph;
JRB busStop=NULL;

// Lệnh compile nầy
//Gcc `pkg-config --cflags gtk+-3.0` Main/main.c -o Main/main `pkg-config --libs gtk+-3.0` JVAL_JRB/jrb.c JVAL_JRB/jval.c QandS/Queue/pqueue.c -w
//Lệnh chạy nầy
// ./Main/main

int main(int argc, char *argv[]){
    // clock_t start=clock();
    // JRB line=read_lineNameANDroute();
    // Graph graph=read_graph();
    // JRB busStop=read_busStop_Routes();
    // clock_t end=clock();
    // double time=(double)(end-start)/CLOCKS_PER_SEC;
    // printf("App Loading time %.2lf seconds\n",time);
    GtkApplication *app = gtk_application_new ("com.example.GtkApplication",
                                             G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (on_activate), NULL);

    g_application_run (G_APPLICATION (app), argc, argv);
    return 0;
}
