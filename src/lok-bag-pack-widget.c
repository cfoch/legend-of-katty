#include "lok.h"

enum
{
  COL_NAME = 0,
  COL_ATTACK_POINTS,
  COL_WEIGHT,
  NUM_COLS
};

typedef struct {
  LokBagPack *bag_pack;
  GtkTreeModel *tree_model;
} DummyType;


static void
pop_item_cb (GtkWidget * button, DummyType * dummy)
{
  LokBagPack *bag_pack;
  GtkListStore *list_store;
  GtkTreeIter iter;

  bag_pack = dummy->bag_pack;
  list_store = GTK_LIST_STORE (dummy->tree_model);

  gtk_tree_model_get_iter_first (dummy->tree_model, &iter);
  lok_bag_pack_pop_element (bag_pack);

  gtk_list_store_remove (list_store, &iter);  
}

static GtkTreeModel *
create_and_fill_model (LokBagPack * bag_pack)
{
  GtkListStore *list_store;
  GtkTreeIter toplevel;
  TList *l;

  list_store = gtk_list_store_new (NUM_COLS, G_TYPE_STRING, G_TYPE_INT,
      G_TYPE_INT);

  if (!bag_pack)
    return GTK_TREE_MODEL (list_store);

  for (l = bag_pack->list->start; l != NULL; l = l->next) {
    LokElement *element;

    element = LOK_ELEMENT (l->data);
    gtk_list_store_append (list_store, &toplevel);
    gtk_list_store_set (list_store, &toplevel, COL_NAME, element->name,
      COL_ATTACK_POINTS, element->points, COL_WEIGHT, element->weight, -1);
  }

  return GTK_TREE_MODEL (list_store);
}


static GtkWidget *
create_view_and_model (LokBagPack * bag_pack)
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
  gtk_tree_view_column_set_title (col, "points of attack");
  gtk_tree_view_append_column(GTK_TREE_VIEW (view), col);
  gtk_tree_view_column_pack_start (col, renderer, TRUE);
  gtk_tree_view_column_add_attribute (col, renderer, "text", COL_ATTACK_POINTS);

  /* Column 3 */
  renderer = gtk_cell_renderer_text_new ();
  col = gtk_tree_view_column_new ();
  gtk_tree_view_column_set_title (col, "weigth");
  gtk_tree_view_append_column(GTK_TREE_VIEW (view), col);
  gtk_tree_view_column_pack_start (col, renderer, TRUE);
  gtk_tree_view_column_add_attribute (col, renderer, "text", COL_WEIGHT);

  model = create_and_fill_model (bag_pack);
  gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);
  g_object_unref (model);
  gtk_tree_selection_set_mode (gtk_tree_view_get_selection (
      GTK_TREE_VIEW (view)), GTK_SELECTION_NONE);

  return view;
}

GtkWidget *
lok_bag_pack_widget_new (LokBagPack * bag_pack)
{
  GtkWidget *widget;
  GtkWidget *view;
  GtkWidget *box, *box_buttons;
  GtkWidget *button_pop;
  DummyType *dummy;

  widget = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  view = create_view_and_model (bag_pack);


  box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_pack_start (GTK_BOX (box), view, TRUE, TRUE, 1);

  button_pop = gtk_button_new_with_label ("POP");

  box_buttons = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start (GTK_BOX (box_buttons), button_pop, TRUE, TRUE, 0);

  gtk_box_pack_start (GTK_BOX (box), box_buttons, TRUE, TRUE, 0);
  gtk_container_add (GTK_CONTAINER (widget), box);

  dummy = malloc (sizeof (DummyType));
  dummy->bag_pack = bag_pack;
  dummy->tree_model = gtk_tree_view_get_model (GTK_TREE_VIEW (view));

  g_signal_connect (G_OBJECT (button_pop), "clicked", G_CALLBACK (pop_item_cb),
      dummy);

  g_signal_connect (G_OBJECT (widget), "destroy", gtk_main_quit, NULL);

  return widget;
}
