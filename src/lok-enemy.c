#include "lok.h"

static LokEnemy LOK_ENEMIES[] = {
  {"Dibbuk", 5, 100,"img/enemy/1.png"},
	{"Nachzehrer", 10, 200,"img/enemy/2.png"},
	{"Gugalanna", 15, 150,"img/enemy/3.png"},
	{"Ichneum", 20, 300,"img/enemy/4.png"},
	{"Strigol", 50, 450,"img/enemy/5.png"},
	{"Hombre Tigre Chira", 25, 350,"img/enemy/6.png"},
	{"Dama Blanca", 30, 200,"img/enemy/7.png"},
	{"Anne", 35, 500,"img/enemy/8.png"},
	{"Koschel", 80, 550,"img/enemy/9.png"},
	{"Beelzebul", 100, 600,"img/enemy/10.png"},
	{"Onagio", 120, 750,"img/enemy/11.png"},
	{"Blemmas", 150, 850,"img/enemy/12.png"},
	{"Ramun", 180, 850,"img/enemy/13.png"},
	{"Mago de Oz", 200, 1000,"img/enemy/14.png"},
  {NULL, 0, 0,NULL}
};


LokEnemy *
lok_enemy_new (const tchar * name, int attack_points,
			 int life_points, const tchar * img)
{
  LokEnemy *enemy;
  enemy = malloc (sizeof (LokEnemy));
  enemy->name = name;
  enemy->attack_points = attack_points;
	enemy->life_points = life_points;
	enemy->img = img;
  return enemy;
}


TArray *
lok_enemy_create_enemies ()
{
  TArray * enemies;
	LokEnemy* enemy;
	int i;

  enemies = t_array_new();

	for (i = 0; LOK_ENEMIES[i].name != NULL; i++) {
		enemy = lok_enemy_new (LOK_ENEMIES[i].name,
											LOK_ENEMIES[i].attack_points,
					 							LOK_ENEMIES[i].life_points,
																LOK_ENEMIES[i].img);
		t_array_append (enemies, enemy);
  }
	return enemies;
}

void
lok_enemy_modify_life_points (LokEnemy* enemy, int points)
{
	enemy->life_points = enemy->life_points + points;
}

void
lok_enemy_restore_life_points (LokEnemy* enemy, int level)
{
	enemy->life_points = LOK_ENEMIES[level].life_points;
}

int
lok_enemy_get_life_points (LokEnemy* enemy)
{
	return enemy->life_points;
}

int
lok_enemy_get_attack_points (LokEnemy* enemy)
{
	return enemy->attack_points;
}

void
lok_enemy_free(LokEnemy* enemy)
{
	free(enemy);
}
