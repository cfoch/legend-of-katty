#include "lok.h"

#ifndef __LOK_ENEMY_H__
#define __LOK_ENEMY_H__

struct _LokEnemy {
  const tchar *name;
  int attack_points;
	int life_points;
	const tchar *img;
};

LokEnemy * lok_enemy_new (const tchar * name, int attack_points,
													int life_points, const tchar * img);

TArray * lok_enemy_create_enemies ();

void lok_enemy_modify_life_points (LokEnemy* enemy, int points);

void lok_enemy_restore_life_points (LokEnemy* enemy, int level);

int lok_enemy_get_life_points (LokEnemy* enemy);

int lok_enemy_get_attack_points (LokEnemy* enemy);

void lok_enemy_free(LokEnemy* enemy);

#endif /* __LOK_ENEMY_H__ */
