#include "lok.h"

#ifndef __LOK_ENEMY_H__
#define __LOK_ENEMY_H__

struct _LokEnemy {
  const tchar *name;
  int attack_points;  
};

LokEnemy * lok_enemy_new (const tchar * name, int attack_points);

#endif /* __LOK_ENEMY_H__ */
