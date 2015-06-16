#include "tlib.h"

int
t_random_int (int min, int max)
{
  return rand () % max + 1;
}
