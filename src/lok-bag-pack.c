#include "lok.h"

LokBagPack *
lok_bag_pack_new (LokGame * game)
{
  LokBagPack *bag_pack;
  bag_pack = malloc (sizeof (LokBagPack));
  bag_pack->list = NULL;
  bag_pack->game = game;
  return bag_pack;
}

LokBagPack *
log_bag_pack_add_element (LokBagPack * bag_pack, LokElement * element)
{
  t_mlist_prepend (T_MLIST (bag_pack->list), element);
}

TBoolean
lok_bag_pack_is_empty (LokBagPack * bag_pack)
{
  return t_mlist_is_empty (M_LIST (bag_pack));
}

LokElement *
lok_bag_pack_pop_element (LokBagPack * bag_pack)
{
  return t_mlist_pop (M_LIST (bag_pack));
}
