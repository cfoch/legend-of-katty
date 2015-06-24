#include "lok.h"

enum
{
  COL_NAME = 0,
  COL_CAPACITY,
  COL_TYPE,
  COL_POINTS,
  COL_WEIGHT,
  COL_AVAILABLE,
  NUM_COLS
};

void
lok_belt_widget_dialog_run (GtkWidget * dialog, LokGameWidget * game_widget)
{
  gint result;
  LokHero *hero;
  gtk_widget_show_all (dialog);

  result = gtk_dialog_run (GTK_DIALOG (dialog));

  switch (result) {
    default:
      break;
  }
  gtk_widget_destroy (dialog);
}

static GtkTreeModel *
create_and_fill_model (LokGameWidget * game_widget)
{
  GtkTreeStore *tree_store;
  GtkTreeIter toplevel, child;
  LokBelt *belt;
  int i;

  belt = game_widget->game->hero->belt;

  tree_store = gtk_tree_store_new (NUM_COLS,
      G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT,
      G_TYPE_BOOLEAN);

  if (!belt)
    return GTK_TREE_MODEL (tree_store);

  for (i = 0; i < t_array_length (belt->array); i++) {
    LokElement *element;

    element = lok_belt_get_element (belt, i);
    gtk_tree_store_append (tree_store, &toplevel, NULL);

    if (element) {
    g_print ("AQUI\n");
      LokElementType element_type;
      element_type = lok_element_get_type (element);
      gtk_tree_store_set (tree_store, &toplevel,
          COL_CAPACITY, lok_belt_get_belt_pocket (belt, i)->capacity,
          COL_TYPE, lok_element_type_to_string (element_type),
          COL_NAME, element->name,
          COL_POINTS, element->points,
          COL_WEIGHT, element->weight,
          COL_AVAILABLE, TRUE,
          -1);
    } else
    g_print ("ACIU\n");
      gtk_tree_store_set (tree_store, &toplevel,
          COL_CAPACITY, lok_belt_get_belt_pocket (belt, i)->capacity,
          COL_TYPE, "(empty)",
          COL_NAME, "(empty)",
          COL_POINTS, 0,
          COL_WEIGHT, 0,
          COL_AVAILABLE, FALSE,
          -1);
  }

  return GTK_TREE_MODEL (tree_store);
}

static GtkWidget *
create_view_and_model (LokGameWidget * game_widget)
{
  GtkTreeViewColumn *col;
  GtkCellRenderer *renderer;
  GtkWidget *view;
  GtkTreeModel *model;

  view = gtk_tree_view_new ();

  /* Column -1 */
  renderer = gtk_cell_renderer_text_new ();
  col = gtk_tree_view_column_new ();
  gtk_tree_view_column_set_title (col, "space");
  gtk_tree_view_append_column(GTK_TREE_VIEW (view), col);
  gtk_tree_view_column_pack_start (col, renderer, TRUE);
  gtk_tree_view_column_add_attribute (col, renderer, "text", COL_CAPACITY);

  /* Column 0 */
  renderer = gtk_cell_renderer_text_new ();
  col = gtk_tree_view_column_new ();
  gtk_tree_view_column_set_title (col, "type");
  gtk_tree_view_append_column(GTK_TREE_VIEW (view), col);
  gtk_tree_view_column_pack_start (col, renderer, TRUE);
  gtk_tree_view_column_add_attribute (col, renderer, "text", COL_TYPE);

  /* Column 1 */
  renderer = gtk_cell_renderer_text_new ();
  col = gtk_tree_view_column_new ();
  gtk_tree_view_column_set_title (col, "name");
  gtk_tree_view_append_column(GTK_TREE_VIEW (view), col);
  gtk_tree_view_column_pack_start (col, renderer, TRUE);
  gtk_tree_view_column_add_attribute (col, renderer, "text", COL_NAME);

  /* Column 2 */
  renderer = gtk_cell_renderer_text_new ();
  col = gtk_tree_view_column_new ();
  gtk_tree_view_column_set_title (col, "points");
  gtk_tree_view_append_column(GTK_TREE_VIEW (view), col);
  gtk_tree_view_column_pack_start (col, renderer, TRUE);
  gtk_tree_view_column_add_attribute (col, renderer, "text", COL_POINTS);

  /* Column 3 */
  renderer = gtk_cell_renderer_text_new ();
  col = gtk_tree_view_column_new ();
  gtk_tree_view_column_set_title (col, "name");
  gtk_tree_view_append_column(GTK_TREE_VIEW (view), col);
  gtk_tree_view_column_pack_start (col, renderer, TRUE);
  gtk_tree_view_column_add_attribute (col, renderer, "text", COL_WEIGHT);
  g_print ("HOLA\n");
  model = create_and_fill_model (game_widget);
  gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);
  g_object_unref (model);
  gtk_tree_selection_set_mode (gtk_tree_view_get_selection (
      GTK_TREE_VIEW (view)), GTK_SELECTION_NONE);

  return view;
}

GtkWidget *
lok_belt_widget_new (LokGameWidget * game_widget)
{
  GtkWidget *dialog, *content_area;
  GtkWidget *view;

  dialog = gtk_dialog_new ();
  content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));

  view = create_view_and_model (game_widget);

  game_widget->belt_tree_model =\
      gtk_tree_view_get_model (GTK_TREE_VIEW (view));

  gtk_container_add (GTK_CONTAINER (content_area), view);

  return dialog;
}
