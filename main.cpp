#include "data.h"
#include "controll.h"
#include "btn.h"
#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    ventana_main();
    gtk_main();
    return 0;
}
