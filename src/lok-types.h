#ifndef __LOK_TYPES_H__
#define __LOK_TYPES_H__

#define LOK_BAG_PACK(x)         (LokBagPack *) x
#define LOK_GAME(x)             (LokGame *) x
#define LOK_ELEMENT(x)          (LokElement *) x
#define LOK_BELT(x)             (LokBelt *) x
#define LOK_BELT_POCKET(x)      (LokBeltPocket *) x
#define LOK_ENEMY(x)            (LokEnemy *) x
#define LOK_HERO(x)             (LokHero *) x
#define LOK_LEVEL(x)            (LokLevel *) x


typedef struct _LokBagPack LokBagPack;
typedef struct _LokGame LokGame;
typedef struct _LokElement LokElement;
typedef struct _LokBelt LokBelt;
typedef struct _LokBeltPocket LokBeltPocket;
typedef struct _LokEnemy LokEnemy;
typedef struct _LokHero LokHero;
typedef struct _LokLevel LokLevel;

#endif /* __LOK_TYPES_H__ */
