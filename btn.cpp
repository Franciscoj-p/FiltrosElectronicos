#include "data.h"
#include "controll.h"
#include "btn.h"
#include <gtk/gtk.h>

GtkWidget *entry_guardar;

void on_ingresar(GtkWidget *widget, gpointer data) { gtk_widget_hide(win1); ventana_datos(); }

void on_regresar(GtkWidget *widget, gpointer data) { GtkWidget *window = gtk_widget_get_toplevel(widget); gtk_widget_hide(window); ventana_menu(); }

void on_regresarF(GtkWidget *widget, gpointer data) { GtkWidget *window = gtk_widget_get_toplevel(widget); gtk_widget_hide(window); ventana_diseñar(); }

void on_rc_button(GtkWidget *widget, gpointer data) { gtk_widget_hide(diseñar); ventana_rc(); }

void on_rl_button(GtkWidget *widget, gpointer data) { gtk_widget_hide(diseñar); ventana_rl(); }

void on_rlc_button(GtkWidget *widget, gpointer data) { gtk_widget_hide(diseñar); ventana_rlc(); }

void on_crear_nuevo(GtkWidget *widget, gpointer data) { gtk_widget_hide(menu); ventana_diseñar(); }

void on_ver_registrados(GtkWidget *widget, gpointer data) { gtk_widget_hide(menu); ventana_mostrar(); } 

void on_mostrar_info(GtkWidget *widget, gpointer data) { gtk_widget_hide(menu); ventana_info(); } 

void on_salir(GtkWidget *widget, gpointer data) { gtk_main_quit(); }

void on_cancel_clicked(GtkButton *button, gpointer user_data) { GtkWidget *dialog = GTK_WIDGET(user_data); gtk_widget_destroy(dialog); }

void on_ok_clicked_elimin(GtkButton *button, gpointer user_data) {

	GtkWidget *dialog = GTK_WIDGET(user_data); 

	//hacer cosas de eliminar

	gtk_widget_destroy(dialog); 
}

void on_ok_clicked_busc(GtkButton *button, gpointer user_data) {

	GtkWidget *dialog = GTK_WIDGET(user_data); 

	//hacer cosas de buscar

	gtk_widget_destroy(dialog); 
}

void on_ok_clicked_edit(GtkButton *button, gpointer user_data) {

	GtkWidget *dialog = GTK_WIDGET(user_data); 

	//hacer cosas de editar

	gtk_widget_destroy(dialog); 
}

void on_ok_clicked_guardar(GtkButton *button, gpointer user_data) {

	GtkWidget *dialog = GTK_WIDGET(user_data); 

	//hacer cosas de guardar

	gtk_widget_destroy(dialog); 
}

void on_aceptar(GtkWidget *widget, gpointer data) { 

	guardarDatosIng(entry_nombre, entry_correo, entry_id);
    gtk_widget_hide(datos);
    ventana_menu(); 
}

void on_guardar(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog, *content_area;
    GtkWidget *label, *entry_guardar;
    GtkWidget *vbox;
    GtkWidget *window = gtk_widget_get_toplevel(widget);

    dialog = gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(dialog), "Guardar");
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    vbox = gtk_vbox_new(FALSE, 5);

    label = gtk_label_new("Nombre del diseño:");
    entry_guardar = gtk_entry_new();
    gtk_widget_modify_text(entry_guardar, GTK_STATE_NORMAL, &color_negro);

    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(content_area), vbox);

    GtkWidget *ok_button = gtk_button_new_with_label("Guardar");
	GtkWidget *ok_label = gtk_bin_get_child(GTK_BIN(ok_button));
	gtk_widget_modify_fg(ok_label, GTK_STATE_NORMAL, &color_negro);
	gtk_widget_modify_fg(ok_label, GTK_STATE_PRELIGHT, &color_negro);
	g_signal_connect(ok_button, "clicked", G_CALLBACK(on_ok_clicked_guardar), dialog);
	
    GtkWidget *cancel_button = gtk_button_new_with_label("Cancelar");
	GtkWidget *cancel_label = gtk_bin_get_child(GTK_BIN(cancel_button));
	gtk_widget_modify_fg(cancel_label, GTK_STATE_NORMAL, &color_negro);
	gtk_widget_modify_fg(cancel_label, GTK_STATE_PRELIGHT, &color_negro);
	g_signal_connect(cancel_button, "clicked", G_CALLBACK(on_cancel_clicked), dialog);

    // Añadir botones al área de acción
    GtkWidget *action_area = gtk_dialog_get_action_area(GTK_DIALOG(dialog));
    gtk_box_pack_start(GTK_BOX(action_area), ok_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(action_area), cancel_button, TRUE, TRUE, 0);

    gtk_widget_show_all(dialog);

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void on_editar_filtro(GtkWidget *widget, gpointer data) { 
	GtkWidget *dialog, *content_area;
    GtkWidget *label, *entry;
    GtkWidget *vbox;
    GtkWidget *window = gtk_widget_get_toplevel(widget);

    dialog = gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(dialog), "Busqueda");
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    vbox = gtk_vbox_new(FALSE, 5);

    label = gtk_label_new("Id del diseño a editar:");
    entry = gtk_entry_new();
    gtk_widget_modify_text(entry, GTK_STATE_NORMAL, &color_negro);

    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(content_area), vbox);

    GtkWidget *ok_button = gtk_button_new_with_label("OK");
	GtkWidget *ok_label = gtk_bin_get_child(GTK_BIN(ok_button));
	gtk_widget_modify_fg(ok_label, GTK_STATE_NORMAL, &color_negro);
	gtk_widget_modify_fg(ok_label, GTK_STATE_PRELIGHT, &color_negro);
	g_signal_connect(ok_button, "clicked", G_CALLBACK(on_ok_clicked_edit), dialog);
	
    GtkWidget *cancel_button = gtk_button_new_with_label("Cancelar");
	GtkWidget *cancel_label = gtk_bin_get_child(GTK_BIN(cancel_button));
	gtk_widget_modify_fg(cancel_label, GTK_STATE_NORMAL, &color_negro);
	gtk_widget_modify_fg(cancel_label, GTK_STATE_PRELIGHT, &color_negro);
	g_signal_connect(cancel_button, "clicked", G_CALLBACK(on_cancel_clicked), dialog);

    // Añadir botones al área de acción
    GtkWidget *action_area = gtk_dialog_get_action_area(GTK_DIALOG(dialog));
    gtk_box_pack_start(GTK_BOX(action_area), ok_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(action_area), cancel_button, TRUE, TRUE, 0);

    gtk_widget_show_all(dialog);

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void on_buscar_filtro(GtkWidget *widget, gpointer data) { 
	GtkWidget *dialog, *content_area;
    GtkWidget *label, *entry;
    GtkWidget *vbox;
    GtkWidget *window = gtk_widget_get_toplevel(widget);

    dialog = gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(dialog), "Busqueda");
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    vbox = gtk_vbox_new(FALSE, 5);

    label = gtk_label_new("Id del diseño a buscar:");
    entry = gtk_entry_new();
    gtk_widget_modify_text(entry, GTK_STATE_NORMAL, &color_negro);

    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(content_area), vbox);

    GtkWidget *ok_button = gtk_button_new_with_label("OK");
	GtkWidget *ok_label = gtk_bin_get_child(GTK_BIN(ok_button));
	gtk_widget_modify_fg(ok_label, GTK_STATE_NORMAL, &color_negro);
	gtk_widget_modify_fg(ok_label, GTK_STATE_PRELIGHT, &color_negro);
	g_signal_connect(ok_button, "clicked", G_CALLBACK(on_ok_clicked_busc), dialog);
	
    GtkWidget *cancel_button = gtk_button_new_with_label("Cancelar");
	GtkWidget *cancel_label = gtk_bin_get_child(GTK_BIN(cancel_button));
	gtk_widget_modify_fg(cancel_label, GTK_STATE_NORMAL, &color_negro);
	gtk_widget_modify_fg(cancel_label, GTK_STATE_PRELIGHT, &color_negro);
	g_signal_connect(cancel_button, "clicked", G_CALLBACK(on_cancel_clicked), dialog);

    // Añadir botones al área de acción
    GtkWidget *action_area = gtk_dialog_get_action_area(GTK_DIALOG(dialog));
    gtk_box_pack_start(GTK_BOX(action_area), ok_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(action_area), cancel_button, TRUE, TRUE, 0);

    gtk_widget_show_all(dialog);

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

}

void on_eliminar_filtro(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog, *content_area;
    GtkWidget *label, *entry;
    GtkWidget *vbox;
    GtkWidget *window = gtk_widget_get_toplevel(widget);

    dialog = gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(dialog), "Busqueda");
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    vbox = gtk_vbox_new(FALSE, 5);

    label = gtk_label_new("Id del diseño a eliminar:");
    entry = gtk_entry_new();
    gtk_widget_modify_text(entry, GTK_STATE_NORMAL, &color_negro);

    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(content_area), vbox);

    GtkWidget *ok_button = gtk_button_new_with_label("OK");
	GtkWidget *ok_label = gtk_bin_get_child(GTK_BIN(ok_button));
	gtk_widget_modify_fg(ok_label, GTK_STATE_NORMAL, &color_negro);
	gtk_widget_modify_fg(ok_label, GTK_STATE_PRELIGHT, &color_negro);
	g_signal_connect(ok_button, "clicked", G_CALLBACK(on_ok_clicked_elimin), dialog);
	
    GtkWidget *cancel_button = gtk_button_new_with_label("Cancelar");
	GtkWidget *cancel_label = gtk_bin_get_child(GTK_BIN(cancel_button));
	gtk_widget_modify_fg(cancel_label, GTK_STATE_NORMAL, &color_negro);
	gtk_widget_modify_fg(cancel_label, GTK_STATE_PRELIGHT, &color_negro);
	g_signal_connect(cancel_button, "clicked", G_CALLBACK(on_cancel_clicked), dialog);

    // Añadir botones al área de acción
    GtkWidget *action_area = gtk_dialog_get_action_area(GTK_DIALOG(dialog));
    gtk_box_pack_start(GTK_BOX(action_area), ok_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(action_area), cancel_button, TRUE, TRUE, 0);

    gtk_widget_show_all(dialog);

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
