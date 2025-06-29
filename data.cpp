#include "data.h"
#include "controll.h"
#include "btn.h"
#include "calc.h"
#include <gtk/gtk.h>
#include <iostream>

void mostrar_error(const std::string& mensaje, const std::string& titulo) {
    GtkWidget *dialog = gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(dialog), titulo.c_str());
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);

    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *label = gtk_label_new(mensaje.c_str());
    gtk_box_pack_start(GTK_BOX(content_area), label, TRUE, TRUE, 10);

    GtkWidget *action_area = gtk_dialog_get_action_area(GTK_DIALOG(dialog));

    GtkWidget *btn_ok = gtk_button_new_with_label("Aceptar");
    GtkWidget *label_ok = gtk_bin_get_child(GTK_BIN(btn_ok));
    gtk_widget_modify_fg(label_ok, GTK_STATE_NORMAL, &color_negro);
    gtk_widget_modify_fg(label_ok, GTK_STATE_PRELIGHT, &color_negro);
    g_signal_connect_swapped(btn_ok, "clicked", G_CALLBACK(gtk_widget_destroy), dialog);

    GtkWidget *btn_cancel = gtk_button_new_with_label("Cancelar");
    GtkWidget *label_cancel = gtk_bin_get_child(GTK_BIN(btn_cancel));
    gtk_widget_modify_fg(label_cancel, GTK_STATE_NORMAL, &color_negro);
    gtk_widget_modify_fg(label_cancel, GTK_STATE_PRELIGHT, &color_negro);
    g_signal_connect_swapped(btn_cancel, "clicked", G_CALLBACK(gtk_widget_destroy), dialog);

    gtk_box_pack_start(GTK_BOX(action_area), btn_ok, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(action_area), btn_cancel, TRUE, TRUE, 5);

    gtk_widget_show_all(dialog);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}



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
    std::string texto = gtk_entry_get_text(GTK_ENTRY(entry));
    if (texto.empty()) {
        std::cerr << "Error: El campo " << nombreCampo << " está vacío." << std::endl;
        return false;
    }
    return true;
}

bool validarDatosIng(GtkWidget *entry_nombre, GtkWidget *entry_correo, GtkWidget *entry_id) {
    std::string nombre = gtk_entry_get_text(GTK_ENTRY(entry_nombre));
    std::string correo = gtk_entry_get_text(GTK_ENTRY(entry_correo));
    std::string id     = gtk_entry_get_text(GTK_ENTRY(entry_id));

    if (nombre.empty() || correo.empty() || id.empty()) {
        mostrar_error("Todos los campos deben estar llenos.");
        return false;
    }

    if (correo.find('@') == std::string::npos || correo.find('.') == std::string::npos) {
        mostrar_error("El correo no es válido.");
        return false;
    }

    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Correo: " << correo << std::endl;
    std::cout << "ID: " << id << std::endl;

    return true;
}

int buscarFiltroPorNombre(const std::string& nombre) {
    for (int i = 0; i < filtros.size(); i++) {
        if (filtros[i].nombre == nombre) {
            return i;
        }
    }
    return -1;
}

bool eliminarFiltroPorNombre(const std::string& nombre) {
    int pos = buscarFiltroPorNombre(nombre);
    if (pos != -1) {
        filtros.erase(filtros.begin() + pos);
        return true;
    }
    return false;
}

void mostrarTodosLosFiltros() {
    for (int i = 0; i < filtros.size(); i++) {
        std::cout << "Filtro #" << i + 1 << ":\n";
        std::cout << "Nombre: " << filtros[i].nombre << "\n";
        std::cout << "Tipo: " << filtros[i].tipo_filtro << "\n";
        std::cout << "Configuracion: " << filtros[i].configuracion << "\n";
        std::cout << "Costo: $" << filtros[i].costo << "\n";
        std::cout << "Ingeniero: " << filtros[i].ingeniero.nombre << "\n\n";
    }
}
