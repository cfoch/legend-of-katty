#include <stdlib.h>

#include "tutils.h"

int
t_random_int (int min, int max)
{
  return rand () % max + min;
}
