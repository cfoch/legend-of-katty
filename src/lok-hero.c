#include "lok.h"

LokHero *
lok_hero_new (LokGame * game)
{
  LokHero *hero;

  hero = malloc (sizeof (LokHero));
  hero->game = game;
  hero->life_points = LOK_MAX_LIFE_POINTS;
  hero->bag_pack = lok_bag_pack_new (game);
  hero->lok_belt = lok_belt_new (game);

  return hero;
}

void
lok_hero_free (LokHero * hero)
{
  lok_bag_pack_free (hero->bag_pack);
  lok_belt_free (hero->belt);
  free (hero);
}


