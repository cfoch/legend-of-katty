#include "lok.h"

struct _LokGameWidgetPrivate {
  GtkWidget *heros_dialog;
  GtkWidget *game_widget;
  GtkWidget *details_level_label;
  GtkWidget *details_life_info;
  GtkWidget *element_avatar;
  GtkWidget *details_element_type_info;
  GtkWidget *details_element_name_info;
  GtkWidget *details_element_points_info;
  GtkWidget *details_element_weight_info;
};

G_DEFINE_TYPE_WITH_PRIVATE (LokGameWidget, lok_game_widget, GTK_TYPE_APPLICATION_WINDOW)

static GtkWidget *
lok_game_screen_widget (LokGameWidget * game_widget)
{
  GtkWidget *screen;
  ClutterActor *stage;
  gint height, width;

  width = 600;
  height = 600;

  screen = gtk_clutter_embed_new ();
  gtk_widget_set_size_request (screen, height, width);

  stage = gtk_clutter_embed_get_stage (GTK_CLUTTER_EMBED (screen));
  lok_game_stage_init (stage, game_widget);

  return screen;
}

static GtkWidget *
lok_game_profile_panel_widget (LokGameWidget * game_widget)
{
  GtkWidget *box;
  GtkWidget *player_name, *hero_avatar, *hero_name, *life, *details;
  GtkWidget *details_life_label, *details_level_label;
  GtkWidget *details_life_info, *details_level_info;
  GdkPixbuf *pixbuf_hero, *pixbuf_arm;
  LokGame *game;
  gint height, width;
  GError *pixbuf_err = NULL;

  width = 600;
  height = 160;

  game = game_widget->game;

  /* Creating pixbufs */
  pixbuf_hero = gdk_pixbuf_new_from_file (game->hero->actor->profile_img_path,
      &pixbuf_err);
  g_print ("pixbuf_error?:%d\n", pixbuf_err == NULL);

  /* Creating widgets */
  box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);

  player_name = gtk_label_new (NULL);
  gtk_label_set_markup (GTK_LABEL (player_name),
      "<span font_weight=\"bold\" font_size=\"x-large\">TODO</span>"); 
  hero_avatar = gtk_image_new_from_pixbuf (pixbuf_hero);
  hero_name = gtk_label_new (game->hero->actor->name);

  details = gtk_grid_new ();
  details_life_label = gtk_label_new ("Life");
  details_level_label = gtk_label_new ("Level");
  details_life_info =\
      gtk_label_new (g_strdup_printf ("%d", game->hero->life_points));
  details_level_info = gtk_label_new (g_strdup_printf ("%d / %d",
      game->count_levels, game->max_levels));

  gtk_grid_attach (GTK_GRID (details), details_life_label, 0, 0, 1, 1);
  gtk_grid_attach (GTK_GRID (details), details_life_info, 1, 0, 1, 1);
  gtk_grid_attach (GTK_GRID (details), details_level_label, 0, 1, 1, 1);
  gtk_grid_attach (GTK_GRID (details), details_level_info, 1, 1, 1, 1);
  gtk_grid_set_column_homogeneous (GTK_GRID (details), TRUE);

  gtk_box_pack_start (GTK_BOX (box), player_name, FALSE, FALSE, 15);
  gtk_box_pack_start (GTK_BOX (box), hero_avatar, FALSE, FALSE, 2);
  gtk_box_pack_start (GTK_BOX (box), hero_name, FALSE, FALSE, 10);
  gtk_box_pack_start (GTK_BOX (box), details, FALSE, FALSE, 10);

  gtk_widget_set_size_request (GTK_WIDGET (box), height, width);

  game_widget->priv->details_level_label = details_level_info;
  game_widget->priv->details_life_info = details_life_info;

  g_object_unref (G_OBJECT (pixbuf_hero));

  return box;
}

static GtkWidget *
lok_game_element_panel_widget (LokGameWidget * game_widget)
{
  GtkWidget *box;
  GtkWidget *element_label, *element_avatar, *details;
  GtkWidget *details_element_type_label, *details_element_name_label;
  GtkWidget *details_element_points_label, *details_element_weight_label;
  GtkWidget *details_element_type_info, *details_element_name_info;
  GtkWidget *details_element_points_info, *details_element_weight_info;
  LokGame *game;
  gint height, width;

  width = 600;
  height = 160;

  box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);

  element_label = gtk_label_new (NULL);
  gtk_label_set_markup (GTK_LABEL (element_label),
      "<span font_weight=\"bold\" font_size=\"x-large\">ELEMENT</span>"); 
  element_avatar = gtk_image_new ();

  details = gtk_grid_new ();

  details_element_type_label = gtk_label_new ("Type");
  details_element_name_label = gtk_label_new ("Name");
  details_element_points_label = gtk_label_new ("Points");
  details_element_weight_label = gtk_label_new ("Weight");

  details_element_type_info = gtk_label_new (NULL);
  details_element_name_info = gtk_label_new (NULL);
  details_element_points_info = gtk_label_new (NULL);
  details_element_weight_info = gtk_label_new (NULL);

  gtk_grid_attach (GTK_GRID (details), details_element_type_label,
      0, 0, 1, 1);
  gtk_grid_attach (GTK_GRID (details), details_element_name_label,
      0, 1, 1, 1);
  gtk_grid_attach (GTK_GRID (details), details_element_points_label,
      0, 2, 1, 1);
  gtk_grid_attach (GTK_GRID (details), details_element_weight_label,
      0, 3, 1, 1);

  gtk_grid_attach (GTK_GRID (details), details_element_type_info,
      1, 0, 1, 1);
  gtk_grid_attach (GTK_GRID (details), details_element_name_info,
      1, 1, 1, 1);
  gtk_grid_attach (GTK_GRID (details), details_element_points_info,
      1, 2, 1, 1);
  gtk_grid_attach (GTK_GRID (details), details_element_weight_info,
      1, 3, 1, 1);

  gtk_grid_set_column_homogeneous (GTK_GRID (details), TRUE);

  gtk_box_pack_start (GTK_BOX (box), element_label, FALSE, FALSE, 15);
  gtk_box_pack_start (GTK_BOX (box), element_avatar, FALSE, FALSE, 2);
  gtk_box_pack_start (GTK_BOX (box), details, FALSE, FALSE, 10);

  gtk_widget_set_size_request (GTK_WIDGET (box), height, width);

  /* Setting private elements. */
  game_widget->priv->element_avatar = element_avatar;

  game_widget->priv->details_element_type_info = details_element_type_info;
  game_widget->priv->details_element_name_info = details_element_name_info;
  game_widget->priv->details_element_points_info =\
      details_element_points_info;
  game_widget->priv->details_element_weight_info =\
      details_element_weight_info;

  lok_game_widget_update_element_info (game_widget);

  return box;
}

void
lok_game_widget_update_element_info (LokGameWidget * game_widget)
{
  LokLevelObject *level_object;
  gchar *type_info , *name_info, *points_info, *weight_info;
  const gchar* img_path;

  level_object = lok_level_get_level_object (game_widget->game->current_level);

  img_path = "img/default.png";

  type_info = "--------";
  name_info = "--------";
  points_info = "--------";
  weight_info = "--------";

  if (level_object) {
    g_print ("Tele_ka====: %d\n", level_object->type == LOK_LEVEL_OBJECT_TYPE_ELEMENT);
    if (lok_level_object_is_element (level_object)) {
      LokElement *element;
      LokElementType type;
      element = lok_level_object_get_element (level_object);
      type = lok_element_get_type (element);

      g_print ("Tele_ka\n");

      type_info = lok_element_type_to_string (type);
      g_print ("type_info: \n", type_info);
      name_info = g_strdup (element->name);
      points_info = g_strdup_printf ("%d", element->points);
      weight_info = g_strdup_printf ("%d", element->weight);

      img_path = element->img_path;
      g_print ("%s->%s\n", name_info, img_path);

    } else if (lok_level_object_is_enemy (level_object)) {

    }
  }

  gtk_label_set_text (
      GTK_LABEL (game_widget->priv->details_element_type_info), type_info);
  gtk_label_set_text (
      GTK_LABEL (game_widget->priv->details_element_name_info), name_info);
  gtk_label_set_text (
      GTK_LABEL (game_widget->priv->details_element_points_info), points_info);
  gtk_label_set_text (
      GTK_LABEL (game_widget->priv->details_element_weight_info), weight_info);

  gtk_image_clear (GTK_IMAGE (game_widget->priv->element_avatar));
  gtk_image_set_from_file (GTK_IMAGE (game_widget->priv->element_avatar),
      img_path);

}

static GtkWidget *
lok_game_heros_dialog (GtkWindow * main_app_window)
{
  GtkWidget *dialog, *heros_icon_view, *content_area;
  TArray *heros;
  LokHero *hero;
  GtkDialogFlags flags;

  flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;
  dialog = gtk_dialog_new_with_buttons ("Legend Of Katty",
                                        main_app_window,
                                        flags,
                                        "Select",
                                        GTK_RESPONSE_ACCEPT,
                                        "Cancel",
                                        GTK_RESPONSE_REJECT,
                                        NULL);
  heros = lok_hero_create_heros ();
  heros_icon_view = lok_heros_widget_new (heros, &hero);

  content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
  gtk_container_add (GTK_CONTAINER (content_area), heros_icon_view);

  return dialog;
}

static LokHero *
lok_game_heros_dialog_run (GtkWidget * dialog)
{
  gint result;
  LokHero *hero;
  gtk_widget_show_all (dialog);

  result = gtk_dialog_run (GTK_DIALOG (dialog));

  switch (result) {
    case GTK_RESPONSE_ACCEPT:
    {
      GtkWidget *heros_icon_view;
      GtkTreeModel *heros_model;
      GtkWidget *content_area;
      GtkTreePath *selected_path;
      GList *list;
      GtkTreeIter iter;

      content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
      list = gtk_container_get_children (GTK_CONTAINER (content_area));
      heros_icon_view = GTK_WIDGET (list->data);
      g_list_free (list);

      heros_model = gtk_icon_view_get_model (GTK_ICON_VIEW (heros_icon_view));
      list = gtk_icon_view_get_selected_items (GTK_ICON_VIEW (heros_icon_view));
      selected_path = (GtkTreePath *) (list->data);

      if (gtk_tree_model_get_iter (heros_model, &iter, selected_path))
        /* TODO: Change 2 by a variable */
        gtk_tree_model_get (heros_model, &iter, 2, &hero, -1);

      break;
    }
    default:
      break;
  }
  gtk_widget_destroy (dialog);
  return hero;
}

static void
lok_game_widget_class_init (LokGameWidgetClass *klass)
{
}

static void
lok_game_widget_init (LokGameWidget * self)
{
  self->priv = lok_game_widget_get_instance_private (self);

}

LokGameWidget *
lok_game_widget_new (GtkApplication * app)
{
  LokGameWidget *widget;
  GtkWidget *heros_dialog;
  LokHero *hero;

  widget = g_object_new (LOK_TYPE_GAME_WIDGET, "application", app, NULL);
  widget->priv->heros_dialog = lok_game_heros_dialog (GTK_WINDOW (widget));

  hero = lok_game_heros_dialog_run (widget->priv->heros_dialog);

  if (hero) {
    GtkWidget *box;
    GtkWidget *profile_panel, *element_panel, *screen;

    box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);

    widget->game = lok_game_new ();
    lok_game_init (widget->game);
    lok_game_set_hero (widget->game, hero);

    profile_panel = lok_game_profile_panel_widget (widget);
    element_panel = lok_game_element_panel_widget (widget);
    screen = lok_game_screen_widget (widget);

    gtk_box_pack_start (GTK_BOX (box), profile_panel, TRUE, TRUE, 1);
    gtk_box_pack_start (GTK_BOX (box), screen, TRUE, TRUE, 1);
    gtk_box_pack_start (GTK_BOX (box), element_panel, TRUE, TRUE, 1);

    gtk_container_add (GTK_CONTAINER (widget), box);
  }

  return widget;
}
