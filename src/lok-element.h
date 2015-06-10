#include "lok.h"

#ifndef __LOK_ELEMENT_H__
#define __LOK_ELEMENT_H__

typedef enum {
  LOK_ELEMENT_TYPE_POTION,
  LOK_ELEMENT_TYPE_ARM,
  LOK_ELEMENT_TYPE_MEDAL
} LokElementType;

struct _LokElement {
  const tchar *name;
  int points;
  int weight;
};

LokElement * lok_element_new (const tchar * element_name, int points,
    int weight);
void lok_element_free (LokElement * element);
LokElementType lok_element_get_type (LokElement * element);
TArray * lok_element_create_elements (LokElementType type);
void LOK_DEBUG_ELEMENT (LokElement * element);
void LOK_DEBUG_ELEMENTS (TArray * elements);

#endif /* __LOK_ELEMENT_H__ */
