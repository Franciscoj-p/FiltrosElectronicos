#include <gtk/gtk.h>

bool validarEntradaNumerica(GtkWidget *entry, const char *nombreCampo);
bool validarTexto(GtkWidget *entry, const char *nombreCampo);
void mostrar_error(const gchar *mensaje, const gchar *titulo = "Error");