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

double costo_componente(double valor, std::string tipo) {
    if (tipo == "R") {
        return COSTO_RESISTENCIA;
    } else if (tipo == "C") {
        if (valor < 1e-7) return COSTO_CAP_BAJO;    // < 100nF
        else if (valor < 1e-5) return COSTO_CAP_MEDIO; // < 10uF
        else return COSTO_CAP_ALTO;
    } else if (tipo == "L") {
        if (valor < 1e-3) return COSTO_IND_BAJO;    // < 1mH
        else if (valor < 1e-1) return COSTO_IND_MEDIO; // < 100mH
        else return COSTO_IND_ALTO;
    }

    return 0.0;
}


double costo_total(const datosFiltro& filtro) {
    double costo_total = 0.0;

    if (filtro.r > 0) costo_total += costo_componente(filtro.r, "R");
    if (filtro.c > 0) costo_total += costo_componente(filtro.c, "C");
    if (filtro.l > 0) costo_total += costo_componente(filtro.l, "L");

    return costo_total;
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
    texto += "Error de frecuencia de corte: " + to_str(resultado.err, 2) + "%\n";
    texto += "Ancho de banda: " + to_str(bw_k) + " kHz\n";
    texto += "Ganancia en fc: " + to_str(resultado.G, 3) + " (" + to_str(resultado.G_dB, 2) + " dB)\n";
    texto += "Costo total del filtro: $" + to_str(resultado.costo, 2) + "\n";

    gtk_text_buffer_set_text(buffer, texto.c_str(), -1);
}


datosIngeniero guardarDatosIng(GtkWidget *entry_nombre, GtkWidget *entry_correo, GtkWidget *entry_id) {

        std::string nombre = gtk_entry_get_text(GTK_ENTRY(entry_nombre));
        std::string correo = gtk_entry_get_text(GTK_ENTRY(entry_correo));
        std::string id     = gtk_entry_get_text(GTK_ENTRY(entry_id));

        datosIngeniero ing;
        ing.nombre = nombre;
        ing.correo = correo;
        ing.id     = id;
        return ing; 
}

double valor_comercial(double valor, const std::vector<double>& serie) {
    double aprox = 0;
    double mError = std::numeric_limits<double>::max(); //maximo valor de error

    // probar 
    for (int exp = -12; exp <= 6; ++exp) {
        double factor = std::pow(10.0, exp);

        for (size_t i = 0; i < serie.size(); ++i) {
            double prueba = serie[i] * factor;
            double error = std::abs(valor - prueba);

            if (error < mError) {
                aprox = prueba;
                mError = error;
            }
        }
    }

    return aprox;
}

double calcular_error_fc(double fc_ingresada, double fc_real) {

    double error = std::abs(fc_real - fc_ingresada) / fc_ingresada;
    return error * 100.0;
}


datosFiltro calcular_rc(GtkWidget *entry_R, GtkWidget *entry_fc, 
                        GtkWidget *radio_pasa_banda, GtkWidget *radio_rechaza_banda, GtkWidget *radio_serie12,
                        GtkWidget *radio_serie24, GtkWidget *entry_nombre) {

    double r = std::atof(gtk_entry_get_text(GTK_ENTRY(entry_R)));
    double fc_ideal = std::atof(gtk_entry_get_text(GTK_ENTRY(entry_fc)));
    double c = 1.0 / (2 * M_PI * r * fc_ideal);  // Cálculo del capacitor
    std::vector<double> serie;

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_serie12))) {
         serie = SERIE_E12; 
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_serie24))) {
        serie = SERIE_E24; 
    }

    c = valor_comercial(c, serie);    // valor comercial 
    double fc = 1.0 / (2.0 * M_PI * r * c);
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
    resultado.err = calcular_error_fc(fc_ideal, fc);
    resultado.BW = BW;
    resultado.Q = 0; // No aplica
    resultado.G = G;
    resultado.G_dB = G_dB;
    resultado.costo = costo_total(resultado);


    return resultado;
}

datosFiltro calcular_rl(GtkWidget *entry_R, GtkWidget *entry_fc,
    GtkWidget *radio_pasa_banda, GtkWidget *radio_rechaza_banda, GtkWidget *radio_serie12,
    GtkWidget *radio_serie24, GtkWidget *entry_nombre) {

    double r = std::atof(gtk_entry_get_text(GTK_ENTRY(entry_R)));
    double fc_ideal = std::atof(gtk_entry_get_text(GTK_ENTRY(entry_fc)));
    double l = r / (2 * M_PI * fc_ideal);// Calcular inductancia 
    std::vector<double> serie;

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_serie12))) {
        serie = SERIE_E12; 
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_serie24))) {
        serie = SERIE_E24; 
    }

    l= valor_comercial(l, serie); // valor comercial
    double fc = 1.0 / (2.0 * M_PI * r * l); 


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
    resultado.err = calcular_error_fc(fc_ideal, fc);
    resultado.BW = BW;
    resultado.G = G;
    resultado.G_dB = G_dB;
    resultado.Q = 0; // no aplica 
    resultado.costo = costo_total(resultado);

    return resultado;
}

datosFiltro calcular_rlc(GtkWidget *entry_R, GtkWidget *entry_C, GtkWidget *entry_fc,
                        GtkWidget *radio_pasa_banda, GtkWidget *radio_rechaza_banda, GtkWidget *radio_serie12,
                        GtkWidget *radio_serie24, GtkWidget *entry_nombre) {

    double r = std::atof(gtk_entry_get_text(GTK_ENTRY(entry_R)));
    double c = std::atof(gtk_entry_get_text(GTK_ENTRY(entry_C)));
    double fc_ideal = std::atof(gtk_entry_get_text(GTK_ENTRY(entry_fc)));
    double l = 1.0 / (pow(2 * M_PI * fc_ideal, 2) * c);// Calcular inductancia a partir de fc y C
    std::vector<double> serie;

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_serie12))) {
        serie = SERIE_E12; 
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_serie24))) {
        serie = SERIE_E24; 
    }

    l = valor_comercial(l, serie); //valor comercial
    c = valor_comercial(c, serie); 
    double fc = 1.0 / (2.0 * M_PI * sqrt(l * c)); 

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
    resultado.err = calcular_error_fc(fc_ideal, fc);
    resultado.BW = BW;
    resultado.Q = Q;
    resultado.G = G;
    resultado.G_dB = G_dB;
    resultado.costo = costo_total(resultado);

    return resultado;
}
