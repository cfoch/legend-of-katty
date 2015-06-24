#include "lok.h"

#ifndef __LOK_LEVEL_H__
#define __LOK_LEVEL_H__

typedef enum {
	LOK_LEVEL_TYPE_NULL,
  LOK_LEVEL_TYPE_POTION,
  LOK_LEVEL_TYPE_ARM,
  LOK_LEVEL_TYPE_ENEMY
} LokLevelTypeDecision;

struct _LokLevel {
  TMatrix *matrix;
  LokGame *game;
  int hero_xpos;
  int hero_ypos;
};

LokLevel * lok_level_new (LokGame * game);
void lok_level_init_test (LokLevel * level);
void lok_level_move_hero (LokLevel * level, LokDirection direction);
LokLevelObject * lok_level_get_level_object (LokLevel * level);

LokLevelTypeDecision lok_level_random_type (int min, int max);
void lok_level_set_matrix_random (LokLevel * level,int* quantity_enemy, int* quantity_element);
void lok_level_set_boss (LokLevel * level);
void lok_level_delete_object (LokLevel * level, int xpos, int ypos);


#endif /* __LOK_LEVEL_H__ */
