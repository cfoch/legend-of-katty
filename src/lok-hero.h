#include "lok.h"

typedef LokHero struct _LokHero;

struct _LokHero {
  LokGame *game;
  int life_points;
  LokBagPack *bag_pack;
  LokBelt *belt;
};
