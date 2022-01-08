#include "state2.h"


extern GtkWidget *window;
extern GtkWidget *state2;
extern void on_activate (GtkApplication *app);
int i;

void printdata(GtkWidget* box,GtkWidget* text){
  gchar *tempText=gtk_combo_box_text_get_active_text(GTK_COMBO_BOX(box));
  gtk_label_set_text(GTK_LABEL(text),tempText);
}

void changeToState2(GtkApplication *app){
  state2 = gtk_application_window_new (app);
  gtk_window_set_default_size(GTK_WINDOW(state2),800,600);
  GtkWidget* backButton=gtk_button_new_with_label("Back");
  GtkWidget* text=gtk_label_new("In ra các bến của 1 tuyến xe buýt");
  GtkWidget* box=gtk_combo_box_text_new();
  for(i=0;i<3;i++){
  }
  GtkWidget *container=gtk_vbox_new(TRUE,5);
  GtkWidget *scrollView=gtk_scrolled_window_new(NULL,NULL);
  gtk_container_add(GTK_CONTAINER(state2),container);
  gtk_box_pack_start(GTK_BOX(container),backButton,TRUE,TRUE,5);
  gtk_box_pack_start(GTK_BOX(container),text,TRUE,TRUE,5);
  gtk_box_pack_start(GTK_BOX(container),box,TRUE,TRUE,5);
  gtk_box_pack_start(GTK_BOX(container),scrollView,TRUE,TRUE,5);
  GtkWidget* text2=gtk_label_new("Here is data ...");
  gtk_container_add(GTK_CONTAINER(scrollView),text2);
  gtk_widget_set_hexpand(scrollView, TRUE);
  gtk_widget_set_vexpand(scrollView, TRUE);
  g_signal_connect_swapped(backButton,"clicked",G_CALLBACK(on_activate),app);
  g_signal_connect(box,"changed", G_CALLBACK(printdata),text2);
  gtk_widget_show_all(state2);
  gtk_window_close(GTK_WINDOW(window));
  gtk_application_remove_window(app,window);
}