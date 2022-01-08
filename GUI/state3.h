#include <gtk/gtk.h>

extern GtkWidget *window;
extern GtkWidget *state1;
extern GtkWidget *state2;
extern GtkWidget *state3;
extern void on_activate (GtkApplication *app);
extern char s[3][30];
extern Graph graph;
extern JRB line;
extern void getMinimumTour(Graph graph,JRB line);

//Tìm đường di chuyển ngắn nhất giữa 2 bến xe buýt
void changeToState3(GtkApplication *app){
  state3 = gtk_application_window_new (app);
  gtk_window_set_default_size(GTK_WINDOW(state3),800,600);
  GtkWidget* backButton=gtk_button_new_with_label("Back");
  GtkWidget* text=gtk_label_new("Tìm đường di chuyển ngắn nhất giữa 2 bến xe buýt");
  GtkWidget *container=gtk_vbox_new(TRUE,5);
  gtk_container_add(state3,container);
  g_signal_connect_swapped(backButton,"clicked",G_CALLBACK(on_activate),app);
  //Add to main container
  gtk_box_pack_start(GTK_BOX(container),backButton,TRUE,TRUE,5);
  gtk_box_pack_start(GTK_BOX(container),text,FALSE,FALSE,5);
  // GtkWidget* seperator=gtk_hseparator_new();
  // gtk_box_pack_start(GTK_BOX(container),seperator,TRUE,FALSE,10);
  //Container Search Bar
  GtkWidget *containerSearch=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
  GtkWidget* textSearch=gtk_label_new("Enter Source Place: ");
  GtkWidget* entryState1=gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(containerSearch),textSearch,TRUE,TRUE,5);
  gtk_box_pack_start(GTK_BOX(containerSearch),entryState1,TRUE,TRUE,5);
  GtkWidget* textSearch2=gtk_label_new("Enter Destination Place: ");
  GtkWidget* entryState2=gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(containerSearch),textSearch2,TRUE,TRUE,5);
  gtk_box_pack_start(GTK_BOX(containerSearch),entryState2,TRUE,TRUE,5);
  //Add small containter to bigone
  gtk_box_pack_start(GTK_BOX(container),containerSearch,FALSE,FALSE,0);
  //Container for two combobox
  GtkWidget* containerComboBoxs=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
  GtkWidget* srcPlaceCB=gtk_combo_box_new();
  GtkWidget* desPlaceCB=gtk_combo_box_new();
  gtk_box_pack_start(GTK_BOX(containerComboBoxs),srcPlaceCB,TRUE,TRUE,5);
  gtk_box_pack_start(GTK_BOX(containerComboBoxs),desPlaceCB,TRUE,TRUE,5);
  gtk_box_pack_start(GTK_BOX(container),containerComboBoxs,TRUE,TRUE,0);
  //Button to start find route and Time
  GtkWidget* boxTemp=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
  GtkWidget* flowTemp1=gtk_flow_box_new();
  GtkWidget* flowTemp2=gtk_flow_box_new();
  GtkButton* buttonStart=gtk_button_new_with_label("Find Route!");
  gtk_box_pack_start(GTK_BOX(boxTemp),flowTemp1,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(boxTemp),buttonStart,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(boxTemp),flowTemp2,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(container),boxTemp,TRUE,FALSE,0);
  //Scroll view for representation of data
  GtkWidget *scrollView=gtk_scrolled_window_new(NULL,NULL);
  gtk_widget_set_hexpand(scrollView, TRUE);
  gtk_widget_set_vexpand(scrollView, TRUE);
  gtk_box_pack_start(GTK_BOX(container),scrollView,TRUE,TRUE,5);


  GtkWidget* labelInfo=gtk_label_new("Infomation Appear Here\n");
  gtk_container_add(GTK_CONTAINER(scrollView),labelInfo);

  gtk_widget_show_all(state3);
  gtk_window_close(GTK_WINDOW(window));
  gtk_application_remove_window(app,window);
}