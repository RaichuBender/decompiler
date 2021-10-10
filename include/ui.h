#ifndef __UI_H__
#define __UI_H__

#include <gtk/gtk.h>

#define UI_WINDOW_TITLE "Decompiler v0.1"

#define UI_WINDOW_SZX 640
#define UI_WINDOW_SZY 480


#define GET_WINDOW()                               \
	({                                             \
		GtkWindow *window = GTK_WINDOW(user_data); \
		window;                                    \
	})

#endif /* __UI_H__ */
