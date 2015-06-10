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

LokGame * lok_game_new (void);
void lok_game_init (LokGame * game, /*LokPlayer * player, */ LokHero * hero,
    TArray * available_elements);



#endif /* __LOK_GAME_H__ */
