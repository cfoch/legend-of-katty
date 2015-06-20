#include "lok.h"

ClutterActor *
lok_game_stage_pattern ()
{
  ClutterActor *actor;
  GError *error = NULL;
  ClutterContent *image = clutter_image_new ();

  GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file ("/home/cfoch/Documents/git/legend-of-katty/img/stage/1.png", NULL);
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
  ClutterLayoutManager *grid;
  ClutterActor *child;

  clutter_actor_set_size (stage, 300, 300);
  clutter_actor_set_background_color (stage, clutter_color_new (200, 20, 20, 0));
  //grid = lok_game_stage_arena (game);
  //child = clutter_grid_layout_get_child_at (CLUTTER_GRID_LAYOUT (grid), 0, 0);
  child = lok_game_stage_pattern ();

  clutter_actor_set_position (child, 300, 300);
  clutter_actor_set_position (child, 75, 75);
  clutter_actor_add_child (stage, child);
  clutter_actor_show (child);

}
