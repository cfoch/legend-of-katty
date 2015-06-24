#include "lok.h"

static LokHeroActor LOK_HERO_ACTORS[] = {
  {"ironman", "img/hero/1.png", "img/hero/actor/1.png"},
  {"helmet", "img/hero/2.png", "img/hero/actor/2.png"},
  {"spidey", "img/hero/3.png", "img/hero/actor/3.png"},
  {"hulk", "img/hero/4.png", "img/hero/actor/4.png"},
  {NULL, NULL}
};


LokHeroActor *
lok_hero_actor_new (int index)
{
  LokHeroActor *hero_actor;
  hero_actor = malloc (sizeof (LokHeroActor));
  hero_actor->name = LOK_HERO_ACTORS[index].name;
  hero_actor->profile_img_path = LOK_HERO_ACTORS[index].profile_img_path;
  hero_actor->actor_img_path = LOK_HERO_ACTORS[index].actor_img_path;

  return hero_actor;
}


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
lok_hero_set_actor (LokHero * hero, int index)
{
  hero->actor = lok_hero_actor_new (index);
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

/*
void
lok_hero_use_belt (LokHero * hero, int index)
{
  LokElement *element;
  element = lok_belt_get_element (hero->belt, index);
  if (!element)
    return;
  if (lok_element_get_type (element) == LOK_ELEMENT_TYPE_POTION) {
    lok_hero_drink_potion (hero, element);
    lok_belt_remove_element (hero->belt, index);
  } else {
    if (hero->hand == NULL) {
      lok_belt_remove_element (hero->belt, index);
      hero->hand = element;
    } else { 
      int capacity_belt;
      capacity_belt = lok_belt_get_belt_pocket (hero->belt, index)->capacity;
      if (capacity_belt >= hero->hand->weight) {
        lok_belt_remove_element (hero->belt, index);
        lok_belt_insert_element (hero->belt, hero->hand, index);
        hero->hand = element;
      }
    }
  }
}
*/

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

TArray *
lok_hero_create_heros ()
{
  TArray *heros;
  LokHero *hero;
  int i;

  heros = t_array_new ();

  for (i = 0; LOK_HERO_ACTORS[i].name != NULL; i++) {
    hero = lok_hero_new (NULL);
    lok_hero_set_actor (hero, i);
    t_array_append (heros, hero);
  }

  return heros;
}

void
lok_hero_attack (LokHero * hero, LokLevelObject * enemy_object)
{
	if (enemy_object == NULL)
		return;
	if (hero->hand != NULL)
		enemy_object->life_points = enemy_object->life_points + hero->hand->points;
}

TBoolean
lok_hero_is_alive (LokHero * hero)
{
	if (hero == NULL)
		return FALSE;
  return hero->life_points > 0;
}
