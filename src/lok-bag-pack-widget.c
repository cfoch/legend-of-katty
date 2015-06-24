#include "lok.h"

enum
{
  COL_NAME = 0,
  COL_TYPE,
  COL_POINTS,
  COL_WEIGHT,
  NUM_COLS
};

enum {
  RESPONSE_ID_POP = 0,
  RESPONSE_ID_USE
};

static void
_pop_tree_model (LokGameWidget * game_widget)
{
  GtkListStore *list_store;
  GtkTreeIter iter;

  list_store = GTK_LIST_STORE (game_widget->bag_pack_tree_model);

  gtk_tree_model_get_iter_first (game_widget->bag_pack_tree_model,
      &iter);
  gtk_list_store_remove (list_store, &iter);
}

void
lok_bag_pack_widget_dialog_run (GtkWidget * dialog, LokGameWidget * game_widget)
{
  gint result;
  LokHero *hero;
  gtk_widget_show_all (dialog);

  result = gtk_dialog_run (GTK_DIALOG (dialog));

  switch (result) {
    case RESPONSE_ID_POP:
      _pop_tree_model (game_widget);
      lok_bag_pack_pop_element (game_widget->game->hero->bag_pack);
      break;
    case RESPONSE_ID_USE:
      lok_hero_use_bag_pack (game_widget->game->hero);
      _pop_tree_model (game_widget);
      lok_level_delete_object (game_widget->game->current_level);
			lok_set_details_arm (game_widget);
      break;
    default:
      break;
  }
  gtk_widget_destroy (dialog);
}

static GtkTreeModel *
create_and_fill_model (LokGameWidget * game_widget)
{
  GtkListStore *list_store;
  GtkTreeIter toplevel;
  TList *l;
  LokBagPack *bag_pack;

  bag_pack = game_widget->game->hero->bag_pack;

  list_store = gtk_list_store_new (NUM_COLS,
      G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT);

  if (!bag_pack)
    return GTK_TREE_MODEL (list_store);

  for (l = bag_pack->list->start; l != NULL; l = l->next) {
    LokElement *element;

    element = LOK_ELEMENT (l->data);
    gtk_list_store_append (list_store, &toplevel);
    gtk_list_store_set (list_store, &toplevel,
        COL_TYPE, lok_element_type_to_string (lok_element_get_type (element)),
        COL_NAME, element->name,
        COL_POINTS, element->points,
        COL_WEIGHT, element->weight,
        -1);
  }

  return GTK_TREE_MODEL (list_store);
}


static GtkWidget *
create_view_and_model (LokGameWidget * game_widget)
{
  GtkTreeViewColumn *col;
  GtkCellRenderer *renderer;
  GtkWidget *view;
  GtkTreeModel *model;
  LokBagPack *bag_pack;

  bag_pack = game_widget->game->hero->bag_pack;

  view = gtk_tree_view_new ();


  /* Column 0 */
  renderer = gtk_cell_renderer_text_new ();
  col = gtk_tree_view_column_new ();
  gtk_tree_view_column_set_title (col, "Type");
  gtk_tree_view_append_column(GTK_TREE_VIEW (view), col);
  gtk_tree_view_column_pack_start (col, renderer, TRUE);
  gtk_tree_view_column_add_attribute (col, renderer, "text", COL_TYPE);

  /* Column 1 */
  renderer = gtk_cell_renderer_text_new ();
  col = gtk_tree_view_column_new ();
  gtk_tree_view_column_set_title (col, "Name");
  gtk_tree_view_append_column(GTK_TREE_VIEW (view), col);
  gtk_tree_view_column_pack_start (col, renderer, TRUE);
  gtk_tree_view_column_add_attribute (col, renderer, "text", COL_NAME);

  /* Column 2 */
  renderer = gtk_cell_renderer_text_new ();
  col = gtk_tree_view_column_new ();
  gtk_tree_view_column_set_title (col, "Points");
  gtk_tree_view_append_column(GTK_TREE_VIEW (view), col);
  gtk_tree_view_column_pack_start (col, renderer, TRUE);
  gtk_tree_view_column_add_attribute (col, renderer, "text", COL_POINTS);

  /* Column 3 */
  renderer = gtk_cell_renderer_text_new ();
  col = gtk_tree_view_column_new ();
  gtk_tree_view_column_set_title (col, "Weigth");
  gtk_tree_view_append_column(GTK_TREE_VIEW (view), col);
  gtk_tree_view_column_pack_start (col, renderer, TRUE);
  gtk_tree_view_column_add_attribute (col, renderer, "text", COL_WEIGHT);

  model = create_and_fill_model (game_widget);
  gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);
  g_object_unref (model);
  gtk_tree_selection_set_mode (gtk_tree_view_get_selection (
      GTK_TREE_VIEW (view)), GTK_SELECTION_NONE);

  return view;
}

static GtkWidget *
lok_game_heros_dialog (GtkWindow * main_app_window)
{
  GtkWidget *dialog, *heros_icon_view, *content_area;
  TArray *heros;
  LokHero *hero;
  GtkDialogFlags flags;

  flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;
  dialog = gtk_dialog_new ();
  heros = lok_hero_create_heros ();
  heros_icon_view = lok_heros_widget_new (heros, &hero);

  content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
  gtk_container_add (GTK_CONTAINER (content_area), heros_icon_view);

  return dialog;
}

GtkWidget *
lok_bag_pack_widget_new (LokGameWidget * game_widget)
{
  GtkWidget *widget;
  GtkWidget *view;
  GtkWidget *box;
  GtkWidget *button_pop, *button_use;
  GtkWidget *dialog, *content_area;
  LokBagPack *bag_pack;

  bag_pack = game_widget->game->hero->bag_pack;

  widget = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  view = create_view_and_model (game_widget);

  dialog = gtk_dialog_new ();
  content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));

  box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_pack_start (GTK_BOX (box), view, TRUE, TRUE, 1);


  button_pop = gtk_dialog_add_button (GTK_DIALOG (dialog), "POP",
      RESPONSE_ID_POP);
  button_use = gtk_dialog_add_button (GTK_DIALOG (dialog), "USE",
      RESPONSE_ID_USE);

  gtk_container_add (GTK_CONTAINER (content_area), box);

  game_widget->bag_pack_tree_model =\
      gtk_tree_view_get_model (GTK_TREE_VIEW (view));


  return dialog;
}
