#include <gtk/gtk.h>
#include <string>
#include <iostream>

struct datosFiltro {
    std::string nombre;  // nombre ingeniero
    std::string id; // id ingeniero
    std::string tipo_filtro;  // "RC", "RL", "RLC"
    std::string configuracion; // "Low-pass", "High-pass"
    double r, l, c;  // Si no aplica 0
    double fc;       // Frecuencia de corte
    double G;        // Ganancia
    double G_dB;     // Ganancia en decibelios
    double BW;       // Ancho de banda
    double Q;        // Factor de calidad 
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