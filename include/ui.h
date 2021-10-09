#ifndef UI_H
#define UI_H

#include <gtk/gtk.h>
#include <sys/stat.h>

static struct stat stat_buf;
#define SHARE(_local_, _share_) stat(_local_, &stat_buf) ? _share_ : _local_

#endif /* UI_H */
