#include "lok.h"

/*
 * LokGame
 *
 * LokGame represents all the scenario with all the components available in the
 * game. These components are the hero, the level, the elements like potions or
 * arms, the number of levels, etc.
 *
 * When a LokGame is created, all the components are not already set.
 * In order to run a LokGame, we need to set all the components, otherwise there
 * will be an error.
 *
 * TODO
 * Handle the error in the case all the components of a LokGame hasn't been set.
 */

LokGame *
lok_game_new ()
{
  LokGame *game;
  game = malloc (sizeof (LokGame));
  return game;
}

void
lok_game_init (LokGame * game)
{
  /* game->player = player; */
  game->hero = NULL;

  game->available_potions =\
      lok_element_create_elements (LOK_ELEMENT_TYPE_POTION);
  game->available_arms = lok_element_create_elements (LOK_ELEMENT_TYPE_ARM);
  game->current_level = lok_level_new (game);
  /* game->available_mosters = lok_moster_create_monsters (); */

  /* lok_level_init_random (game->current_level); */
  lok_level_init_test (game->current_level);

  game->max_levels = t_random_int (2, LOK_MAX_LEVELS_NUMBER);
  game->count_levels = 1;
}


void
lok_game_set_hero (LokGame * game, LokHero * hero)
{
  game->hero = hero;
}
