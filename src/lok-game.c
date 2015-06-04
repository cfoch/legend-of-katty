
#define LOK_MAX_BELT_LENGTH 25
#define LOK_MAX_ELEMENT_WEIGHT 10

LokGame *
lok_game_new ()
{
  LokGame *game;
  game = malloc (sizeof (LokGame));
  return game;
}

void
lok_game_init (LokGame * game, LokPlayer * player, LokHero * hero,
    TArray * available_elements)
{
  game->player = player;
  game->hero = hero;
  game->available_potions =\
      lok_element_create_elements (LOK_ELEMENT_TYPE_POTION);
  game->available_arms = lok_element_create_elements (LOK_ELEMENT_TYPE_ARM);
  game->available_mosters = lok_moster_create_monsters ();
}
