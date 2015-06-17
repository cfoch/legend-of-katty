#include "lok.h"

LokHero *
lok_hero_new (LokGame * game)
{
  LokHero *hero;

  hero = malloc (sizeof (LokHero));
  hero->game = game;
  hero->life_points = LOK_HERO_MAX_LIFE_POINTS;
  hero->bag_pack = lok_bag_pack_new (game);
  hero->belt = lok_belt_new (game);
  hero->hand = NULL;

  return hero;
}

void
lok_hero_drop_hand (LokHero * hero)
{
  hero->hand = NULL;
}

void
lok_hero_drink_potion (LokHero * hero, LokElement * element)
{
  hero->life_points += element->points;
  if (hero->life_points > LOK_HERO_MAX_LIFE_POINTS)
    hero->life_points = LOK_HERO_MAX_LIFE_POINTS;
}

void
lok_hero_use_bag_pack (LokHero * hero)
{
  LokElement *element;
  element = lok_bag_pack_pop_element (hero->bag_pack);

  if (!element)
    return;

  if (lok_element_get_type (element) == LOK_ELEMENT_TYPE_POTION)
    lok_hero_drink_potion (hero, element);
  else {
    if (hero->hand != NULL)
      lok_bag_pack_add_element (hero->bag_pack, hero->hand);
    hero->hand = element;
  }
}

void
lok_hero_pop_bag_pack (LokHero * hero)
{
  lok_bag_pack_pop_element (hero->bag_pack);
}

void
lok_hero_use_belt (LokHero * hero, int index)
{
  LokElement *element;
  element = lok_belt_get_element (hero->belt, index);
  if (!element)
    return;
  if (lok_element_get_type (element == LOK_ELEMENT_TYPE_POTION)) {
    lok_hero_drink_potion (hero, element);
    lok_belt_remove_element (hero->belt, index);
  } else {
    if (hero->hand == NULL) {
      lok_belt_remove_element (hero->belt, index);
      hero->hand = element;
    } else { 
      int capacity_belt = lok_belt_get_belt_pocket (hero->belt,index) ->capicity;
      if (capicity_belt >= hero->hand->weight){
        lok_belt_remove_element (hero->belt, index);
        lok_belt_insert_element (hero->belt, hero->hand);
        hero->hand = element;
      }
      /*No hace nada si no puede poner el arma de la mano en el cinturon*/ 
    }
  }
}

void
lok_hero_remove_element_belt (LokHero * hero, int index)
{
  lok_belt_remove_element (hero->belt, index);
}

void
lok_hero_free (LokHero * hero)
{
  lok_bag_pack_free (hero->bag_pack);
  lok_belt_free (hero->belt);
  free (hero);
}


