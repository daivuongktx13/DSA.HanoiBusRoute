#include <gtk/gtk.h>
GtkWidget *window=NULL;
GtkWidget *state1=NULL;
GtkWidget *state2=NULL;
GtkWidget *state3=NULL;
char s[3][30]={"Ubuntu","Linux","Window"};

extern void changeToState2(GtkApplication *app);
extern void changeToState3(GtkApplication *app);
extern void changeToState1(GtkApplication *app);

int i;



void on_activate (GtkApplication *app) {
  //Init

  //Create a new window
  GList* list=gtk_application_get_windows(app);
  GtkWidget* prevWindow=NULL;
  if(list!=NULL) {
    prevWindow=(GtkWidget*)list->data;
  }
  window = gtk_application_window_new (app);
  gtk_window_set_default_size(GTK_WINDOW(window),800,600);
  // GtkWidget *textView= gtk_text_view_new_with_buffer(gtk_text_buffer_new(NULL));
  GtkWidget *button1 = gtk_button_new_with_label ("In ra các xe buýt đi qua 1 bến");
  GtkWidget *button2 = gtk_button_new_with_label ("In ra các bến của 1 tuyến xe buýt");
  GtkWidget *button3 = gtk_button_new_with_label ("Tìm đường di chuyển ngắn nhất giữa 2 bến xe buýt");
  GtkWidget *container=gtk_vbox_new(TRUE,5);
  GtkWidget* text=gtk_label_new("");
  gtk_label_set_markup(GTK_LABEL(text), "<b>Hanoi Bus Application</b>");
  gtk_container_add(GTK_CONTAINER(window),container);
  gtk_box_pack_start(GTK_BOX(container),text,FALSE,TRUE,5);
  gtk_box_pack_start(GTK_BOX(container),button1,FALSE,TRUE,5);
  gtk_box_pack_start(GTK_BOX(container),button2,FALSE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(container),button3,FALSE,TRUE,0);
  g_signal_connect_swapped (button1, "clicked", G_CALLBACK (changeToState1), app);
  g_signal_connect_swapped (button2, "clicked", G_CALLBACK (changeToState2), app);
  g_signal_connect_swapped (button3, "clicked", G_CALLBACK (changeToState3), app);
  gtk_widget_show_all(window);
  if(prevWindow!=NULL) {
    gtk_window_close(GTK_WINDOW(prevWindow));
    gtk_application_remove_window(app,GTK_WINDOW(prevWindow));
  }
  // printf("App Loading time %.2lf seconds\n",time);
}
