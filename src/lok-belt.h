#ifndef __LOK_BELT_H__
#define __LOK_BELT_H__

typedef struct _LokBelt LokBelt;
typedef struct _LokBeltPocket LokBeltPocket;

struct _LokBelt {
  LokGame *game;
  TArray *array;
}

struct _LokBeltPocket {
  LokGame *game;
  int capacity;
  LokElement *element;
};

#endif /* __LOK_BELT__ */
