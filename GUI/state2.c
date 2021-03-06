#include "state2.h"


extern GtkWidget *window;
extern GtkWidget *state2;
extern void on_activate (GtkApplication *app);
extern void printdata2(GtkWidget* box,GtkWidget* text);
extern void searchData2(GtkEntry* entry,GtkComboBox* combobox);



void changeToState2(GtkApplication *app){
  state2 = gtk_application_window_new (app);
  gtk_window_set_default_size(GTK_WINDOW(state2),1000,800);
  GtkWidget* backButton=gtk_button_new_with_label("Back");
  GtkWidget* text=gtk_label_new("");
  gtk_label_set_markup(text,"<b>In ra các bến của 1 tuyến xe buýt</b>");
  GtkWidget* box=gtk_combo_box_text_new();
  GtkWidget *container=gtk_vbox_new(TRUE,5);
  //Container search
  GtkWidget *containerSearch=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
  GtkWidget* textSearch=gtk_label_new("Enter place to search: ");
  GtkWidget* entryState2=gtk_entry_new();
  GtkWidget* buttonSearch=gtk_button_new_with_label("Search!");
  gtk_box_pack_start(GTK_BOX(containerSearch),textSearch,FALSE,FALSE,5);
  gtk_box_pack_end(GTK_BOX(containerSearch),entryState2,TRUE,TRUE,5);
  g_signal_connect(entryState2,"activate",G_CALLBACK(searchData2),box);

  GtkWidget *scrollView=gtk_scrolled_window_new(NULL,NULL);
  gtk_container_add(GTK_CONTAINER(state2),container);
  gtk_box_pack_start(GTK_BOX(container),backButton,TRUE,TRUE,5);
  gtk_box_pack_start(GTK_BOX(container),text,FALSE,FALSE,5);
  gtk_box_pack_start(GTK_BOX(container),containerSearch,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(container),box,TRUE,TRUE,5);
  gtk_box_pack_start(GTK_BOX(container),scrollView,TRUE,TRUE,5);
  GtkWidget* text2=gtk_label_new("Here is data ...");
  gtk_label_set_xalign(text2,0.05);
  gtk_container_add(GTK_CONTAINER(scrollView),text2);
  gtk_widget_set_hexpand(scrollView, TRUE);
  gtk_widget_set_vexpand(scrollView, TRUE);
  g_signal_connect_swapped(backButton,"clicked",G_CALLBACK(on_activate),app);
  g_signal_connect(box,"changed", G_CALLBACK(printdata2),text2);
  gtk_widget_show_all(state2);
  gtk_window_close(GTK_WINDOW(window));
  gtk_application_remove_window(app,window);
}