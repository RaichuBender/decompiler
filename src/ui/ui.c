#include "ui.h"

GtkBuilder *	builder;
GtkWidget *		main_window;
GtkButton *		about_btn;
GtkAboutDialog *about_diag;

void ui_entry(int argc, const char *argv[])
{
	gtk_init(&argc, &argv);

	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder,
							  SHARE("share/ui.glade", "/usr/share/decompiler/ui.glade"),
							  NULL);
	
	main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
	gtk_builder_connect_signals(builder, NULL);

	gtk_widget_show(main_window);
	gtk_main();
}

void ui_flush(void)
{
	g_object_unref(G_OBJECT(builder));

	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder,
							  SHARE("share/ui.glade", "/usr/share/decompiler/ui.glade"),
							  NULL);
}

void on_about_menu_activate(void)
{
	GtkWidget *diag = GTK_WIDGET(gtk_builder_get_object(builder, "about_diag"));

	gtk_builder_connect_signals(builder, NULL);
	gtk_widget_show(diag);

	about_diag = diag;
	ui_flush();
}

void on___glade_unnamed_24_button_press_event(void)
{
	gtk_widget_destroy(about_diag);
}
