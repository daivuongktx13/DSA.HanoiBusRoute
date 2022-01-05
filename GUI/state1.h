#include <gtk/gtk.h>

extern GtkWidget *window;
extern GtkWidget *state1;
extern GtkWidget *state2;
extern GtkWidget *state3;
extern void on_activate (GtkApplication *app);
extern char s[3][30];


void searchForInfo(GtkWidget* entry,GtkComboBox* combobox){
  gchar* text=gtk_entry_get_text(entry);
  int i;
  gtk_combo_box_text_remove_all(combobox);
  for(i=0;i<3;i++){
    char* find=strstr(s[i],text);
    if(find!=NULL) {
      gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combobox),s[i]);
    }
  }
}
void printInfo1(GtkComboBox* combobox,GtkLabel* label){
  gchar* text=gtk_combo_box_text_get_active_text(combobox);
  gtk_label_set_text(label,text);
  g_free(text);
}
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
  gtk_box_pack_start(GTK_BOX(container),comboBox,TRUE,TRUE,5);
  g_signal_connect(entryState1,"activate",G_CALLBACK(searchForInfo),comboBox);
  //Scroll view
  GtkWidget *scrollView=gtk_scrolled_window_new(NULL,NULL);
  gtk_widget_set_hexpand(scrollView, TRUE);
  gtk_widget_set_vexpand(scrollView, TRUE);
  gtk_box_pack_start(GTK_BOX(container),scrollView,TRUE,TRUE,5);
  GtkWidget* labelInfo=gtk_label_new("Nothing have search");
  gtk_container_add(GTK_CONTAINER(scrollView),labelInfo);
  g_signal_connect(comboBox,"changed",G_CALLBACK(printInfo1),labelInfo);
  //Show all
  gtk_widget_show_all(state1);
  gtk_window_close(GTK_WINDOW(window));
  gtk_application_remove_window(app,GTK_WINDOW(window));
}