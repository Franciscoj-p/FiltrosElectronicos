#include "data.h"
#include "controll.h"
#include "btn.h"
#include "calc.h"
#include <gtk/gtk.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <iomanip>  

void guardarDiseño(datosFiltro resultado, datosIngeniero ing, //std::vector<Filtros>,
                  std::string nombreDiseño) {
    std::string nombre = nombreDiseño;
    std::string tipo_filtro = resultado.tipo_filtro;
    std::string configuracion = resultado.configuracion;
    double r = resultado.r;
    double c = resultado.c;
    double l = resultado.l;
    double fc = resultado.fc;
    double BW = resultado.BW;
    double Q = resultado.Q;
    double G = resultado.G;
    double G_dB = resultado.G_dB;
    datosIngeniero ingeniero = ing;

    // Imprimir en consola los datos para debug
    std::cout << "Guardando diseño: " << nombre << std::endl;
    std::cout << "Tipo de filtro: " << tipo_filtro << std::endl;
    std::cout << "Configuración: " << configuracion << std::endl;
    std::cout << "Resistencia (R): " << r << " Ω" << std::endl;
    std::cout << "Capacitancia (C): " << c << " F" << std::endl;
    std::cout << "Inductancia (L): " << l << " H" << std::endl;
    std::cout << "Frecuencia de corte (fc): " << fc << " Hz" << std::endl;
    std::cout << "Ancho de banda (BW): " << BW << " Hz" << std::endl;
    std::cout << "Factor de calidad (Q): " << Q << std::endl;
    std::cout << "Ganancia (G): " << G << " (" << G_dB << " dB)" << std::endl;
    std::cout << "Datos del ingeniero:" << std::endl;
    std::cout << "  Nombre: " << ingeniero.nombre << std::endl;
    std::cout << "  Correo: " << ingeniero.correo << std::endl;
    std::cout << "  ID: " << ingeniero.id << std::endl;

    //Guardar en matriz
    //buscar si ya existe un filtro con el mismo nombre

}

std::string to_str(double valor, int decimales = 2) {  //redondear a decimales
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(decimales) << valor;
    return ss.str();
}

void mostrar_resultado(GtkWidget *textview_result, datosFiltro resultado) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview_result));
    std::string texto;

    texto += "--- PARÁMETROS ---\n";

    double r_k = resultado.r / 1000.0;        // Ω → kΩ
    double c_n = resultado.c * 1e9;           // F → nF
    double c_p = resultado.c * 1e12;          // F → pF
    double l_m = resultado.l * 1e3;           // H → mH
    double l_u = resultado.l * 1e6;           // H → μH
    double fc_k = resultado.fc / 1000.0;      // Hz → kHz
    double bw_k = resultado.BW / 1000.0;      // Hz → kHz

    if (resultado.tipo_filtro == "RC") {
        texto += "Resistencia (R): " + to_str(r_k) + " kΩ\n";
        if (c_n >= 1.0)
            texto += "Capacitancia (C): " + to_str(c_n) + " nF\n";
        else
            texto += "Capacitancia (C): " + to_str(c_p) + " pF\n";
    }
    else if (resultado.tipo_filtro == "RL") {
        texto += "Resistencia (R): " + to_str(r_k) + " kΩ\n";
        if (l_m >= 1.0)
            texto += "Inductancia (L): " + to_str(l_m) + " mH\n";
        else
            texto += "Inductancia (L): " + to_str(l_u) + " µH\n";
    }
    else if (resultado.tipo_filtro == "RLC") {
        texto += "Resistencia (R): " + to_str(r_k) + " kΩ\n";
        if (c_n >= 1.0)
            texto += "Capacitancia (C): " + to_str(c_n) + " nF\n";
        else
            texto += "Capacitancia (C): " + to_str(c_p) + " pF\n";

        if (l_m >= 1.0)
            texto += "Inductancia (L): " + to_str(l_m) + " mH\n";
        else
            texto += "Inductancia (L): " + to_str(l_u) + " µH\n";

        texto += "Factor de calidad (Q): " + to_str(resultado.Q, 3) + "\n";
    }

    texto += "Frecuencia de corte: " + to_str(fc_k) + " kHz\n";
    texto += "Ancho de banda: " + to_str(bw_k) + " kHz\n";
    texto += "Ganancia en fc: " + to_str(resultado.G, 3) + " (" + to_str(resultado.G_dB, 2) + " dB)\n";

    gtk_text_buffer_set_text(buffer, texto.c_str(), -1);
}


datosIngeniero guardarDatosIng(GtkWidget *entry_nombre, GtkWidget *entry_correo, GtkWidget *entry_id) {
    const char *nombre = gtk_entry_get_text(GTK_ENTRY(entry_nombre));
    const char *correo = gtk_entry_get_text(GTK_ENTRY(entry_correo));
    const char *id     = gtk_entry_get_text(GTK_ENTRY(entry_id));

    if (strlen(nombre) == 0 || strlen(correo) == 0 || strlen(id) == 0) {
        std::cerr << "Error: Todos los campos deben estar llenos." << std::endl;
        return {};
    }

    if (strchr(correo, '@') == nullptr || strchr(correo, '.') == nullptr) {
        std::cerr << "Error: El correo no es válido." << std::endl;
        return {};
    }

    datosIngeniero ing;
    ing.nombre = nombre;
    ing.correo = correo;
    ing.id     = id;

    return ing;
}

datosFiltro calcular_rc(GtkWidget *entry_R, GtkWidget *entry_fc, 
                        GtkWidget *radio_pasa_banda, GtkWidget *radio_rechaza_banda, 
                        GtkWidget *entry_nombre) {

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
    GtkWidget *entry_nombre) {

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
    resultado.tipo_filtro = "RL";
    resultado.configuracion = tipo_filtro;
    resultado.r = r;
    resultado.l = l;
    resultado.c = 0; // no aplica 
    resultado.fc = fc;
    resultado.BW = BW;
    resultado.G = G;
    resultado.G_dB = G_dB;
    resultado.Q = 0; // no aplica 

    return resultado;
}

datosFiltro calcular_rlc(GtkWidget *entry_R, GtkWidget *entry_C, GtkWidget *entry_fc,
                        GtkWidget *radio_pasa_banda, GtkWidget *radio_rechaza_banda,
                        GtkWidget *entry_nombre) {

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
