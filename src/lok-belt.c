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
  /* FIXME */
  /* Set random length */
  TArray *array;
  int length, i;
  array = t_array_new ();
  for (i = 0; i < length; i++) {
    int capacity;
    /* FIXME */
    /* Set random capacity */
    LokBeltPocket *pocket;
    LokElement *element = NULL;
    pocket = lok_belt_pocket_new ();
    lok_belt_pocket_set_capacity (pocket, capacity);
    lok_belt_pocket_set_element (pocket, element);
    t_array_append (array, pocket);
  }
}

void
lok_belt_insert_element (LokBelt * belt, int index, LokElement * element)
{
  /* TODO */
  /* Handle the case in which index >= length */
  t_array_insert (T_ARRAY (belt), index, element);
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
