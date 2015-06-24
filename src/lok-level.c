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
	level->count_enemies = 0;
	level->total_enemies = 0;
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
	/*Variables para probar*/	
	lok_level_set_matrix_random  (level);
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

LokLevelTypeDecision
lok_level_random_type (int min, int max)
{
	int random_num = t_random_int(min,max);
	if (random_num < (55*max/100+min))
		return LOK_LEVEL_TYPE_NULL;
	else if (random_num < (70*max/100 + min))
		return LOK_LEVEL_TYPE_POTION;
	else if (random_num < (80*max/100 + min))
		return LOK_LEVEL_TYPE_ARM;
	else
		return LOK_LEVEL_TYPE_ENEMY;
}


void
lok_level_set_matrix_random  (LokLevel * level)
{
  /* TODO */
  /* complete */
	int i,j;
	int random_potion;
	LokLevelTypeDecision random_type;
	tpointer *data;
	LokLevelObject *object_data;
	
	for (i=0;i< LOK_LEVEL_DEFAULT_MATRIX_WIDTH; i++)
		for (j=0;j< LOK_LEVEL_DEFAULT_MATRIX_HEIGHT;j++){
			/*TODO: Get a const for the max value for the function lok_level_random_type */
			random_type = lok_level_random_type (1, 100000);
			/*The first block has to be empty*/
			if (i==0 && j==0)
				random_type = LOK_LEVEL_TYPE_NULL;
			/*Para probar sin enemigos
			if (random_type == LOK_LEVEL_TYPE_ENEMY)
				random_type = LOK_LEVEL_TYPE_NULL;
			/*End test*/
			switch (random_type){
				case LOK_LEVEL_TYPE_NULL:
					t_matrix_insert (level->matrix,NULL, i, j);
					break;
				case LOK_LEVEL_TYPE_POTION:
					/*TODO: Define a const for MAX_QUANTIY_POTION*/
					random_potion = t_random_int(1,6);
					data = t_array_index (level->game->available_potions, random_potion - 1);
					object_data = lok_level_object_new (data, LOK_LEVEL_OBJECT_TYPE_ELEMENT);
					t_matrix_insert (level->matrix, object_data, i, j);
					//printf ("POTION: %s\n", lok_level_object_get_element (object_data)->name);
					break;
				case LOK_LEVEL_TYPE_ARM:
					data = t_array_index (level->game->available_arms, level->game->count_levels - 1);
					object_data = lok_level_object_new (data, LOK_LEVEL_OBJECT_TYPE_ELEMENT);
					t_matrix_insert (level->matrix, object_data, i, j);
					//printf ("ARM: %s\n", lok_level_object_get_element (object_data)->name);
					break;
				case LOK_LEVEL_TYPE_ENEMY:
					data = t_array_index (level->game->available_monsters, level->game->count_levels - 1);
					object_data = lok_level_object_new (data, LOK_LEVEL_OBJECT_TYPE_ENEMY);
					t_matrix_insert (level->matrix,object_data, i, j);
					(level->count_enemies)++;
					break;
				default:
					break;
			}
		}
	/*Only two enemies
	data = t_array_index (level->game->available_monsters, level->game->count_levels - 1);
	object_data = lok_level_object_new (data, LOK_LEVEL_OBJECT_TYPE_ENEMY);
	t_matrix_insert (level->matrix,object_data, LOK_LEVEL_DEFAULT_MATRIX_WIDTH -1, LOK_LEVEL_DEFAULT_MATRIX_HEIGHT - 1);
	(level->count_enemies)++;
data = t_array_index (level->game->available_monsters, level->game->count_levels - 1);
	object_data = lok_level_object_new (data, LOK_LEVEL_OBJECT_TYPE_ENEMY);
	t_matrix_insert (level->matrix,object_data, LOK_LEVEL_DEFAULT_MATRIX_WIDTH -1, LOK_LEVEL_DEFAULT_MATRIX_HEIGHT - 2);
	(level->count_enemies)++;
	/*End Test of one enemy*/
	level->total_enemies = level->count_enemies;
}

void
lok_level_set_boss (LokLevel * level)
{
	tpointer data;

	data =  t_array_index (level->game->available_monsters, level->game->count_levels);
	t_matrix_insert (level->matrix, data, LOK_LEVEL_DEFAULT_MATRIX_WIDTH - 1, LOK_LEVEL_DEFAULT_MATRIX_HEIGHT - 1);
}

void
lok_level_delete_object (LokLevel * level)
{
	t_matrix_insert (level->matrix, NULL, level->hero_xpos , level->hero_ypos);
}

TBoolean
lok_level_enemies_killed (LokLevel * level)
{
	return (level->count_enemies <= 0);
}


void
lok_level_set_next_level (LokLevel * level){
	(level->game->count_levels)++;
	/*Reset level for the next level*/
	level->hero_xpos = 0;
  level->hero_ypos = 0;
	level->count_enemies = 0;
	level->total_enemies = 0;
	lok_level_set_matrix_random (level);
}

