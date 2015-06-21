#include "lok.h"

#ifndef __LOK_LEVEL_H__
#define __LOK_LEVEL_H__

struct _LokLevel {
  TMatrix *matrix;
  LokGame *game;
  int hero_xpos;
  int hero_ypos;
};

LokLevel * lok_level_new ();
void lok_level_init_random (LokLevel * level);
void lok_level_init_test (LokLevel * level);
void lok_level_move_hero (LokLevel * level, LokDirection direction);
LokLevelObject * lok_level_get_level_object (LokLevel * level);

#endif /* __LOK_LEVEL_H__ */
