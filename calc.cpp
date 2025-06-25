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

        if (resultado.tipo_filtro == "RC" || resultado.tipo_filtro == "RL") {
            texto = 
            "Frecuencia de corte: " + std::to_string(resultado.fc) + " Hz\n" +
            "Ancho de banda: " + std::to_string(resultado.BW) + " Hz\n" +
            "Ganancia: " + std::to_string(resultado.G) + " (" + std::to_string(resultado.G_dB) + " dB)\n";
        } else if (resultado.tipo_filtro == "RLC") {
            texto = 
            "Frecuencia de corte: " + std::to_string(resultado.fc) + " Hz\n" +
            "Ancho de banda: " + std::to_string(resultado.BW) + " Hz\n" +
            "Ganancia: " + std::to_string(resultado.G) + " (" + std::to_string(resultado.G_dB) + " dB)\n" +
            "Factor de calidad: " + std::to_string(resultado.Q) + "\n";
        }
        gtk_text_buffer_set_text(buffer, texto.c_str(), -1);
}

datosFiltro calcular_rc(GtkWidget *entry_R, GtkWidget *entry_C, GtkWidget *radio_pasa_banda, GtkWidget *radio_rechaza_banda, GtkWidget *entry_nombre, GtkWidget *entry_id) {
    int r = std::atoi(gtk_entry_get_text(GTK_ENTRY(entry_R)));
    int c = std::atoi(gtk_entry_get_text(GTK_ENTRY(entry_C)));
    int l = 0;
    std::string tipo_filtro; 

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_pasa_banda))) {
        tipo_filtro = "High-pass"; 
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_rechaza_banda))) {
        tipo_filtro = "Low-pass";
    } 

    double fc = 1.0 / (2 * M_PI * r * c);  // Frecuencia de corte en Hz
    double G = 1.0 / sqrt(2); //Ganancia en punto de corte del filtro RC
    double G_dB = 20 * log10(G); //Ganancia en decibelios
    double BW = fc; //Ancho de banda del filtro RC

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
    resultado.l = l; 
    resultado.Q = 0;
    resultado.fc = fc;
    resultado.G = G;
    resultado.G_dB = G_dB;
    resultado.BW = BW;

    return resultado;
}

datosFiltro calcular_rl(GtkWidget *entry_R, GtkWidget *entry_L, GtkWidget *radio_pasa_banda, GtkWidget *radio_rechaza_banda, GtkWidget *entry_nombre, GtkWidget *entry_id) {
    int r = std::atoi(gtk_entry_get_text(GTK_ENTRY(entry_R)));
    int l = std::atoi(gtk_entry_get_text(GTK_ENTRY(entry_L)));
    int c = 0;
    std::string tipo_filtro;

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_pasa_banda))) {
        tipo_filtro = "High-pass";
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_rechaza_banda))) {
        tipo_filtro = "Low-pass"; 
    } 

    double fc = r / (2 * M_PI * l);  // Frecuencia de corte en Hz
    double G = 1.0 / sqrt(2); //Ganancia en punto de corte del filtro RC
    double G_dB = 20 * log10(G); //Ganancia en decibelios
    double BW = fc; //Ancho de banda del filtro RC

    std::cout << "Frecuencia de corte: " << fc << " Hz\n";
    std::cout << "Ganancia: " << G << " (" << G_dB << " dB)\n";
    std::cout << "Ancho de banda: " << BW << " Hz\n";

    datosFiltro resultado;

    resultado.nombre = gtk_entry_get_text(GTK_ENTRY(entry_nombre));
    resultado.id = gtk_entry_get_text(GTK_ENTRY(entry_id));
    resultado.tipo_filtro = "RL";
    resultado.configuracion = tipo_filtro;
    resultado.r = r;
    resultado.c = c;
    resultado.l = l; 
    resultado.Q = 0;
    resultado.fc = fc;
    resultado.G = G;
    resultado.G_dB = G_dB;
    resultado.BW = BW;

    return resultado;
}

datosFiltro calcular_rlc(GtkWidget *entry_R, GtkWidget *entry_L, GtkWidget *entry_C, GtkWidget *radio_pasa_banda, GtkWidget *radio_rechaza_banda, GtkWidget *entry_nombre, GtkWidget *entry_id) {
    int r = std::atoi(gtk_entry_get_text(GTK_ENTRY(entry_R)));
    int l = std::atoi(gtk_entry_get_text(GTK_ENTRY(entry_L)));
    int c = std::atoi(gtk_entry_get_text(GTK_ENTRY(entry_C)));
    std::string tipo_filtro;


    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_pasa_banda))) {
        tipo_filtro = "High-pass"; 
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_rechaza_banda))) {
        tipo_filtro = "Low-pass"; 
    }     

    double fc = 1.0 / (2 * M_PI * sqrt(l * c)); // Frecuencia de corte en Hz
    double BW = r / l;                          // Ancho de banda
    double Q = fc / BW;                       // Factor de calidad
    double G = 1.0 / sqrt(2);                   //Ganancia en punto de corte del filtro RC
    double G_dB = 20 * log10(G);              // Ganancia en decibelios

    std::cout << "Frecuencia de resonancia: " << fc << " Hz\n";
    std::cout << "Ganancia: " << G << " (" << G_dB << " dB)\n";
    std::cout << "Ancho de banda: " << BW << " Hz\n";
    std::cout << "Factor de calidad: " << Q << "\n";

    datosFiltro resultado;

    resultado.nombre = gtk_entry_get_text(GTK_ENTRY(entry_nombre));
    resultado.id = gtk_entry_get_text(GTK_ENTRY(entry_id));
    resultado.tipo_filtro = "RLC";
    resultado.configuracion = tipo_filtro;
    resultado.r = r;
    resultado.c = c;
    resultado.l = l; 
    resultado.Q = Q;
    resultado.fc = fc;
    resultado.G = G;
    resultado.G_dB = G_dB;
    resultado.BW = BW;

    return resultado;
}