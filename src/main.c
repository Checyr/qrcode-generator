#include <stdio.h>
#include <gtk/gtk.h>
#include <wchar.h>

#include <Windows.h>

#include <cairo.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "qrcodegen.h"

static void doBasicDemo(void);
static void printQr(const uint8_t qrcode[]);

static void doBasicDemo(void) {
	const char *text = "Testing";                // User-supplied text
	enum qrcodegen_Ecc errCorLvl = qrcodegen_Ecc_LOW;  // Error correction level
	
	// Make and print the QR Code symbol
	uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
	uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
	bool ok = qrcodegen_encodeText(text, tempBuffer, qrcode, errCorLvl,
		qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
	if (ok)
		printQr(qrcode);
}

int qrcode_error_check(void){
    doBasicDemo();
    return 0;
}

static int btn_callb_edit(GtkWidget *widget, gpointer data){

    int sum = 3 + 5;
    printf("result: %d \n",sum);
    return 0;
}

static int btn_callb_delete(GtkWidget *widget, gpointer data){
    printf("remove button Pressed \n");
    return 0;
}

static void activate(GtkApplication *app, gpointer naoseioquee){
    GtkWidget *window;
    GtkWidget *btn_edit;
    GtkWidget *btn_delete;
    GtkWidget *box1;
    GtkWidget *box_outer;
    GtkCssProvider * provider;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "QRcode Generetor");
    gtk_window_set_default_size (GTK_WINDOW (window), 1200, 700); // width, height
    gtk_widget_set_name(window, "window"); 

    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "../src/css/style.css");  // No error parameter needed
    gtk_style_context_add_provider_for_display(
        gtk_widget_get_display(window),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );



    // Create an outer vertical box to center the inner box
    box_outer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_hexpand(box_outer, TRUE);
    gtk_widget_set_vexpand(box_outer, TRUE);
    gtk_widget_set_halign(box_outer, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(box_outer, GTK_ALIGN_CENTER);

    // Create an inner horizontal box to hold the buttons
    box1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_widget_set_name(box1, "box1");

    btn_edit = gtk_button_new_with_label("Edit");
    g_signal_connect(btn_edit, "clicked", G_CALLBACK(btn_callb_edit), NULL);
    gtk_widget_set_name(btn_edit, "btn_edit"); 


    btn_delete = gtk_button_new_with_label("Delete");
    g_signal_connect(btn_delete, "clicked", G_CALLBACK(btn_callb_delete), NULL);
    gtk_widget_set_name(btn_delete, "btn_delete"); 

    gtk_box_append(GTK_BOX(box_outer), box1);

    gtk_box_append(GTK_BOX(box1), btn_edit);
    gtk_box_append(GTK_BOX(box1), btn_delete);

    gtk_window_set_child(GTK_WINDOW(window), box_outer);

    gtk_window_present(GTK_WINDOW(window));

}

// Prints the given QR Code to the console.
static void printQr(const uint8_t qrcode[]) {
    SetConsoleOutputCP(CP_UTF8);
	int size = qrcodegen_getSize(qrcode);
	int border = 0;
	for (int y = -border; y < size + border; y++) {
		for (int x = -border; x < size + border; x++) {
			fputs((qrcodegen_getModule(qrcode, x, y) ? "\u2588\u2588" : "  "), stdout);
		}
		fputs("\n", stdout);
	}
	fputs("\n", stdout);
}



int main (int argc, char **argv){
    GtkApplication *app;
    int status;

    qrcode_error_check();

    app = gtk_application_new("gabrielly.gtk.qrcodegenerator", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app,"activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}