#ifndef CONTROLL_H
#define CONTROLL_H

#include <gtk/gtk.h>

// Ventanas globales
extern GtkWidget *win1;
extern GtkWidget *datos;
extern GtkWidget *menu;

// Funciones
void ventana_main();
void ventana_datos();
void ventana_menu();
void on_ingresar(GtkWidget *widget, gpointer data);
void on_aceptar(GtkWidget *widget, gpointer data);
void on_crear_nuevo(GtkWidget *widget, gpointer data);
void on_ver_registrados(GtkWidget *widget, gpointer data);
void on_buscar(GtkWidget *widget, gpointer data);
void on_editar(GtkWidget *widget, gpointer data);
void on_eliminar(GtkWidget *widget, gpointer data);
void on_ver_barato(GtkWidget *widget, gpointer data);
void on_ver_costoso(GtkWidget *widget, gpointer data);
void on_mostrar_info(GtkWidget *widget, gpointer data);
void on_salir(GtkWidget *widget, gpointer data);


#endif
