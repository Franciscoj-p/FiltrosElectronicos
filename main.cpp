#include "data.h"
#include "controll.h"
#include "btn.h"
#include "calc.h"
#include <gtk/gtk.h>

//comando para compilar: g++ main.cpp controll.cpp data.cpp btn.cpp -o main `pkg-config --cflags --libs gtk+-2.0`


int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    ventana_main();
    gtk_main();
    return 0;
}
