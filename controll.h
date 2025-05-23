#ifndef CONTROLL_H
#define CONTROLL_H

#include <gtk/gtk.h>

// Ventanas globales
extern GtkWidget *win1;
extern GtkWidget *datos;
extern GtkWidget *menu;
extern GtkWidget *mostrar;
extern GtkWidget *diseñar;
extern GtkWidget *info;

// Funciones
void ventana_main();
void ventana_datos();
void ventana_menu();
void ventana_mostrar();
void ventana_diseñar();
void ventana_info();
void on_ingresar(GtkWidget *widget, gpointer data);
void on_aceptar(GtkWidget *widget, gpointer data);
void on_regresar(GtkWidget *widget, gpointer data);
void on_crear_nuevo(GtkWidget *widget, gpointer data);
void on_ver_registrados(GtkWidget *widget, gpointer data);
void on_mostrar_info(GtkWidget *widget, gpointer data);
void on_salir(GtkWidget *widget, gpointer data);
void on_editar_filtro(GtkWidget *widget, gpointer data);
void on_buscar_filtro(GtkWidget *widget, gpointer data);
void on_eliminar_filtro(GtkWidget *widget, gpointer data);
void on_regresar(GtkWidget *widget, gpointer data);
void on_ok_clicked_elimin(GtkButton *button, gpointer user_data);
void on_ok_clicked_busc(GtkButton *button, gpointer user_data);
void on_ok_clicked_edit(GtkButton *button, gpointer user_data);
void on_cancel_clicked(GtkButton *button, gpointer user_data);

#endif
