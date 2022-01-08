#include <gtk/gtk.h>
#include "../GUI/state1.h"
#include "../GUI/state2.h"
#include "../GUI/state3.h"
#include "../GUI/state.h"


int main (int argc, char *argv[]) {
  // Create a new application
  GtkApplication *app = gtk_application_new ("com.example.GtkApplication",
                                             G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (on_activate), NULL);
  return g_application_run (G_APPLICATION (app), argc, argv);
}