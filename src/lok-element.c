#include "lok.h"

static LokElement LOK_ELEMENT_ARMS[] = {
  {"Yasha", -5, 1, "img/element/arm/1.png"},
	{"Sange", -15, 1, "img/element/arm/2.png"},
	{"Desolator", -25, 2, "img/element/arm/3.png"},
	{"Battle Fury", -35, 2, "img/element/arm/4.png"},
	{"Manta Style", -45, 2, "img/element/arm/5.png"},
	{"Lothar Edge", -55, 3, "img/element/arm/6.png"},
	{"Heaven", -65, 3, "img/element/arm/6.png"},
	{"Difussal Blade", -75, 3, "img/element/arm/7.png"},
	{"Blade of Alarity", -85, 4, "img/element/arm/8.png"},
	{"Satanic", -95, 4, "img/element/arm/9.png"},
	{"Buriza", -105, 4, "img/element/arm/10.png"},
	{"Abyssal Blade", -115, 5, "img/element/arm/11.png"},
	{"Armlet of Mordigan", -125, 5, "img/element/arm/12.png"},
	{"Divine Rapier", -145, 7, "img/element/arm/13.png"},
  {NULL, 0, 0, NULL}
};

static LokElement LOK_ELEMENT_POTIONS[] = {
  {"Tango", 10, 2, "img/element/potion/1.png"},
	{"Clarity", 50, 3, "img/element/potion/2.png"},
	{"Healing Salve", 100, 4, "img/element/potion/3.png"},
	{"Mango", 200, 5, "img/element/potion/4.png"},
	{"Ironwood", 350, 6, "img/element/potion/5.png"},
	{"Tranquil Potion", 500, 7, "img/element/potion/6.png"},
  {NULL, 0, 0, NULL}
};

LokElement *
lok_element_new (const tchar * element_name, int points, int weight,
    const tchar * img_path)
{
  LokElement *element;
  element = malloc (sizeof (LokElement));
  element->name = element_name;
  element->points = points;
  element->weight = weight;
  element->img_path = img_path;
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
            LOK_ELEMENT_ARMS[i].points, LOK_ELEMENT_ARMS[i].weight,
            LOK_ELEMENT_ARMS[i].img_path);
        t_array_append (elements, element);
      }
      break;
    case LOK_ELEMENT_TYPE_POTION:
      for (i = 0; LOK_ELEMENT_POTIONS[i].name != NULL; i++) {
        element = lok_element_new (LOK_ELEMENT_POTIONS[i].name,
            LOK_ELEMENT_POTIONS[i].points, LOK_ELEMENT_POTIONS[i].weight,
            LOK_ELEMENT_POTIONS[i].img_path);
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

tchar *
lok_element_type_to_string (LokElementType type)
{
  switch (type) {
    case LOK_ELEMENT_TYPE_ARM:
      return strdup ("Arm");
    case LOK_ELEMENT_TYPE_POTION:
      return strdup ("Potion");
    default:
      return strdup ("(error)");
  }
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
