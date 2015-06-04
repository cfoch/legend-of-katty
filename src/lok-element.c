#include "lok.h"

LokElement *
lok_element_new (const tchar * element_name, int points, int weight)
{
  LokELement *element;
  element = malloc (sizeof (LokElement));
  element->name = element_name;
  element->points = points;
  element->weight = weight;
  return element;
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
