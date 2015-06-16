#include "lok.h"

#ifndef __LOK_BAG_PACK_H__
#define __LOK_BAG_PACK_H__

struct _LokBagPack {
  LokGame *game;
  TMList *list;
};

LokBagPack * lok_bag_pack_new (LokGame * game);
LokBagPack * lok_bag_pack_add_element (LokBagPack * bag_pack,
    LokElement * element);
TBoolean lok_bag_pack_is_empty (LokBagPack * bag_pack);
LokElement * lok_bag_pack_pop_element (LokBagPack * bag_pack);
void lok_bag_pack_free (LokBagPack * bag_pack);

#endif /* __LOK_BAG_PACK__ */
