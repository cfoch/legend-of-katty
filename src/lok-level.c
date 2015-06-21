#include "lok.h"

#define LOK_LEVEL_DEFAULT_MATRIX_WIDTH              8
#define LOK_LEVEL_DEFAULT_MATRIX_HEIGHT             8

LokLevel *
lok_level_new (LokGame * game)
{
  LokLevel* level;

  level = malloc (sizeof (LokLevel));

  level->matrix = t_matrix_new (LOK_LEVEL_DEFAULT_MATRIX_WIDTH,
      LOK_LEVEL_DEFAULT_MATRIX_HEIGHT);
  level->game = game;
  level->hero_xpos = 0;
  level->hero_ypos = 0;

  return level;
}

LokLevelObject *
lok_level_get_level_object (LokLevel * level)
{
  LokLevelObject *object = NULL;
  object = t_matrix_get (level->matrix, level->hero_xpos, level->hero_ypos);
  return object;
}

void
lok_level_init_test (LokLevel * level)
{
  t_matrix_insert (level->matrix, level->game->hero, level->hero_xpos,
      level->hero_ypos);
  t_matrix_insert (level->matrix,
      t_array_index (level->game->available_potions, 0), 5, 0);
  t_matrix_insert (level->matrix,
      t_array_index (level->game->available_potions, 1), 4, 7);
  t_matrix_insert (level->matrix,
      t_array_index (level->game->available_potions, 1), 1, 5);
  t_matrix_insert (level->matrix,
      t_array_index (level->game->available_arms, 0), 0, 2);
  t_matrix_insert (level->matrix,
      t_array_index (level->game->available_arms, 1), 7, 1);
}

void
lok_level_move_hero (LokLevel * level, LokDirection direction)
{
  switch (direction) {
    case LOK_DIRECTION_UP:
      level->hero_ypos = (level->hero_ypos > 0) ? level->hero_ypos - 1 : 0;
      break;
    case LOK_DIRECTION_RIGHT:
      level->hero_xpos = (level->hero_xpos < LOK_LEVEL_DEFAULT_MATRIX_WIDTH - 1) ?
          level->hero_xpos + 1 : LOK_LEVEL_DEFAULT_MATRIX_WIDTH - 1;
      break;
    case LOK_DIRECTION_LEFT:
      level->hero_xpos = (level->hero_xpos > 0) ? level->hero_xpos - 1 : 0;
      break;
    case LOK_DIRECTION_DOWN:
      level->hero_ypos = (level->hero_ypos < LOK_LEVEL_DEFAULT_MATRIX_HEIGHT - 1) ?
          level->hero_ypos + 1 : LOK_LEVEL_DEFAULT_MATRIX_HEIGHT - 1;
      break;
    default:
      break;
  }
}

void
lok_level_init_random (LokLevel * level)
{
  /* TODO */
  /* complete */
}
