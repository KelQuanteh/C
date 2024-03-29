#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
    
    GtkWidget *window;
    
    GtkWidget *image;
    
    gtk_init(&argc, &argv);
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    g_signal_connect(window, "destroy" ,G_CALLBACK(gtk_main_quit), NULL);
    
    image = gtk_image_new_from_file( "image.jpg" );
    
    gtk_container_add(GTK_CONTAINER(window),image);
    
    gtk_widget_show_all(window);
    
    gtk_main();
    
    return 0;
}