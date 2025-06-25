#include "data.h"
#include "controll.h"
#include "btn.h"
#include "calc.h"
#include <gtk/gtk.h>
#include <iostream>

void mostrar_error(const gchar *mensaje, const gchar *titulo) {
    GtkWidget *dialog = gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(dialog), titulo);
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);

    // Área de contenido
    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *label = gtk_label_new(mensaje);
    gtk_box_pack_start(GTK_BOX(content_area), label, TRUE, TRUE, 10);

    // Área de acción personalizada
    GtkWidget *action_area = gtk_dialog_get_action_area(GTK_DIALOG(dialog));

    // Botón Aceptar
    GtkWidget *btn_ok = gtk_button_new_with_label("Aceptar");
    GtkWidget *label_ok = gtk_bin_get_child(GTK_BIN(btn_ok));
    gtk_widget_modify_fg(label_ok, GTK_STATE_NORMAL, &color_negro);
    gtk_widget_modify_fg(label_ok, GTK_STATE_PRELIGHT, &color_negro);
    g_signal_connect_swapped(btn_ok, "clicked", G_CALLBACK(gtk_widget_destroy), dialog);

    // Botón Cancelar
    GtkWidget *btn_cancel = gtk_button_new_with_label("Cancelar");
    GtkWidget *label_cancel = gtk_bin_get_child(GTK_BIN(btn_cancel));
    gtk_widget_modify_fg(label_cancel, GTK_STATE_NORMAL, &color_negro);
    gtk_widget_modify_fg(label_cancel, GTK_STATE_PRELIGHT, &color_negro);
    g_signal_connect_swapped(btn_cancel, "clicked", G_CALLBACK(gtk_widget_destroy), dialog);

    // Agregar botones al área de acción
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
    const char *texto = gtk_entry_get_text(GTK_ENTRY(entry));
    if (strlen(texto) == 0) {
        std::cerr << "Error: El campo " << nombreCampo << " está vacío." << std::endl;
        return false;
    }
    return true;
}

bool validarDatosIng(GtkWidget *entry_nombre, GtkWidget *entry_correo, GtkWidget *entry_id) {
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