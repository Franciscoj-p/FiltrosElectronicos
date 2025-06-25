#include "controll.h"
#include "data.h"
#include "btn.h"
#include "calc.h"
#include <gtk/gtk.h>

GtkWidget *win1;
GtkWidget *datos;
GtkWidget *menu;
GtkWidget *mostrar;
GtkWidget *diseñar;
GtkWidget *info;
GtkWidget *entry_nombre;
GtkWidget *entry_correo;
GtkWidget *entry_id;
GtkWidget *rc;
GtkWidget *rl;
GtkWidget *rlc;
GtkWidget *combo_tipo;
GtkWidget *entry_R;
GtkWidget *entry_C;
GtkWidget *entry_L;
GtkWidget *textview_result;
GtkWidget *radio_pasa_banda;
GtkWidget *radio_rechaza_banda;

GdkColor color_negro = {0, 0, 0, 0};
GdkColor color_blanco= {0, 0, 0, 0};

void ventana_main() {
    win1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(win1), "FILTROS ELECTRONICOS");
    gtk_window_set_default_size(GTK_WINDOW(win1), 350, 250);
    gtk_container_set_border_width(GTK_CONTAINER(win1), 15);
    g_signal_connect(G_OBJECT(win1), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_vbox_new(FALSE, 10);
    gtk_container_add(GTK_CONTAINER(win1), vbox);

    GtkWidget *label_msg = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_msg), "<span font_desc='20' weight='bold'>Bienvenido</span>");
    gtk_misc_set_alignment(GTK_MISC(label_msg), 0.5, 0.5);
    gtk_box_pack_start(GTK_BOX(vbox), label_msg, FALSE, FALSE, 10);

    GtkWidget *label_bienvenida = gtk_label_new("Bienvenido al programa de ayuda para el diseño y análisis de circuitos electrónicos");
    gtk_misc_set_alignment(GTK_MISC(label_bienvenida), 0, 0.5);
    gtk_box_pack_start(GTK_BOX(vbox), label_bienvenida, FALSE, FALSE, 0);

    GtkWidget *button = gtk_button_new_with_label("Ingresar");
    GtkWidget *label = gtk_bin_get_child(GTK_BIN(button));
    gtk_widget_modify_fg(label, GTK_STATE_NORMAL, &color_negro);
	gtk_widget_modify_fg(label, GTK_STATE_PRELIGHT, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 15);

    g_signal_connect(button, "clicked", G_CALLBACK(on_ingresar), NULL);

    gtk_widget_show_all(win1);
}

void ventana_datos() {

    datos = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(datos), "Ingreso de Datos - Ingeniero");
    gtk_window_set_default_size(GTK_WINDOW(datos), 350, 250);
    gtk_container_set_border_width(GTK_CONTAINER(datos), 15);
    g_signal_connect(datos, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_vbox_new(FALSE, 10);
    gtk_container_add(GTK_CONTAINER(datos), vbox);

    GtkWidget *label_msg = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_msg), "<span font_desc='20' weight='bold'>Ingrese sus datos</span>");
    gtk_misc_set_alignment(GTK_MISC(label_msg), 0.5, 0.5);
    gtk_box_pack_start(GTK_BOX(vbox), label_msg, FALSE, FALSE, 10);

    GtkWidget *label_id = gtk_label_new("ID Ingeniero:");
    gtk_misc_set_alignment(GTK_MISC(label_id), 0, 0.5);
    entry_id = gtk_entry_new();
    gtk_widget_modify_text(entry_id, GTK_STATE_NORMAL, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), label_id, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_id, FALSE, FALSE, 5);

    GtkWidget *label_nombre = gtk_label_new("Nombre:");
    gtk_misc_set_alignment(GTK_MISC(label_nombre), 0, 0.5);
    entry_nombre = gtk_entry_new();
	gtk_widget_modify_text(entry_nombre, GTK_STATE_NORMAL, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), label_nombre, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_nombre, FALSE, FALSE, 5);
	
    GtkWidget *label_correo = gtk_label_new("Correo:");
    gtk_misc_set_alignment(GTK_MISC(label_correo), 0, 0.5);
    entry_correo = gtk_entry_new();
	gtk_widget_modify_text(entry_correo, GTK_STATE_NORMAL, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), label_correo, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_correo, FALSE, FALSE, 5);

    GtkWidget *button = gtk_button_new_with_label("Aceptar");
    GtkWidget *label_btn = gtk_bin_get_child(GTK_BIN(button));
    gtk_widget_modify_fg(label_btn, GTK_STATE_NORMAL, &color_negro);
    gtk_widget_modify_fg(label_btn, GTK_STATE_PRELIGHT, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 15);

    g_signal_connect(button, "clicked", G_CALLBACK(on_aceptar), NULL);

    gtk_widget_show_all(datos);
}

void ventana_menu(){
    
    menu = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(menu), "Menú Principal");
    gtk_window_set_default_size(GTK_WINDOW(menu), 400, 400);
    gtk_container_set_border_width(GTK_CONTAINER(menu), 15);
    g_signal_connect(G_OBJECT(menu), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_vbox_new(FALSE, 10);
    gtk_container_add(GTK_CONTAINER(menu), vbox);

    GtkWidget *label_msg = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_msg), "<span font_desc='18' weight='bold'>Menú Principal</span>");
    gtk_misc_set_alignment(GTK_MISC(label_msg), 0.5, 0.5);
    gtk_box_pack_start(GTK_BOX(vbox), label_msg, FALSE, FALSE, 10);

    const char* opciones[] = {    //arreglo labels
        "1. Crear nuevo diseño de filtro",
        "2. Mostrar diseños",
        "3. Mostrar info del programa",
        "4. Salir"
    };

    GCallback funciones[] = {  //arreglo enlace a funciones
        G_CALLBACK(on_crear_nuevo),
        G_CALLBACK(on_ver_registrados),
        G_CALLBACK(on_mostrar_info),
        G_CALLBACK(on_salir)
    };

    for (int i = 0; i < 4; i++) {   //bucle para crear botones
        GtkWidget *button = gtk_button_new_with_label(opciones[i]);
        GtkWidget *label = gtk_bin_get_child(GTK_BIN(button));
		GdkColor color_negro = {0, 0, 0, 0};
		gtk_widget_modify_fg(label, GTK_STATE_NORMAL, &color_negro);
		gtk_widget_modify_fg(label, GTK_STATE_PRELIGHT, &color_negro);
        gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 5);
        g_signal_connect(button, "clicked", funciones[i], NULL);
    }

    gtk_widget_show_all(menu);
}

void ventana_diseñar() {

    diseñar = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(diseñar), "Diseño de Filtro");
    gtk_window_set_default_size(GTK_WINDOW(diseñar), 350, 250);
    gtk_container_set_border_width(GTK_CONTAINER(diseñar), 15);
    g_signal_connect(diseñar, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_vbox_new(FALSE, 10);
    gtk_container_add(GTK_CONTAINER(diseñar), vbox);

    GtkWidget *label_msg = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_msg), "<span font_desc='20' weight='bold'>Seleccione tipo de filtro:</span>");
    gtk_misc_set_alignment(GTK_MISC(label_msg), 0.5, 0.5);
    gtk_box_pack_start(GTK_BOX(vbox), label_msg, FALSE, FALSE, 10);

    GtkWidget *button_rc = gtk_button_new_with_label("RC");
    GtkWidget *label_rc = gtk_bin_get_child(GTK_BIN(button_rc));
    gtk_widget_modify_fg(label_rc, GTK_STATE_NORMAL, &color_negro);
    gtk_widget_modify_fg(label_rc, GTK_STATE_PRELIGHT, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), button_rc, FALSE, FALSE, 5);
    g_signal_connect(button_rc, "clicked", G_CALLBACK(on_rc_button), NULL);

    GtkWidget *button_rl = gtk_button_new_with_label("RL");
    GtkWidget *label_rl = gtk_bin_get_child(GTK_BIN(button_rl));
    gtk_widget_modify_fg(label_rl, GTK_STATE_NORMAL, &color_negro);
    gtk_widget_modify_fg(label_rl, GTK_STATE_PRELIGHT, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), button_rl, FALSE, FALSE, 5);
    g_signal_connect(button_rl, "clicked", G_CALLBACK(on_rl_button), NULL);

    GtkWidget *button_rlc = gtk_button_new_with_label("RLC");
    GtkWidget *label_rlc = gtk_bin_get_child(GTK_BIN(button_rlc));
    gtk_widget_modify_fg(label_rlc, GTK_STATE_NORMAL, &color_negro);
    gtk_widget_modify_fg(label_rlc, GTK_STATE_PRELIGHT, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), button_rlc, FALSE, FALSE, 5);
    g_signal_connect(button_rlc, "clicked", G_CALLBACK(on_rlc_button), NULL);

    GtkWidget *button = gtk_button_new_with_label("Regresar");
    GtkWidget *label = gtk_bin_get_child(GTK_BIN(button));
    gtk_widget_modify_fg(label, GTK_STATE_NORMAL, &color_negro);
    gtk_widget_modify_fg(label, GTK_STATE_PRELIGHT, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 5);
    g_signal_connect(button, "clicked", G_CALLBACK(on_regresar), NULL);

    gtk_widget_show_all(diseñar);
}

void ventana_mostrar() {

    mostrar = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(mostrar), "Filtros Registrados");
    gtk_window_set_default_size(GTK_WINDOW(mostrar), 350, 250);
    gtk_container_set_border_width(GTK_CONTAINER(mostrar), 15);
    g_signal_connect(mostrar, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_vbox_new(FALSE, 10);
    gtk_container_add(GTK_CONTAINER(mostrar), vbox);

    GtkWidget *label_msg = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_msg), "<span font_desc='20' weight='bold'>Filtros Registrados</span>");
    gtk_misc_set_alignment(GTK_MISC(label_msg), 0.5, 0.5);
    gtk_box_pack_start(GTK_BOX(vbox), label_msg, FALSE, FALSE, 10);

    GtkWidget *lable_msg2 = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(lable_msg2), "<span font_desc='18' weight='bold'>...</span>");
    gtk_misc_set_alignment(GTK_MISC(lable_msg2), 0.5, 0.5);
    gtk_box_pack_start(GTK_BOX(vbox), lable_msg2, FALSE, FALSE, 10);

    const char* opciones[] = {    //arreglo labels
        "1. Editar diseño de filtro",
        "2. Buscar diseño de filtro",
        "3. Eliminar diseño de filtro",
        "4. Regresar"
    };

    GCallback funciones[] = {  //arreglo enlace a funciones
        G_CALLBACK(on_editar_filtro),
        G_CALLBACK(on_buscar_filtro),
        G_CALLBACK(on_eliminar_filtro),
        G_CALLBACK(on_regresar)
    };

    for (int i = 0; i < 4; i++) {   //bucle para crear botones
    GtkWidget *button = gtk_button_new_with_label(opciones[i]);
    GtkWidget *label = gtk_bin_get_child(GTK_BIN(button));
    gtk_widget_modify_fg(label, GTK_STATE_NORMAL, &color_negro);
    gtk_widget_modify_fg(label, GTK_STATE_PRELIGHT, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 5);
    g_signal_connect(button, "clicked", funciones[i], NULL);
    }

    gtk_widget_show_all(mostrar);
}

void ventana_info() {

    info = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(info), "Diseño de Filtro");
    gtk_window_set_default_size(GTK_WINDOW(info), 350, 250);
    gtk_container_set_border_width(GTK_CONTAINER(info), 15);
    g_signal_connect(info, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_vbox_new(FALSE, 10);
    gtk_container_add(GTK_CONTAINER(info), vbox);

    GtkWidget *label_msg = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_msg), "<span font_desc='20' weight='bold'>Proyecto hecho por:</span>");
    gtk_misc_set_alignment(GTK_MISC(label_msg), 0.5, 0.5);
    gtk_box_pack_start(GTK_BOX(vbox), label_msg, FALSE, FALSE, 10);

    GtkWidget *label_dev1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_dev1), "<span foreground='red' font_family='Serif' font_desc='16' weight='bold'>Francisco Popo</span>");
    gtk_misc_set_alignment(GTK_MISC(label_dev1), 0.5, 0.5);
    gtk_box_pack_start(GTK_BOX(vbox), label_dev1, FALSE, FALSE, 5);

    GtkWidget *label_dev2 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_dev2), "<span foreground='blue' font_family='Serif' font_desc='16' weight='bold'>Esteban Valencia</span>");
    gtk_misc_set_alignment(GTK_MISC(label_dev2), 0.5, 0.5);
    gtk_box_pack_start(GTK_BOX(vbox), label_dev2, FALSE, FALSE, 5);

    GtkWidget *label_dev3 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_dev3), "<span foreground='gray' font_family='Serif' font_desc='16' weight='bold'>Jose Piedrahita</span>");
    gtk_misc_set_alignment(GTK_MISC(label_dev3), 0.5, 0.5);
    gtk_box_pack_start(GTK_BOX(vbox), label_dev3, FALSE, FALSE, 5);


    GtkWidget *button = gtk_button_new_with_label("Regresar");
    GtkWidget *label = gtk_bin_get_child(GTK_BIN(button));
    gtk_widget_modify_fg(label, GTK_STATE_NORMAL, &color_negro);
    gtk_widget_modify_fg(label, GTK_STATE_PRELIGHT, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 5);
    g_signal_connect(button, "clicked", G_CALLBACK(on_regresar), NULL);

    gtk_widget_show_all(info);
}

void ventana_rc() {
    rc = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(rc), "Filtro RC");
    gtk_window_set_default_size(GTK_WINDOW(rc), 350, 250);
    gtk_container_set_border_width(GTK_CONTAINER(rc), 15);
    g_signal_connect(rc, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_vbox_new(FALSE, 10);
    gtk_container_add(GTK_CONTAINER(rc), vbox);

    GtkWidget *label_msg = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_msg), "<span font_desc='20' weight='bold'>Diseño Filtro RC</span>");
    gtk_misc_set_alignment(GTK_MISC(label_msg), 0.5, 0.5);
    gtk_box_pack_start(GTK_BOX(vbox), label_msg, FALSE, FALSE, 10);

    radio_pasa_banda = gtk_radio_button_new_with_label(NULL, "Pasa altas (Low-pass)");
    radio_rechaza_banda = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio_pasa_banda), "Pasa bajas (Low-pass)");
    gtk_box_pack_start(GTK_BOX(vbox), radio_pasa_banda, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), radio_rechaza_banda, FALSE, FALSE, 0);

    GtkWidget *label_R = gtk_label_new("Resistencia (Ohm):");
    gtk_misc_set_alignment(GTK_MISC(label_R), 0, 0.5);  
    entry_R = gtk_entry_new();
    gtk_widget_modify_text(entry_R, GTK_STATE_NORMAL, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), label_R, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_R, FALSE, FALSE, 5);

    GtkWidget *label_fc = gtk_label_new("Frecuencia de Corte:");
    gtk_misc_set_alignment(GTK_MISC(label_fc), 0, 0.5);
    entry_fc = gtk_entry_new();
	gtk_widget_modify_text(entry_fc, GTK_STATE_NORMAL, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), label_fc, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_fc, FALSE, FALSE, 5);

    GtkWidget *label_result = gtk_label_new("Resultados:");
    gtk_misc_set_alignment(GTK_MISC(label_result), 0, 0.5);
    textview_result = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textview_result), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textview_result), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textview_result), GTK_WRAP_WORD);
    gtk_widget_modify_text(textview_result, GTK_STATE_NORMAL, &color_negro);
    gtk_widget_set_size_request(textview_result, -1, 100);
    gtk_box_pack_start(GTK_BOX(vbox), label_result, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), textview_result, FALSE, FALSE, 5);

    GtkWidget *btn_calcular = gtk_button_new_with_label("Calcular");
    GtkWidget *label_calcular = gtk_bin_get_child(GTK_BIN(btn_calcular));
    gtk_widget_modify_fg(label_calcular, GTK_STATE_NORMAL, &color_negro);
    gtk_widget_modify_fg(label_calcular, GTK_STATE_PRELIGHT, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), btn_calcular, FALSE, FALSE, 10);
    g_signal_connect(btn_calcular, "clicked", G_CALLBACK(on_calcularRC), NULL);

    GtkWidget *btn_simular = gtk_button_new_with_label("Simular");
    GtkWidget *label_simular = gtk_bin_get_child(GTK_BIN(btn_simular));
    gtk_widget_modify_fg(label_simular, GTK_STATE_NORMAL, &color_negro);
    gtk_widget_modify_fg(label_simular, GTK_STATE_PRELIGHT, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), btn_simular, FALSE, FALSE, 10);
    g_signal_connect(btn_simular, "clicked", G_CALLBACK(on_simular), NULL);

    GtkWidget *btn_guardar = gtk_button_new_with_label("Guardar");
    GtkWidget *label_guardar = gtk_bin_get_child(GTK_BIN(btn_guardar));
    gtk_widget_modify_fg(label_guardar, GTK_STATE_NORMAL, &color_negro);
    gtk_widget_modify_fg(label_guardar, GTK_STATE_PRELIGHT, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), btn_guardar, FALSE, FALSE, 10);
    g_signal_connect(btn_guardar, "clicked", G_CALLBACK(on_guardar), NULL);

    GtkWidget *button = gtk_button_new_with_label("Regresar");
    GtkWidget *label = gtk_bin_get_child(GTK_BIN(button));
    gtk_widget_modify_fg(label, GTK_STATE_NORMAL, &color_negro);
    gtk_widget_modify_fg(label, GTK_STATE_PRELIGHT, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 5);
    g_signal_connect(button, "clicked", G_CALLBACK(on_regresarF), NULL);

    gtk_widget_show_all(rc);
}

void ventana_rl() {
    rl = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(rl), "Filtro RL");
    gtk_window_set_default_size(GTK_WINDOW(rl), 350, 250);
    gtk_container_set_border_width(GTK_CONTAINER(rl), 15);
    g_signal_connect(rl, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_vbox_new(FALSE, 10);
    gtk_container_add(GTK_CONTAINER(rl), vbox);

    GtkWidget *label_msg = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_msg), "<span font_desc='20' weight='bold'>Diseño Filtro RL</span>");
    gtk_misc_set_alignment(GTK_MISC(label_msg), 0.5, 0.5);
    gtk_box_pack_start(GTK_BOX(vbox), label_msg, FALSE, FALSE, 10);

    radio_pasa_banda = gtk_radio_button_new_with_label(NULL, "Pasa altas (Low-pass)");
    radio_rechaza_banda = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio_pasa_banda), "Pasa bajas (Low-pass)");
    gtk_box_pack_start(GTK_BOX(vbox), radio_pasa_banda, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), radio_rechaza_banda, FALSE, FALSE, 0);

    GtkWidget *label_R = gtk_label_new("Resistencia (Ohm):");
    gtk_misc_set_alignment(GTK_MISC(label_R), 0, 0.5);  
    entry_R = gtk_entry_new();
    gtk_widget_modify_text(entry_R, GTK_STATE_NORMAL, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), label_R, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_R, FALSE, FALSE, 5);

    GtkWidget *label_fc = gtk_label_new("Frecuencia de Corte:");
    gtk_misc_set_alignment(GTK_MISC(label_fc), 0, 0.5);
    entry_fc = gtk_entry_new();
	gtk_widget_modify_text(entry_fc, GTK_STATE_NORMAL, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), label_fc, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_fc, FALSE, FALSE, 5);

    GtkWidget *label_result = gtk_label_new("Resultados:");
    gtk_misc_set_alignment(GTK_MISC(label_result), 0, 0.5);
    textview_result = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textview_result), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textview_result), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textview_result), GTK_WRAP_WORD);
    gtk_widget_modify_text(textview_result, GTK_STATE_NORMAL, &color_negro);
    gtk_widget_set_size_request(textview_result, -1, 100);
    gtk_box_pack_start(GTK_BOX(vbox), label_result, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), textview_result, FALSE, FALSE, 5);

    GtkWidget *btn_calcular = gtk_button_new_with_label("Calcular");
    GtkWidget *label_calcular = gtk_bin_get_child(GTK_BIN(btn_calcular));
    gtk_widget_modify_fg(label_calcular, GTK_STATE_NORMAL, &color_negro);
    gtk_widget_modify_fg(label_calcular, GTK_STATE_PRELIGHT, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), btn_calcular, FALSE, FALSE, 10);
    g_signal_connect(btn_calcular, "clicked", G_CALLBACK(on_calcularRL), NULL);

    GtkWidget *btn_simular = gtk_button_new_with_label("Simular");
    GtkWidget *label_simular = gtk_bin_get_child(GTK_BIN(btn_simular));
    gtk_widget_modify_fg(label_simular, GTK_STATE_NORMAL, &color_negro);
    gtk_widget_modify_fg(label_simular, GTK_STATE_PRELIGHT, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), btn_simular, FALSE, FALSE, 10);
    g_signal_connect(btn_simular, "clicked", G_CALLBACK(on_simular), NULL);

    GtkWidget *btn_guardar = gtk_button_new_with_label("Guardar");
    GtkWidget *label_guardar = gtk_bin_get_child(GTK_BIN(btn_guardar));
    gtk_widget_modify_fg(label_guardar, GTK_STATE_NORMAL, &color_negro);
    gtk_widget_modify_fg(label_guardar, GTK_STATE_PRELIGHT, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), btn_guardar, FALSE, FALSE, 10);
    g_signal_connect(btn_guardar, "clicked", G_CALLBACK(on_guardar), NULL);

    GtkWidget *button = gtk_button_new_with_label("Regresar");
    GtkWidget *label = gtk_bin_get_child(GTK_BIN(button));
    gtk_widget_modify_fg(label, GTK_STATE_NORMAL, &color_negro);
    gtk_widget_modify_fg(label, GTK_STATE_PRELIGHT, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 5);
    g_signal_connect(button, "clicked", G_CALLBACK(on_regresarF), NULL);

    gtk_widget_show_all(rl);
}

void ventana_rlc() {
    rlc = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(rlc), "Filtro RLC");
    gtk_window_set_default_size(GTK_WINDOW(rlc), 350, 250);
    gtk_container_set_border_width(GTK_CONTAINER(rlc), 15);
    g_signal_connect(rlc, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_vbox_new(FALSE, 10);
    gtk_container_add(GTK_CONTAINER(rlc), vbox);

    GtkWidget *label_msg = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_msg), "<span font_desc='20' weight='bold'>Diseño Filtro RLC</span>");
    gtk_misc_set_alignment(GTK_MISC(label_msg), 0.5, 0.5);
    gtk_box_pack_start(GTK_BOX(vbox), label_msg, FALSE, FALSE, 10);

    radio_pasa_banda = gtk_radio_button_new_with_label(NULL, "Pasa banda (Band-pass)");
    radio_rechaza_banda = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio_pasa_banda), "Rechaza banda (Notch)");
    gtk_box_pack_start(GTK_BOX(vbox), radio_pasa_banda, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), radio_rechaza_banda, FALSE, FALSE, 0);

    GtkWidget *label_R = gtk_label_new("Resistencia (Ohm):");
    gtk_misc_set_alignment(GTK_MISC(label_R), 0, 0.5);  
    entry_R = gtk_entry_new();
    gtk_widget_modify_text(entry_R, GTK_STATE_NORMAL, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), label_R, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_R, FALSE, FALSE, 5);

    GtkWidget *label_C = gtk_label_new("Capacitancia (F):");
    gtk_misc_set_alignment(GTK_MISC(label_C), 0, 0.5);
    entry_C = gtk_entry_new();
	gtk_widget_modify_text(entry_C, GTK_STATE_NORMAL, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), label_C, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_C, FALSE, FALSE, 5);

    GtkWidget *label_fc = gtk_label_new("Frecuencia de Corte:");
    gtk_misc_set_alignment(GTK_MISC(label_fc), 0, 0.5);
    entry_fc = gtk_entry_new();
	gtk_widget_modify_text(entry_fc, GTK_STATE_NORMAL, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), label_fc, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_fc, FALSE, FALSE, 5);

    GtkWidget *label_result = gtk_label_new("Resultados:");
    gtk_misc_set_alignment(GTK_MISC(label_result), 0, 0.5);
    textview_result = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textview_result), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textview_result), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textview_result), GTK_WRAP_WORD);
    gtk_widget_modify_text(textview_result, GTK_STATE_NORMAL, &color_negro);
    gtk_widget_set_size_request(textview_result, -1, 100);
    gtk_box_pack_start(GTK_BOX(vbox), label_result, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), textview_result, FALSE, FALSE, 5);

    GtkWidget *btn_calcular = gtk_button_new_with_label("Calcular");
    GtkWidget *label_calcular = gtk_bin_get_child(GTK_BIN(btn_calcular));
    gtk_widget_modify_fg(label_calcular, GTK_STATE_NORMAL, &color_negro);
    gtk_widget_modify_fg(label_calcular, GTK_STATE_PRELIGHT, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), btn_calcular, FALSE, FALSE, 10);
    g_signal_connect(btn_calcular, "clicked", G_CALLBACK(on_calcularRLC), NULL);

    GtkWidget *btn_simular = gtk_button_new_with_label("Simular");
    GtkWidget *label_simular = gtk_bin_get_child(GTK_BIN(btn_simular));
    gtk_widget_modify_fg(label_simular, GTK_STATE_NORMAL, &color_negro);
    gtk_widget_modify_fg(label_simular, GTK_STATE_PRELIGHT, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), btn_simular, FALSE, FALSE, 10);
    g_signal_connect(btn_simular, "clicked", G_CALLBACK(on_simular), NULL);

    GtkWidget *btn_guardar = gtk_button_new_with_label("Guardar");
    GtkWidget *label_guardar = gtk_bin_get_child(GTK_BIN(btn_guardar));
    gtk_widget_modify_fg(label_guardar, GTK_STATE_NORMAL, &color_negro);
    gtk_widget_modify_fg(label_guardar, GTK_STATE_PRELIGHT, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), btn_guardar, FALSE, FALSE, 10);
    g_signal_connect(btn_guardar, "clicked", G_CALLBACK(on_guardar), NULL);

    GtkWidget *button = gtk_button_new_with_label("Regresar");
    GtkWidget *label = gtk_bin_get_child(GTK_BIN(button));
    gtk_widget_modify_fg(label, GTK_STATE_NORMAL, &color_negro);
    gtk_widget_modify_fg(label, GTK_STATE_PRELIGHT, &color_negro);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 5);
    g_signal_connect(button, "clicked", G_CALLBACK(on_regresarF), NULL);

    gtk_widget_show_all(rlc);
}