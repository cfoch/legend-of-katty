#include "lok.h"

int
main (int argc, char ** argv)
{
  TArray *elements;
  elements = lok_element_create_elements (LOK_ELEMENT_TYPE_ARM);
  LOK_DEBUG_ELEMENTS (elements);
  return 0;
}
