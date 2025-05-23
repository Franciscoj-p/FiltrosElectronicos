#include "controll.h"


GtkWidget *win1;
GtkWidget *datos;
GtkWidget *menu;

void ventana_main() {
    win1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(win1), "FILTROS ELECTRONICOS");
    gtk_window_set_default_size(GTK_WINDOW(win1), 350, 250);
    gtk_container_set_border_width(GTK_CONTAINER(win1), 15);
    g_signal_connect(G_OBJECT(win1), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_vbox_new(FALSE, 10);
    gtk_container_add(GTK_CONTAINER(win1), vbox);

    GtkWidget *label_msg = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_msg), "<span font_desc='20' weight='bold'>Bienvenido</span>");
    gtk_misc_set_alignment(GTK_MISC(label_msg), 0.5, 0.5);
    gtk_box_pack_start(GTK_BOX(vbox), label_msg, FALSE, FALSE, 10);

    GtkWidget *label_bienvenida = gtk_label_new("Bienvenido al programa de ayuda para el diseño y análisis de circuitos electrónicos");
    gtk_misc_set_alignment(GTK_MISC(label_bienvenida), 0, 0.5);
    gtk_box_pack_start(GTK_BOX(vbox), label_bienvenida, FALSE, FALSE, 0);

    GtkWidget *button = gtk_button_new_with_label("Ingresar");
    GtkWidget *label = gtk_bin_get_child(GTK_BIN(button));
    GdkColor color_negro = {0, 0, 0, 0};
    gtk_widget_modify_fg(label, GTK_STATE_NORMAL, &color_negro);
	gtk_widget_modify_fg(label, GTK_STATE_PRELIGHT, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 15);

    g_signal_connect(button, "clicked", G_CALLBACK(on_ingresar), NULL);

    gtk_widget_show_all(win1);
}

void ventana_datos() {
    datos = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(datos), "Ingreso de Datos - Ingeniero");
    gtk_window_set_default_size(GTK_WINDOW(datos), 350, 250);
    gtk_container_set_border_width(GTK_CONTAINER(datos), 15);
    g_signal_connect(G_OBJECT(datos), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_vbox_new(FALSE, 10);
    gtk_container_add(GTK_CONTAINER(datos), vbox);

    GtkWidget *label_msg = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_msg), "<span font_desc='20' weight='bold'>Ingrese sus datos</span>");
    gtk_misc_set_alignment(GTK_MISC(label_msg), 0.5, 0.5);
    gtk_box_pack_start(GTK_BOX(vbox), label_msg, FALSE, FALSE, 10);

    GtkWidget *label_id = gtk_label_new("ID Ingeniero:");
    gtk_misc_set_alignment(GTK_MISC(label_id), 0, 0.5);
    GtkWidget *entry_id = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), label_id, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_id, FALSE, FALSE, 5);

    GtkWidget *label_nombre = gtk_label_new("Nombre:");
    gtk_misc_set_alignment(GTK_MISC(label_nombre), 0, 0.5);
    GtkWidget *entry_nombre = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), label_nombre, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_nombre, FALSE, FALSE, 5);

    GtkWidget *label_correo = gtk_label_new("Correo:");
    gtk_misc_set_alignment(GTK_MISC(label_correo), 0, 0.5);
    GtkWidget *entry_correo = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), label_correo, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_correo, FALSE, FALSE, 5);

    GtkWidget *button = gtk_button_new_with_label("Aceptar");
    GtkWidget *label = gtk_bin_get_child(GTK_BIN(button));
    GdkColor color_negro = {0, 0, 0, 0};
    gtk_widget_modify_fg(label, GTK_STATE_NORMAL, &color_negro);
	gtk_widget_modify_fg(label, GTK_STATE_PRELIGHT, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 15);
	
	g_signal_connect(button, "clicked", G_CALLBACK(on_aceptar), NULL);

    gtk_widget_show_all(datos);
}

void ventana_menu(){
    
    menu = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(menu), "Menú Principal");
    gtk_window_set_default_size(GTK_WINDOW(menu), 400, 400);
    gtk_container_set_border_width(GTK_CONTAINER(menu), 15);
    g_signal_connect(G_OBJECT(menu), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_vbox_new(FALSE, 10);
    gtk_container_add(GTK_CONTAINER(menu), vbox);

    GtkWidget *label_msg = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_msg), "<span font_desc='18' weight='bold'>Menú Principal</span>");
    gtk_misc_set_alignment(GTK_MISC(label_msg), 0.5, 0.5);
    gtk_box_pack_start(GTK_BOX(vbox), label_msg, FALSE, FALSE, 10);

    const char* opciones[] = {    //arreglo labels
        "1. Crear nuevo diseño de filtro",
        "2. Mostrar diseños",
        "3. Mostrar info del programa",
        "4. Salir"
    };

    GCallback funciones[] = {  //arreglo enlace a funciones
        G_CALLBACK(on_crear_nuevo),
        G_CALLBACK(on_ver_registrados),
        G_CALLBACK(on_mostrar_info),
        G_CALLBACK(on_salir)
    };

    for (int i = 0; i < 4; i++) {   //bucle para crear botones
        GtkWidget *button = gtk_button_new_with_label(opciones[i]);
        GtkWidget *label = gtk_bin_get_child(GTK_BIN(button));
		GdkColor color_negro = {0, 0, 0, 0};
		gtk_widget_modify_fg(label, GTK_STATE_NORMAL, &color_negro);
		gtk_widget_modify_fg(label, GTK_STATE_PRELIGHT, &color_negro);
        gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 5);
        g_signal_connect(button, "clicked", funciones[i], NULL);
    }

    gtk_widget_show_all(menu);
}

// Función del botón

void on_crear_nuevo(GtkWidget *widget, gpointer data)     { /* lógica aquí */ } //enviar a diseñar

void on_ver_registrados(GtkWidget *widget, gpointer data) { /* lógica aquí */ }

void on_buscar(GtkWidget *widget, gpointer data)          { /* lógica aquí */ }

void on_editar(GtkWidget *widget, gpointer data)          { /* lógica aquí */ }

void on_eliminar(GtkWidget *widget, gpointer data)        { /* lógica aquí */ }

void on_ver_barato(GtkWidget *widget, gpointer data)      { /* lógica aquí */ }

void on_ver_costoso(GtkWidget *widget, gpointer data)     { /* lógica aquí */ }

void on_mostrar_info(GtkWidget *widget, gpointer data)    { /* lógica aquí */ }

void on_salir(GtkWidget *widget, gpointer data)           { gtk_main_quit(); }

void on_ingresar(GtkWidget *widget, gpointer data) { gtk_widget_hide(win1); ventana_datos(); }

void on_aceptar(GtkWidget *widget, gpointer data) { gtk_widget_hide(datos); ventana_menu();  }
