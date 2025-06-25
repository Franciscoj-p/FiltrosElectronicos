#include "data.h"
#include "controll.h"
#include "btn.h"
#include "calc.h"
#include <gtk/gtk.h>
#include <iostream>
#include <cmath>
#include <vector>

void mostrar_resultado(GtkWidget *textview_result, datosFiltro resultado) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview_result));
    std::string texto;

    texto += "--- DATOS DEL FILTRO ---\n";
    texto += "Nombre del diseño: " + resultado.nombre + "\n";
    texto += "ID del diseño: " + resultado.id + "\n";
    texto += "Tipo de filtro: " + resultado.tipo_filtro + "\n";
    texto += "Configuración: " + resultado.configuracion + "\n";

    texto += "\n--- PARÁMETROS ---\n";

    if (resultado.tipo_filtro == "RC") {
        texto += "Resistencia (R): " + std::to_string(resultado.r) + " Ω\n";
        texto += "Capacitancia (C): " + std::to_string(resultado.c) + " F\n";
    }
    else if (resultado.tipo_filtro == "RL") {
        texto += "Resistencia (R): " + std::to_string(resultado.r) + " Ω\n";
        texto += "Inductancia (L): " + std::to_string(resultado.l) + " H\n";
    }
    else if (resultado.tipo_filtro == "RLC") {
        texto += "Resistencia (R): " + std::to_string(resultado.r) + " Ω\n";
        texto += "Capacitancia (C): " + std::to_string(resultado.c) + " F\n";
        texto += "Inductancia (L): " + std::to_string(resultado.l) + " H\n";
        texto += "Factor de calidad (Q): " + std::to_string(resultado.Q) + "\n";
    }

    texto += "Frecuencia de corte: " + std::to_string(resultado.fc) + " Hz\n";
    texto += "Ancho de banda: " + std::to_string(resultado.BW) + " Hz\n";
    texto += "Ganancia en fc: " + std::to_string(resultado.G) + " (" + std::to_string(resultado.G_dB) + " dB)\n";

    texto += "\n--- DATOS DEL INGENIERO ---\n";
    texto += "Nombre: " + resultado.ingeniero.nombre + "\n";
    texto += "Correo: " + resultado.ingeniero.correo + "\n";
    texto += "ID: " + resultado.ingeniero.id + "\n";

    gtk_text_buffer_set_text(buffer, texto.c_str(), -1);
}

datosIngeniero guardarDatosIng(GtkWidget *entry_nombre, GtkWidget *entry_correo, GtkWidget *entry_id) {
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

    datosIngeniero ing;
    ing.nombre = nombre;
    ing.correo = correo;
    ing.id     = id;

    return ing;
}

datosFiltro calcular_rc(GtkWidget *entry_R, GtkWidget *entry_C, GtkWidget *entry_fc, 
                        GtkWidget *radio_pasa_banda, GtkWidget *radio_rechaza_banda, 
                        GtkWidget *entry_nombre, GtkWidget *entry_id) {

    double r = std::atof(gtk_entry_get_text(GTK_ENTRY(entry_R)));
    double fc = std::atof(gtk_entry_get_text(GTK_ENTRY(entry_fc)));
    double c = 1.0 / (2 * M_PI * r * fc);  // Cálculo del capacitor
    std::string tipo_filtro; 

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_pasa_banda))) {
        tipo_filtro = "High-pass"; 
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_rechaza_banda))) {
        tipo_filtro = "Low-pass";
    } 

    // Ganancia en punto de corte
    double G = 1.0 / sqrt(2); // ≈ 0.707
    double G_dB = 20 * log10(G); // ≈ -3.01 dB
    double BW = fc; 

    std::cout << "Resistencia (R): " << r << " ohm\n";
    std::cout << "Capacitancia (C): " << c << " F\n";
    std::cout << "Frecuencia de corte: " << fc << " Hz\n";
    std::cout << "Ganancia: " << G << " (" << G_dB << " dB)\n";
    std::cout << "Ancho de banda: " << BW << " Hz\n";

    datosFiltro resultado;
    resultado.nombre = gtk_entry_get_text(GTK_ENTRY(entry_nombre));
    resultado.id = gtk_entry_get_text(GTK_ENTRY(entry_id));
    resultado.tipo_filtro = "RC";
    resultado.configuracion = tipo_filtro;
    resultado.r = r;
    resultado.c = c;
    resultado.l = 0; // No aplica
    resultado.fc = fc;
    resultado.BW = BW;
    resultado.Q = 0; // No aplica
    resultado.G = G;
    resultado.G_dB = G_dB;

    return resultado;
}

datosFiltro calcular_rl(GtkWidget *entry_R, GtkWidget *entry_fc,
    GtkWidget *radio_pasa_banda, GtkWidget *radio_rechaza_banda,
    GtkWidget *entry_nombre, GtkWidget *entry_id) {

    double r = std::atof(gtk_entry_get_text(GTK_ENTRY(entry_R)));
    double fc = std::atof(gtk_entry_get_text(GTK_ENTRY(entry_fc)));
    double l = r / (2 * M_PI * fc);// Calcular inductancia 

    std::string tipo_filtro;
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_pasa_banda))) {
    tipo_filtro = "High-pass";
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_rechaza_banda))) {
    tipo_filtro = "Low-pass";
    }

    // Ganancia en punto de corte
    double G = 1.0 / sqrt(2); // ~0.707
    double G_dB = 20 * log10(G); // ~ -3.01 dB
    double BW = fc;

    std::cout << "Resistencia (R): " << r << " ohm\n";
    std::cout << "Inductancia (L): " << l << " H\n";
    std::cout << "Frecuencia de corte: " << fc << " Hz\n";
    std::cout << "Ganancia: " << G << " (" << G_dB << " dB)\n";
    std::cout << "Ancho de banda: " << BW << " Hz\n";

    datosFiltro resultado;
    resultado.nombre = gtk_entry_get_text(GTK_ENTRY(entry_nombre));
    resultado.id = gtk_entry_get_text(GTK_ENTRY(entry_id));
    resultado.tipo_filtro = "RL";
    resultado.configuracion = tipo_filtro;
    resultado.r = r;
    resultado.l = l;
    resultado.c = = 0; // no aplica 
    resultado.fc = fc;
    resultado.BW = BW;
    resultado.G = G;
    resultado.G_dB = G_dB;
    resultado.Q = 0; // no aplica 

    return resultado;
}

datosFiltro calcular_rlc(GtkWidget *entry_R, GtkWidget *entry_C, GtkWidget *entry_fc,
                        GtkWidget *radio_pasa_banda, GtkWidget *radio_rechaza_banda,
                        GtkWidget *entry_nombre, GtkWidget *entry_id) {

    double r = std::atof(gtk_entry_get_text(GTK_ENTRY(entry_R)));
    double c = std::atof(gtk_entry_get_text(GTK_ENTRY(entry_C)));
    double fc = std::atof(gtk_entry_get_text(GTK_ENTRY(entry_fc)));
    double l = 1.0 / (pow(2 * M_PI * fc, 2) * c);// Calcular inductancia a partir de fc y C

    double BW = r / l;
    double Q = fc / BW;
    double G = 1.0 / sqrt(2); // Para -3 dB en corte
    double G_dB = 20 * log10(G);

    std::string tipo_filtro;
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_pasa_banda))) {
    tipo_filtro = "Band-pass";
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_rechaza_banda))) {
    tipo_filtro = "Band-stop";
    }

    std::cout << "Resistencia (R): " << r << " ohm\n";
    std::cout << "Capacitancia (C): " << c << " F\n";
    std::cout << "Inductancia (L): " << l << " H\n";
    std::cout << "Frecuencia de resonancia: " << fc << " Hz\n";
    std::cout << "Ancho de banda: " << BW << " Hz\n";
    std::cout << "Factor de calidad: " << Q << "\n";
    std::cout << "Ganancia: " << G << " (" << G_dB << " dB)\n";

    datosFiltro resultado;
    resultado.nombre = gtk_entry_get_text(GTK_ENTRY(entry_nombre));
    resultado.id = gtk_entry_get_text(GTK_ENTRY(entry_id));
    resultado.tipo_filtro = "RLC";
    resultado.configuracion = tipo_filtro;
    resultado.r = r;
    resultado.c = c;
    resultado.l = l;
    resultado.fc = fc;
    resultado.BW = BW;
    resultado.Q = Q;
    resultado.G = G;
    resultado.G_dB = G_dB;

    return resultado;
}
