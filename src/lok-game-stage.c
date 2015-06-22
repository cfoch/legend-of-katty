#include "lok.h"

typedef struct {
  ClutterActor *hero_actor;
  LokGameWidget *game_widget;
} LokGameStage;

ClutterActor *
lok_game_stage_pattern ()
{
  ClutterActor *actor;
  GError *error = NULL;
  ClutterContent *image = clutter_image_new ();

  GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file ("img/stage/1.png", NULL);
  clutter_image_set_data (CLUTTER_IMAGE (image),
                          gdk_pixbuf_get_pixels (pixbuf),
                          gdk_pixbuf_get_has_alpha (pixbuf)
                            ? COGL_PIXEL_FORMAT_RGBA_8888
                            : COGL_PIXEL_FORMAT_RGB_888,
                          gdk_pixbuf_get_width (pixbuf),
                          gdk_pixbuf_get_height (pixbuf),
                          gdk_pixbuf_get_rowstride (pixbuf),
                          &error);
  g_object_unref (pixbuf);

  actor = clutter_actor_new ();
  clutter_actor_set_content (actor, image);
  /* TODO: Set 75 as a number is too ugly. Define a constant! */
  clutter_actor_set_size (actor, 75, 75);
  return actor;
}


ClutterActor *
lok_game_stage_create_actor_from_hero (LokHero * hero)
{
  ClutterActor *actor;
  GError *error = NULL;
  ClutterContent *image = clutter_image_new ();

  GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file (hero->actor->actor_img_path,
      NULL);
  clutter_image_set_data (CLUTTER_IMAGE (image),
                          gdk_pixbuf_get_pixels (pixbuf),
                          gdk_pixbuf_get_has_alpha (pixbuf)
                            ? COGL_PIXEL_FORMAT_RGBA_8888
                            : COGL_PIXEL_FORMAT_RGB_888,
                          gdk_pixbuf_get_width (pixbuf),
                          gdk_pixbuf_get_height (pixbuf),
                          gdk_pixbuf_get_rowstride (pixbuf),
                          &error);
  g_object_unref (pixbuf);

  actor = clutter_actor_new ();
  clutter_actor_set_content (actor, image);
  /* TODO: Set 75 as a number is too ugly. Define a constant! */
  clutter_actor_set_size (actor, 75, 75);

  return actor;
}

ClutterLayoutManager *
lok_game_stage_arena (LokGame * game)
{
  int i, j;
  ClutterLayoutManager *grid;

  grid = clutter_grid_layout_new ();

  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++) {
      ClutterActor *pattern;
      g_print ("pattern == NULL: %d\n", pattern == NULL);
      pattern = lok_game_stage_pattern ();
      clutter_grid_layout_attach (CLUTTER_GRID_LAYOUT (grid),
          pattern, i, j, 1, 1);
    }

  return grid;
}

static void
_move (LokGameStage * game_stage, LokDirection direction)
{
  clutter_actor_save_easing_state (game_stage->hero_actor);

  lok_level_move_hero (game_stage->game_widget->game->current_level, direction);
  clutter_actor_set_position (game_stage->hero_actor,
      game_stage->game_widget->game->current_level->hero_xpos * 75,
      game_stage->game_widget->game->current_level->hero_ypos * 75);
  lok_game_widget_update_element_info (game_stage->game_widget);

  clutter_actor_restore_easing_state (game_stage->hero_actor);
}

static void
_move_down (GObject * instance, const gchar *action_name, guint key_val,
    ClutterModifierType  modifiers, LokGameStage * game_stage)
{
  _move (game_stage, LOK_DIRECTION_DOWN);
}

static void
_move_up (GObject * instance, const gchar *action_name, guint key_val,
    ClutterModifierType  modifiers, LokGameStage * game_stage)
{
  _move (game_stage, LOK_DIRECTION_UP);
}

static void
_move_left (GObject * instance, const gchar *action_name, guint key_val,
    ClutterModifierType  modifiers, LokGameStage * game_stage)
{
  _move (game_stage, LOK_DIRECTION_LEFT);
}

static void
_move_right (GObject * instance, const gchar *action_name, guint key_val,
    ClutterModifierType  modifiers, LokGameStage * game_stage)
{
  _move (game_stage, LOK_DIRECTION_RIGHT);
}

static gboolean
_key_press_cb (ClutterActor *actor,
             ClutterEvent *event,
             gpointer      user_data)
{
  ClutterBindingPool *pool;

  pool = clutter_binding_pool_find (G_OBJECT_TYPE_NAME (actor));

  return clutter_binding_pool_activate (pool,
                                        clutter_event_get_key_symbol (event),
                                        clutter_event_get_state (event),
                                        G_OBJECT (actor));
}

void
lok_game_stage_init (ClutterActor * stage, LokGameWidget * game_widget)
{
  ClutterActor *pattern, *actor;
  ClutterBindingPool *binding_pool;
  ClutterStageClass *stage_class;
  LokGameStage *game_stage;
  LokGame *game;
  int i, j;

  game = game_widget->game;

  stage_class = CLUTTER_STAGE_GET_CLASS (stage);
  binding_pool = clutter_binding_pool_get_for_class (stage_class);

  /* TODO: Wrap this loop in a function in order to reduce amount of lines */
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++) {
      pattern = lok_game_stage_pattern ();

      /* TODO: Set 75 as a number is too ugly. Define a constant! */
      clutter_actor_set_position (pattern, i * 75, j * 75);
      clutter_actor_add_child (stage, pattern);
      clutter_actor_show (pattern);
    }

  actor = lok_game_stage_create_actor_from_hero (game->hero);

  game_stage = malloc (sizeof (LokGameStage));
  game_stage->game_widget = game_widget;
  game_stage->hero_actor = actor;

  clutter_actor_set_position (actor, game->current_level->hero_xpos,
      game->current_level->hero_ypos);
  clutter_actor_add_child (stage, actor);
  clutter_actor_show (actor);

  clutter_binding_pool_install_action (binding_pool,
                                       "move-down",      /* identifier */
                                       CLUTTER_KEY_Down, /* up arrow pressed */
                                       0,              /* no modifiers pressed */
                                       G_CALLBACK (_move_down),
                                       game_stage,  /* user data passed */
                                       NULL);
  clutter_binding_pool_install_action (binding_pool,
                                       "move-up",      /* identifier */
                                       CLUTTER_KEY_Up, /* up arrow pressed */
                                       0,              /* no modifiers pressed */
                                       G_CALLBACK (_move_up),
                                       game_stage,  /* user data passed */
                                       NULL);
  clutter_binding_pool_install_action (binding_pool,
                                       "move-right",      /* identifier */
                                       CLUTTER_KEY_Right, /* up arrow pressed */
                                       0,              /* no modifiers pressed */
                                       G_CALLBACK (_move_right),
                                       game_stage,  /* user data passed */
                                       NULL);
  clutter_binding_pool_install_action (binding_pool,
                                       "move-left",      /* identifier */
                                       CLUTTER_KEY_Left, /* up arrow pressed */
                                       0,              /* no modifiers pressed */
                                       G_CALLBACK (_move_left),
                                       game_stage,  /* user data passed */
                                       NULL);

  g_signal_connect (stage,
                    "key-press-event",
                    G_CALLBACK (_key_press_cb),
                    NULL);
}
