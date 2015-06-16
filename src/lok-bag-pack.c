#include "lok.h"

LokBagPack *
lok_bag_pack_new (LokGame * game)
{
  LokBagPack *bag_pack;
  bag_pack = malloc (sizeof (LokBagPack));
  bag_pack->list = t_mlist_new ();
  bag_pack->game = game;
  return bag_pack;
}

LokBagPack *
lok_bag_pack_add_element (LokBagPack * bag_pack, LokElement * element)
{
  t_mlist_prepend (T_MLIST (bag_pack->list), element);
}

TBoolean
lok_bag_pack_is_empty (LokBagPack * bag_pack)
{
  return t_mlist_is_empty (T_MLIST (bag_pack->list));
}

LokElement *
lok_bag_pack_pop_element (LokBagPack * bag_pack)
{
  return t_mlist_pop (T_MLIST (bag_pack->list));
}

void
lok_bag_pack_free (LokBagPack * bag_pack)
{
  /* TODO */
  /* write me! */
}
