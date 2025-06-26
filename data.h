#include <gtk/gtk.h>
#include <string>
#include <iostream>

void mostrar_error(const std::string& mensaje, const std::string& titulo = "Aviso");
bool validarEntradaNumerica(GtkWidget *entry, const char *nombreCampo);
bool validarTexto(GtkWidget *entry, const char *nombreCampo);
bool validarDatosIng(GtkWidget *entry_nombre, GtkWidget *entry_correo, GtkWidget *entry_id);
int buscarFiltroPorNombre(const std::string& nombre);
bool eliminarFiltroPorNombre(const std::string& nombre);
void mostrarTodosLosFiltros();