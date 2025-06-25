#include <gtk/gtk.h>

bool guardarDatosIng(GtkWidget *entry_nombre, GtkWidget *entry_correo, GtkWidget *entry_id);
bool validarEntradaNumerica(GtkWidget *entry, const char *nombreCampo);
bool validarTexto(GtkWidget *entry, const char *nombreCampo);
