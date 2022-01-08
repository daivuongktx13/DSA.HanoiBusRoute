#include "state1.h"

extern GtkWidget *window;
extern GtkWidget *state1;

extern void on_activate (GtkApplication *app);
extern void searchForInfo1(GtkWidget* entry,GtkComboBox* combobox);
extern void printInfo1(GtkComboBox* combobox,GtkLabel* label);



//In ra các xe buýt đi qua 1 bến
void changeToState1(GtkApplication *app){
  state1 = gtk_application_window_new (app);
  gtk_window_set_default_size(GTK_WINDOW(state1),800,600);
  //Back button
  GtkWidget* backButton=gtk_button_new_with_label("Back");
  //Text In ra các xe buýt đi qua 1 bến
  GtkWidget* text=gtk_label_new("In ra các xe buýt đi qua 1 bến");
  GtkWidget* seperator=gtk_hseparator_new();
  //Big container
  GtkWidget *container=gtk_vbox_new(TRUE,5);
  gtk_container_add(GTK_CONTAINER(state1),container);
  gtk_box_pack_start(GTK_BOX(container),backButton,TRUE,TRUE,5);
  gtk_box_pack_start(GTK_BOX(container),text,TRUE,TRUE,5);
  gtk_box_pack_start(GTK_BOX(container),seperator,TRUE,FALSE,10);
  g_signal_connect_swapped(backButton,"clicked",G_CALLBACK(on_activate),app);
  //Small container
  GtkWidget *containerSearch=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
  GtkWidget* textSearch=gtk_label_new("Enter place to search: ");
  GtkWidget* entryState1=gtk_entry_new();
  GtkWidget* buttonSearch=gtk_button_new_with_label("Search!");
  gtk_box_pack_start(GTK_BOX(containerSearch),textSearch,FALSE,FALSE,5);
  gtk_box_pack_end(GTK_BOX(containerSearch),entryState1,TRUE,TRUE,5);
  //Add small containter
  gtk_box_pack_start(GTK_BOX(container),containerSearch,FALSE,FALSE,0);
  //Combo Box Data
  GtkWidget* comboBox=gtk_combo_box_text_new();
  gtk_box_pack_start(GTK_BOX(container),comboBox,TRUE,TRUE,0);
  g_signal_connect(entryState1,"activate",G_CALLBACK(searchForInfo1),comboBox);
  //Scroll view
  GtkWidget *scrollView=gtk_scrolled_window_new(NULL,NULL);
  gtk_widget_set_hexpand(scrollView, TRUE);
  gtk_widget_set_vexpand(scrollView, TRUE);
  gtk_box_pack_start(GTK_BOX(container),scrollView,TRUE,TRUE,0);
  GtkWidget* labelInfo=gtk_label_new("Here is data ...");
  gtk_label_set_xalign(labelInfo,0.05);
  gtk_container_add(GTK_CONTAINER(scrollView),labelInfo);
  g_signal_connect(comboBox,"changed",G_CALLBACK(printInfo1),labelInfo);
  //Show all
  gtk_widget_show_all(state1);
  gtk_window_close(GTK_WINDOW(window));
  gtk_application_remove_window(app,GTK_WINDOW(window));
}