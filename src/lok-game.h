#ifndef __LOK_GAME_H__
#define __LOK_GAME_H__

typedef struct _LokGame LokGame;

struct _LokGame {
	LokPlayer *player;
  LokHero *hero;
  TArray *available_potions;
  TArray *available_arms;
  TArray *available_monsters;
};


#endif /* __LOK_GAME_H__ */



