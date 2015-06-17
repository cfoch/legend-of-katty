#include "lok.h"

#ifndef __LOK_HERO_H__
#define __LOK_HERO_H__

struct _LokHero {
  LokGame *game;
  int life_points;
  LokBagPack *bag_pack;
  LokBelt *belt;
  LokElement *hand;
};

LokHero * lok_hero_new (LokGame * game);
void lok_hero_free (LokHero * hero);

#endif /* __LOK_HERO_H__ */
