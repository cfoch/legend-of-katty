#include "lok.h"

#ifndef __LOK_HERO_H__
#define __LOK_HERO_H__

struct _LokHeroActor {
  const char *name;
  const char *profile_img_path;
  const char *actor_img_path;
};

struct _LokHero {
  LokGame *game;
  int life_points;
  LokBagPack *bag_pack;
  LokBelt *belt;
  LokElement *hand;
  LokHeroActor *actor;
};

LokHero * lok_hero_new (LokGame * game);
void lok_hero_free (LokHero * hero);
void lok_game_set_hero (LokGame * game, LokHero * hero);
void lok_hero_set_actor (LokHero * hero, int index);
TArray * lok_hero_create_heros ();
void lok_hero_attack (LokHero * hero, LokLevelObject * enemy_object);
TBoolean lok_hero_is_alive (LokHero * hero);

#endif /* __LOK_HERO_H__ */
