#include <gtk/gtk.h>

// Ventanas globales
extern GtkWidget *win1;
extern GtkWidget *datos;
extern GtkWidget *menu;
extern GtkWidget *mostrar;
extern GtkWidget *diseñar;
extern GtkWidget *info;
extern GtkWidget *rc;
extern GtkWidget *rl;
extern GtkWidget *rlc;

extern GdkColor color_negro;
extern GdkColor color_blanco;

extern GtkWidget *entry_nombre;
extern GtkWidget *entry_correo;
extern GtkWidget *entry_id;
extern GtkWidget *combo_tipo;
extern GtkWidget *entry_R;
extern GtkWidget *entry_C;
extern GtkWidget *entry_L;
extern GtkWidget *entry_result;

void ventana_main();
void ventana_datos();
void ventana_menu();
void ventana_mostrar();
void ventana_diseñar();
void ventana_info();
void ventana_rc();
void ventana_rl();
void ventana_rlc();