#include "lok.h"

#ifndef __LOK_GAME_H__
#define __LOK_GAME_H__

struct _LokGame {
	/* LokPlayer *player; */
  LokHero *hero;
  TArray *available_potions;
  TArray *available_arms;
  TArray *available_monsters;
  LokLevel *current_level;
  int max_levels;
  int count_levels;
};


#endif /* __LOK_GAME_H__ */
