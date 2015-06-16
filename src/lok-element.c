#include "lok.h"

static LokElement LOK_ELEMENT_ARMS[] = {
  {"Yasha", 5, 1},
	{"Sange", 15, 1},
	{"Desolator", 25, 2},
	{"Battle Fury", 35, 2},
	{"Manta Style", 45, 2},
	{"Lothar Edge", 55, 3},
	{"Heaven", 65, 3},
	{"Difussal Blade", 75, 3},
	{"Blade of Alarity", 85, 4},
	{"Satanic", 95, 4},
	{"Buriza", 105, 4},
	{"Abyssal Blade", 115, 5},
	{"Armlet of Mordigan", 125, 5},
	{"Divine Rapier", 145, 7},
  {NULL, 0, 0}
};

static LokElement LOK_ELEMENT_POTIONS[] = {
  {"Tango", 10, 2},
	{"Clarity", 50, 3},
	{"Healing Salve", 100, 4},
	{"Mango", 200, 5},
	{"Ironwood", 350, 6},
	{"Tranquil Potion", 500, 7},
  {NULL, 0, 0}
};

LokElement *
lok_element_new (const tchar * element_name, int points, int weight)
{
  LokElement *element;
  element = malloc (sizeof (LokElement));
  element->name = element_name;
  element->points = points;
  element->weight = weight;
  return element;
}


TArray *
lok_element_create_elements (LokElementType type)
{
  TArray *elements;
  LokElement *element;
  int i;

  elements = t_array_new ();

  switch (type) {
    case LOK_ELEMENT_TYPE_ARM:
      for (i = 0; LOK_ELEMENT_ARMS[i].name != NULL; i++) {
        element = lok_element_new (LOK_ELEMENT_ARMS[i].name,
            LOK_ELEMENT_ARMS[i].points, LOK_ELEMENT_ARMS[i].weight);
        t_array_append (elements, element);
      }
      break;
    case LOK_ELEMENT_TYPE_POTION:
      for (i = 0; LOK_ELEMENT_POTIONS[i].name != NULL; i++) {
        element = lok_element_new (LOK_ELEMENT_POTIONS[i].name,
            LOK_ELEMENT_POTIONS[i].points, LOK_ELEMENT_POTIONS[i].weight);
        t_array_append (elements, element);
      }
      break;
    default:
      break;
  }
  return elements;
}

void
lok_element_free (LokElement * element)
{
  free (element);
}

LokElementType
lok_element_get_type (LokElement * element)
{
  if (element->points > 0)
    return LOK_ELEMENT_TYPE_POTION;
  else if (element->points < 0)
    return LOK_ELEMENT_TYPE_ARM;
  else
    return LOK_ELEMENT_TYPE_MEDAL;
}

static void
_LOK_DEBUG_ELEMENT (LokElement * element)
{
  printf ("\tname: %s\n", element->name);
  printf ("\tpoints: %d\n", element->points);
  printf ("\tweight: %d\n", element->weight);
}

void
LOK_DEBUG_ELEMENT (LokElement * element)
{
  printf ("DEBUG (LokElement):\n");
  _LOK_DEBUG_ELEMENT (element);
}

void
LOK_DEBUG_ELEMENTS (TArray * elements)
{
  int i;
  printf ("DEBUG TArray:\n");
  for (i = 0; i < t_array_length (elements); i++) {
    printf ("(LokElement *)\n");
    _LOK_DEBUG_ELEMENT ((LokElement *) elements->vector[i]);
    printf ("\n");
  }
}
