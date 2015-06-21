#include "lok.h"

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

void
lok_game_stage_init (ClutterActor * stage, LokGame * game)
{
  ClutterActor *pattern, *actor;
  int i, j;

  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++) {
      pattern = lok_game_stage_pattern ();

      /* TODO: Set 75 as a number is too ugly. Define a constant! */
      clutter_actor_set_position (pattern, i * 75, j * 75);
      clutter_actor_add_child (stage, pattern);
      clutter_actor_show (pattern);
    }

  actor = lok_game_stage_create_actor_from_hero (game->hero);
  clutter_actor_set_position (actor, 0, 0);
  clutter_actor_add_child (stage, actor);
  clutter_actor_show (actor);
  

}
