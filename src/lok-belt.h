#include "lok.h"

#ifndef __LOK_BELT_H__
#define __LOK_BELT_H__

struct _LokBelt {
  LokGame *game;
  TArray *array;
};

struct _LokBeltPocket {
  LokGame *game;
  int capacity;
  LokElement *element;
};

LokBeltPocket * lok_belt_pocket_new ();
void lok_belt_pocket_set_capacity (LokBeltPocket * pocket, int capacity);
void lok_belt_pocket_set_element (LokBeltPocket * pocket, LokElement * element);

void lok_belt_pocket_free (LokBeltPocket * pocket);
LokBelt * lok_belt_new (LokGame * game);
void lok_belt_insert_element (LokBelt * belt, int index, LokElement * element);
void lok_belt_free (LokBelt * belt);

#endif /* __LOK_BELT__ */
