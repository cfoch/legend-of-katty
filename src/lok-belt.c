#include "lok.h"

LokBeltPocket *
lok_belt_pocket_new ()
{
  LokBeltPocket *pocket;
  pocket = malloc (sizeof (LokBeltPocket));
  pocket->capacity = 0;
  return pocket;
}

void
lok_belt_pocket_set_capacity (LokBeltPocket * pocket, int capacity)
{
  pocket->capacity = capacity;
}

void
lok_belt_pocket_set_element (LokBeltPocket * pocket, LokElement * element)
{
  pocket->element = element;
}

void
lok_belt_pocket_free (LokBeltPocket * pocket)
{
  lok_element_free (pocket->element);
  free (pocket);
}

LokBelt *
lok_belt_new (LokGame * game)
{
  LokBelt *belt;
  TArray *array;
  int length, i;

  belt = malloc (sizeof (LokBelt));
  belt->game = game;
  belt->array = t_array_new ();
  length = LOK_BELT_MAX_LENGTH;
  for (i = 0; i < length; i++) {
    int capacity;
    LokBeltPocket *pocket;

    capacity = t_random_int (LOK_BELT_POCKET_MIN_WEIGHT,
        LOK_BELT_POCKET_MAX_WEIGHT);
    pocket = lok_belt_pocket_new ();
    lok_belt_pocket_set_capacity (pocket, capacity);
    lok_belt_pocket_set_element (pocket, NULL);
    t_array_append (belt->array, pocket);
  }
  return belt;
}

LokBeltPocket *
lok_belt_get_belt_pocket (LokBelt * belt, int index)
{
  return LOK_BELT_POCKET (t_array_index (belt->array, index));
}

void
lok_belt_insert_element (LokBelt * belt, int index, LokElement * element)
{
  LokBeltPocket *belt_pocket;

  belt_pocket = lok_belt_get_belt_pocket (belt, index);
  if (belt_pocket->capacity >= element->weight)
    belt_pocket->element = element;
}

LokElement *
lok_belt_get_element (LokBelt * belt, int index)
{
  return lok_belt_get_belt_pocket (belt, index)->element;
}

void
lok_belt_remove_element (LokBelt * belt, int index)
{
  LokBeltPocket *belt_pocket;
  belt_pocket = lok_belt_get_belt_pocket (belt, index);
  belt_pocket->element = NULL;
}

void
lok_belt_free (LokBelt * belt)
{
  int i;
  for (i = 0; i < t_array_length (T_ARRAY (belt)); i++)
    lok_belt_pocket_free (t_array_index (T_ARRAY (belt), i));
  free (T_ARRAY (belt)->array);
  free (T_ARRAY (belt));
}
