#include <gtk/gtk.h>
#include <string>
#include <iostream>

struct datosIngeniero {
    std::string nombre;
    std::string correo;
    std::string id;
} 

struct datosFiltro {
    std::string nombre;  // nombre diseño
    std::string id; // id diseño
    std::string tipo_filtro;  // "RC", "RL", "RLC"
    std::string configuracion; // "Low-pass", "High-pass"
    double r, l, c;  // Si no aplica 0
    double fc;       // Frecuencia de corte
    double BW;       // Ancho de banda
    double Q;        // Factor de calidad 
    double G;        // ganancia en punto de corte 
    double G_dB;        // ganancia en decibelios 
    datosIngeniero ingeniero ; // Datos del ingeniero
    
};

datosFiltro calcular_rc(GtkWidget *entry_R, GtkWidget *entry_C,
    GtkWidget *radio_pasa_banda, GtkWidget *radio_rechaza_banda,
    GtkWidget *entry_nombre, GtkWidget *entry_id);

datosFiltro calcular_rl(GtkWidget *entry_R, GtkWidget *entry_L,
    GtkWidget *radio_pasa_banda, GtkWidget *radio_rechaza_banda,
    GtkWidget *entry_nombre, GtkWidget *entry_id);

datosFiltro calcular_rlc(GtkWidget *entry_R, GtkWidget *entry_L, GtkWidget *entry_C,
     GtkWidget *radio_pasa_banda, GtkWidget *radio_rechaza_banda,
     GtkWidget *entry_nombre, GtkWidget *entry_id);
    
void mostrar_resultado(GtkWidget *textview_result, datosFiltro resultado);
datosIngeniero guardarDatosIng(GtkWidget *entry_nombre, GtkWidget *entry_correo, GtkWidget *entry_id);