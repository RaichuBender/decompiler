#include <gtk/gtk.h>
#include <sys/stat.h>

void ui_entry(int argc, const char *argv[])
{
	GtkBuilder *builder;
	GtkWidget * window;

	gtk_init(&argc, &argv);

	builder = gtk_builder_new();
	struct stat buf;
	gtk_builder_add_from_file(builder,
							  stat("ui.glade", &buf) ? "/usr/share/decompiler/ui.glade" : "ui.glade",
							  NULL);
	
	window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
	gtk_builder_connect_signals(builder, NULL);

	g_object_unref(G_OBJECT(builder));

	gtk_widget_show(window);
	gtk_main();
}

void ui_about(GtkMenuItem *mn, GtkWindow *wn)
{
	gtk_window_present(wn);
}

void _ui_quit(GtkMenuItem *menu_quit_btn, GtkWindow *main_window);

/**********************************
*
*     @brief     
*
*
**********************************/
void _ui_quit(GtkMenuItem *menu_quit_btn, GtkWindow *main_window)
{
	// cmdline_main();
	exit(0);
}
