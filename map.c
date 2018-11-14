#include "map.h"

#include <gtk/gtk.h>

static GtkWidget *window;
static GtkWidget *canvas;
static GtkWidget *vbox;
static GtkWidget *button;
static GdkGC *map_gc;

static void quit () {
    gtk_exit(0);
}

void map_init(unsigned short cols, unsigned short rows, action_func_t facc) {
    gtk_init(NULL, NULL);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_signal_connect(GTK_OBJECT(window), "destroy", GTK_SIGNAL_FUNC(quit), NULL);

    vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show(vbox);

    canvas = gtk_drawing_area_new();
    gtk_drawing_area_size(GTK_DRAWING_AREA(canvas), cols, rows);
    gtk_box_pack_start(GTK_BOX(vbox), canvas, TRUE, TRUE, 0);
    gtk_widget_show(canvas);

    button = gtk_button_new_with_label ("Start");
    gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);
    gtk_signal_connect_object(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(facc), NULL);
    gtk_widget_show(button);
    
    gtk_widget_show(window);
    map_gc = gdk_gc_new(canvas->window);
    gtk_main();
}

void map_draw_dot(unsigned short col, unsigned short row) {
    gdk_draw_point(canvas->window, map_gc, col, row);
}

void map_draw_rectangle(unsigned short col, unsigned short row, unsigned short width, unsigned short length) {
    gdk_draw_rectangle(canvas->window, map_gc, TRUE, col, row, width, length);
}
