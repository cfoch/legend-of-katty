#include "lok.h"

LokLevel *
lok_level_new (LokGame * game)
{
  LokLevel* level;

  level->array = t_array_new_with_length (LOK_LEVEL_DEFAULT_LENGTH);
  level->game = game;

  return level;
}

void
lok_level_init_random (LokLevel * level)
{
  /* TODO */
  /* complete */
}
