#include "data.h"
#include "controll.h"
#include "btn.h"
#include "calc.h"
#include <gtk/gtk.h>
#include <iostream>

bool validarEntradaNumerica(GtkWidget *entry, const char *nombreCampo) {
    const char *texto = gtk_entry_get_text(GTK_ENTRY(entry));
    if (strlen(texto) == 0) {
        std::cerr << "Error: El campo " << nombreCampo << " está vacío." << std::endl;
        return false;
    }
    char *endptr;
    double valor = strtod(texto, &endptr);
    if (*endptr != '\0' || valor <= 0) {
        std::cerr << "Error: El valor de " << nombreCampo << " no es un número válido." << std::endl;
        return false;
    }
    return true;
}

bool validarTexto(GtkWidget *entry, const char *nombreCampo) {
    const char *texto = gtk_entry_get_text(GTK_ENTRY(entry));
    if (strlen(texto) == 0) {
        std::cerr << "Error: El campo " << nombreCampo << " está vacío." << std::endl;
        return false;
    }
    return true;
}

bool guardarDatosIng(GtkWidget *entry_nombre, GtkWidget *entry_correo, GtkWidget *entry_id) {
    const char *nombre = gtk_entry_get_text(GTK_ENTRY(entry_nombre));
    const char *correo = gtk_entry_get_text(GTK_ENTRY(entry_correo));
    const char *id     = gtk_entry_get_text(GTK_ENTRY(entry_id));

    if (strlen(nombre) == 0 || strlen(correo) == 0 || strlen(id) == 0) {
        std::cerr << "Error: Todos los campos deben estar llenos." << std::endl;
        return false;
    }

    if (strchr(correo, '@') == nullptr || strchr(correo, '.') == nullptr) {
        std::cerr << "Error: El correo no es válido." << std::endl;
        return false;
    }

    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Correo: " << correo << std::endl;
    std::cout << "ID: " << id << std::endl;
    return true;
}