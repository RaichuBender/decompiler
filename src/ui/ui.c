#include "ui.h"

char *ui_text;

/**********************************
*
*     @brief     
*
*     @param application 
*     @param user_data 
*
**********************************/
static void
app_activate(	GApplication *application	,
				gpointer      user_data			)
{
	GtkWidget 	  * window;
	GtkWidget 	  * scroll;
	GtkWidget 	  * text_view;
	GtkTextBuffer * buffer;
	char 		  * text = malloc(4096 * 128);

	ui_text = text; disassemble();
	window = gtk_application_window_new(GTK_APPLICATION(application));
	gtk_window_set_title(GTK_WINDOW(window), UI_WINDOW_TITLE);
	gtk_window_set_default_size(GTK_WINDOW(window), UI_WINDOW_SZX, UI_WINDOW_SZY);

	scroll = gtk_scrolled_window_new();
	gtk_window_set_child(GTK_WINDOW(window), scroll);

	text_view = gtk_text_view_new();
	buffer	  = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
	gtk_text_buffer_set_text(buffer, text, -1);
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD_CHAR);

	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroll), text_view);

	gtk_widget_show(window);
}

/**********************************
*
*     @brief     
*
*     @param argc 
*     @param argv 
*     @return int 
*
**********************************/
int ui_main(	int         argc	,
				const char *argv[]		)
{
	GtkApplication *application;
	int				stat;

	application = gtk_application_new("town.raichu.bender.decompiler", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(application, "activate", G_CALLBACK(app_activate), NULL);
	stat = g_application_run(G_APPLICATION(application), argc, argv);
	g_object_unref(application);
	return stat;
}
