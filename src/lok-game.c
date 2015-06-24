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
	game->available_monsters = lok_enemy_create_enemies();

  /*  lok_level_set_matrix_random(game->current_level, &a, &b); */

  game->max_levels = LOK_MAX_LEVELS_NUMBER;
  game->count_levels = 1;
	game->difficulty = 1;
	lok_level_init_test (game->current_level);
}


void
lok_game_set_hero (LokGame * game, LokHero * hero)
{
	LokElement* arm;
	LokElement* potion;
  game->hero = hero;
	arm = t_array_index (game->available_arms, 0);
	potion = t_array_index (game->available_potions, 0);
	game->hero->hand = LOK_ELEMENT (arm);
	lok_bag_pack_add_element (game->hero->bag_pack, LOK_ELEMENT (potion));
}

void
lok_game_set_new_level (LokGame * game)
{
	/*Ignore this variables, just for fun*/
	/*TODO: Hay que arreglar esto*/
	int a = 0;
	int b = 0;

	lok_level_set_matrix_random (game->current_level, &a, &b);
}
