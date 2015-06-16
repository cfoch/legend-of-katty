#include "lok.h"

LokEnemy *
lok_enemy_new (const tchar * name, int attack_points)
{
  LokEnemy *enemy;
  enemy = malloc (sizeof (LokEnemy));
  enemy->name = name;
  enemy->attack_points = attack_points;
  return enemy;
}

/*
TArray *
lok_enemy_create_monsters ()
{
  TArray *array;
  array = t_array_new
}
*/
