#include <gtk/gtk.h>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>

struct datosIngeniero {
    std::string nombre;
    std::string correo;
    std::string id;
};

struct datosFiltro {
    std::string nombre;  // nombre diseño
    std::string tipo_filtro;  // "RC", "RL", "RLC"
    std::string configuracion; // "Low-pass", "High-pass"
    double r, l, c;  // Si no aplica 0
    double fc;       // Frecuencia de corte
    double err; // Error de frecuencia de corte
    double BW;       // Ancho de banda
    double Q;        // Factor de calidad 
    double G;        // ganancia en punto de corte 
    double G_dB;        // ganancia en decibelios 
    double costo; // Costo del filtro
    datosIngeniero ingeniero ; // Datos del ingeniero
    
};

const std::vector<double> SERIE_E12 = {1.0, 1.2, 1.5, 1.8, 2.2, 2.7, 3.3, 3.9, 4.7, 5.6, 6.8, 8.2};

const std::vector<double> SERIE_E24 = {
    1.0, 1.1, 1.2, 1.3, 1.5, 1.6, 1.8, 2.0,
    2.2, 2.4, 2.7, 3.0, 3.3, 3.6, 3.9, 4.3,
    4.7, 5.1, 5.6, 6.2, 6.8, 7.5, 8.2, 9.1
};

//USD

const double COSTO_RESISTENCIA = 0.05;

const double COSTO_CAP_BAJO = 0.05;   // < 100nF
const double COSTO_CAP_MEDIO = 0.10;  // < 10uF
const double COSTO_CAP_ALTO = 0.20;   // >= 10uF

const double COSTO_IND_BAJO = 0.30;   // < 1mH
const double COSTO_IND_MEDIO = 0.75;  // < 100mH
const double COSTO_IND_ALTO = 1.50;   // >= 100mH

datosFiltro calcular_rc(GtkWidget *entry_R, GtkWidget *entry_fc,
    GtkWidget *radio_pasa_banda, GtkWidget *radio_rechaza_banda, GtkWidget *radio_serie12,
    GtkWidget *radio_serie24, GtkWidget *entry_nombre);

datosFiltro calcular_rl(GtkWidget *entry_R, GtkWidget *entry_fc,
    GtkWidget *radio_pasa_banda, GtkWidget *radio_rechaza_banda, GtkWidget *radio_serie12,
    GtkWidget *radio_serie24, GtkWidget *entry_nombre);

datosFiltro calcular_rlc(GtkWidget *entry_R, GtkWidget *entry_fc, GtkWidget *entry_C,
     GtkWidget *radio_pasa_banda, GtkWidget *radio_rechaza_banda, GtkWidget *radio_serie12,
     GtkWidget *radio_serie24, GtkWidget *entry_nombre);
    
void mostrar_resultado(GtkWidget *textview_result, datosFiltro resultado);
datosIngeniero guardarDatosIng(GtkWidget *entry_nombre, GtkWidget *entry_correo, GtkWidget *entry_id);
void guardarDiseño(datosFiltro resultado, datosIngeniero ing, std::string nombre);
extern datosIngeniero inge;
extern datosFiltro filtro;