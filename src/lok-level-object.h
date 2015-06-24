#include "lok.h"

#ifndef __LOK_LEVEL_OBJECT_H__
#define __LOK_LEVEL_OBJECT_H__

typedef enum {
  LOK_LEVEL_OBJECT_TYPE_HERO,
  LOK_LEVEL_OBJECT_TYPE_ELEMENT,
  LOK_LEVEL_OBJECT_TYPE_ENEMY
} LokLevelObjectType;

struct _LokLevelObject {
  LokLevelObjectType type;
  tpointer data;
  int life_points;
};

LokLevelObject * lok_level_object_new (tpointer data, LokLevelObjectType type);
LokEnemy * lok_level_object_get_enemy (LokLevelObject * object);
LokElement * lok_level_object_get_element (LokLevelObject * object);
TBoolean lok_level_object_is_enemy (LokLevelObject * object);
TBoolean lok_level_object_is_element (LokLevelObject * object);
void lok_level_object_free (LokLevelObject * object);
TBoolean lok_level_object_enemy_is_alive (LokLevelObject * object);

#endif /* __LOK_LEVEL_OBJECT_H__ */
