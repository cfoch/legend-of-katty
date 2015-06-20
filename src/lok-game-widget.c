#include "lok.h"

static GtkWidget *
lok_game_screen_widget (LokGame * game)
{
  GtkWidget *screen;
  ClutterActor *stage;
  gint height, width;

  width = 600;
  height = 600;

  screen = gtk_clutter_embed_new ();
  gtk_widget_set_size_request (screen, height, width);

  stage = gtk_clutter_embed_get_stage (GTK_CLUTTER_EMBED (screen));
  lok_game_stage_init (stage, game);

  return screen;
}

static GtkWidget *
lok_game_panel_widget (LokGame * game)
{
  GtkWidget *box;
  GtkWidget *player_name, *hero_avatar, *hero_name, *life, *details;
  GtkWidget *details_life_label, *details_level_label;
  GtkWidget *details_life_info, *details_level_info;
  gint height, width;

  width = 600;
  height = 160;

  box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);

  player_name = gtk_label_new (NULL);
  gtk_label_set_markup (GTK_LABEL (player_name),
      "<span font_weight=\"bold\" font_size=\"x-large\">TODO</span>"); 
  hero_avatar = gtk_image_new_from_file (game->hero->actor->img_path);
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

  return box;
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

GtkWidget *
lok_game_widget_new (GtkApplication * app)
{
  GtkWidget *main_window;
  GtkWidget *heros_dialog;
  LokHero *hero;

  main_window = gtk_application_window_new (app);
  heros_dialog = lok_game_heros_dialog (GTK_WINDOW (main_window));
  hero = lok_game_heros_dialog_run (heros_dialog);

  if (hero) {
    GtkWidget *box;
    GtkWidget *panel, *screen;
    LokGame *game;

    box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);

    game = lok_game_new ();
    lok_game_init (game);
    lok_game_set_hero (game, hero);

    panel = lok_game_panel_widget (game);
    screen = lok_game_screen_widget (game);

    gtk_box_pack_start (GTK_BOX (box), panel, TRUE, TRUE, 1);
    gtk_box_pack_start (GTK_BOX (box), screen, TRUE, TRUE, 1);

    gtk_container_add (GTK_CONTAINER (main_window), box);
  }

  return main_window;
}
