#include "lok.h"

LokGame *
lok_game_new ()
{
  LokGame *game;
  game = malloc (sizeof (LokGame));
  return game;
}

void
lok_game_init (LokGame * game, /*LokPlayer * player, */ LokHero * hero,
    TArray * available_elements)
{
  /* game->player = player; */
  game->hero = hero;

  game->available_potions =\
      lok_element_create_elements (LOK_ELEMENT_TYPE_POTION);
  game->available_arms = lok_element_create_elements (LOK_ELEMENT_TYPE_ARM);
  /* game->available_mosters = lok_moster_create_monsters (); */
  game->current_level = lok_level_new (game);
  lok_level_init_random (game->current_level);

  game->max_levels = t_random_int (2, LOK_MAX_LEVELS_NUMBER);
  game->count_levels = 1;
}
