#include "lok.h"

enum
{
  COL_NAME = 0,
  COL_POINTS,
  COL_WEIGHT,
  NUM_COLS
};

static GtkTreeModel *
create_and_fill_model (LokBelt * belt)
{
  GtkTreeStore *tree_store;
  GtkTreeIter toplevel, child;
  int i;

  tree_store = gtk_tree_store_new (NUM_COLS, G_TYPE_STRING, G_TYPE_INT,
      G_TYPE_INT);

  if (!belt)
    return GTK_TREE_MODEL (tree_store);

  for (i = 0; i < t_array_length (belt->array); i++) {
    LokElement *element;

    element = LOK_ELEMENT (t_array_index (belt->array, i));
    gtk_tree_store_append (tree_store, &toplevel, NULL);
    gtk_tree_store_set (tree_store, &toplevel, COL_NAME, element->name,
      COL_POINTS, element->points, COL_WEIGHT, element->weight, -1);
  }

  return GTK_TREE_MODEL (tree_store);
}

static GtkWidget *
create_view_and_model (LokBelt * belt)
{
  GtkTreeViewColumn *col;
  GtkCellRenderer *renderer;
  GtkWidget *view;
  GtkTreeModel *model;

  view = gtk_tree_view_new ();

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

  model = create_and_fill_model (belt);
  gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);
  g_object_unref (model);
  gtk_tree_selection_set_mode (gtk_tree_view_get_selection (
      GTK_TREE_VIEW (view)), GTK_SELECTION_NONE);

  return view;
}

GtkWidget *
lok_belt_widget_new (LokBelt * belt)
{
  GtkWidget *widget;
  GtkWidget *view;

  widget = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  view = create_view_and_model (belt);

  gtk_container_add (GTK_CONTAINER (widget), view);

  return widget;
}
