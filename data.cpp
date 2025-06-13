#include "data.h"
#include "controll.h"
#include "btn.h"
#include "calc.h"
#include <gtk/gtk.h>
#include <iostream>

void guardarDatosIng(GtkWidget *entry_nombre, GtkWidget *entry_correo, GtkWidget *entry_id) {
    std::string nombre = gtk_entry_get_text(GTK_ENTRY(entry_nombre));
    std::string correo = gtk_entry_get_text(GTK_ENTRY(entry_correo));
    std::string id     = gtk_entry_get_text(GTK_ENTRY(entry_id));
	std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Correo: " << correo << std::endl;
    std::cout << "ID: " << id << std::endl;
}