#ifndef __LOK_GAME_WIDGET_H__
#define __LOK_GAME_WIDGET_H__

#include <glib-object.h>
#include "lok.h"
/*
 * Potentially, include other headers on which this header depends.
 */

/*
 * Type macros.
 */
#define LOK_TYPE_GAME_WIDGET                  (lok_game_widget_get_type ())
#define LOK_GAME_WIDGET(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), LOK_TYPE_GAME_WIDGET, LokGameWidget))
#define LOK_IS_GAME_WIDGET(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), LOK_TYPE_GAME_WIDGET))
#define LOK_GAME_WIDGET_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), LOK_TYPE_GAME_WIDGET, LokGameWidgetClass))
#define LOK_IS_GAME_WIDGET_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), LOK_TYPE_GAME_WIDGET))
#define LOK_GAME_WIDGET_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), LOK_TYPE_GAME_WIDGET, LokGameWidgetClass))

typedef struct _LokGameWidget        LokGameWidget;
typedef struct _LokGameWidgetPrivate LokGameWidgetPrivate;
typedef struct _LokGameWidgetClass   LokGameWidgetClass;

struct _LokGameWidget
{
  /* Parent instance structure */
  GtkApplicationWindow parent;
  LokGameWidgetPrivate *priv;

  /* instance members */
  LokGame *game;
};

struct _LokGameWidgetClass
{
  /* Parent class structure */
  GtkApplicationWindowClass parent_class;

  /* class members */
  
};

/* used by LOK_TYPE_GAME_WIDGET */
GType lok_game_widget_get_type (void);

LokGameWidget * lok_game_widget_new (GtkApplication * app);
void lok_game_widget_update_element_info (LokGameWidget * game_widget);

#endif /* __LOK_GAME_WIDGET_H__ */
