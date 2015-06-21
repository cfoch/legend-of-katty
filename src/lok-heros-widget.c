#include "lok.h"

enum
{
  COL_HERO_IMG = 0,
  COL_HERO_NAME,
  COL_HERO_REFERENCE,
  NUM_COLS
};

#define MAX_COLS 3

static GtkTreeModel *
lok_heros_list_store (TArray * heros)
{
  GtkListStore *list_store;
  GtkTreeIter iter;
  LokHero *hero;
  int i;

  list_store =  gtk_list_store_new (NUM_COLS, GDK_TYPE_PIXBUF, G_TYPE_STRING,
      G_TYPE_POINTER);

  for (i = 0; i < t_array_length (heros); i++) {
    GdkPixbuf *pixbuf;
    GError *error = NULL;

    hero = LOK_HERO (t_array_index (heros, i));

    pixbuf = gdk_pixbuf_new_from_file (hero->actor->profile_img_path, &error);
    gtk_list_store_append (list_store, &iter);
    g_print ("actor: %s\n", hero->actor->profile_img_path);
    gtk_list_store_set (list_store, &iter, COL_HERO_IMG, pixbuf,
      COL_HERO_NAME, hero->actor->name, COL_HERO_REFERENCE, hero, -1);
  }

  return GTK_TREE_MODEL (list_store);
}

/*
 * lok_heros_widget_new
 * Renders an icon view showing up all the available heros to select. After
 * selecting one, hero argument is set to the one which was chosen.
 */
GtkWidget *
lok_heros_widget_new (TArray * heros, LokHero ** hero)
{
  GtkWidget *widget;
  GtkTreeModel *model;

  model = lok_heros_list_store (heros);
  widget = gtk_icon_view_new_with_model (model);

  gtk_icon_view_set_text_column (GTK_ICON_VIEW (widget), COL_HERO_NAME);
  gtk_icon_view_set_pixbuf_column (GTK_ICON_VIEW (widget), COL_HERO_IMG);
  gtk_icon_view_set_item_width (GTK_ICON_VIEW (widget), 128);
  gtk_icon_view_set_columns (GTK_ICON_VIEW (widget), MAX_COLS);

  return widget;  
}
