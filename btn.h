#include <gtk/gtk.h>
#include <string>
#include <iostream>

struct DatosSimulacion {
    GtkWidget *dialogo;
    GtkWidget *entry_nombre_diseño;
    std::string tipo_filtro;
};

extern GtkWidget *entry_guardar;
extern GtkWidget *entry_buscar;
extern GtkWidget *entry_eliminar;
extern GtkWidget *entry_editar;


void on_ingresar(GtkWidget *widget, gpointer data);
void on_aceptar(GtkWidget *widget, gpointer data);
void on_regresar(GtkWidget *widget, gpointer data);
void on_regresarF(GtkWidget *widget, gpointer data);
void on_crear_nuevo(GtkWidget *widget, gpointer data);
void on_ver_registrados(GtkWidget *widget, gpointer data);
void on_mostrar_info(GtkWidget *widget, gpointer data);
void on_salir(GtkWidget *widget, gpointer data);
void on_editar_filtro(GtkWidget *widget, gpointer data);
void on_buscar_filtro(GtkWidget *widget, gpointer data);
void on_eliminar_filtro(GtkWidget *widget, gpointer data);
void on_regresar(GtkWidget *widget, gpointer data);
void on_rc_button(GtkWidget *widget, gpointer data);
void on_rl_button(GtkWidget *widget, gpointer data);
void on_rlc_button(GtkWidget *widget, gpointer data);
void on_guardar(GtkWidget *widget, gpointer data);
void on_calcularRC(GtkWidget *widget, gpointer data);
void on_calcularRL(GtkWidget *widget, gpointer data);
void on_calcularRLC(GtkWidget *widget, gpointer data);
void on_ok_clicked_guardar(GtkButton *button, gpointer user_data);
void on_ok_clicked_elimin(GtkButton *button, gpointer user_data);
void on_ok_clicked_busc(GtkButton *button, gpointer user_data);
void on_ok_clicked_edit(GtkButton *button, gpointer user_data);
void on_cancel_clicked(GtkButton *button, gpointer user_data);