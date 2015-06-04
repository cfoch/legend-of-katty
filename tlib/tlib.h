#ifndef __T_LIB_H__
#define __T_LIB_H__

#include <stdlib.h>

#define INT_TO_TPOINTER(i)     (tpointer) (long) (i)
#define TPOINTER_TO_INT(i)     (int) (long) (i)

#define t_alloc(a,t,sz)        realloc(a, sz * sizeof (t))
#define t_swap(a, b)           do { typeof(a) t; t = a; a = b; b = t; } while(0)

#include "ttypes.h"
#include "tarray.h"

#endif /* __T_LIB_H__ */
