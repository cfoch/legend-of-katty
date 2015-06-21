#ifndef __T_MLIST_H__
#define __T_MLIST_H__

#include "ttypes.h"

#define T_MLIST(x)      ((TMList *) x)

struct _TMList {
  TList *start;
  TList *end;
  int length;
};

TMList * t_mlist_new ();
tpointer t_mlist_pop (TMList * list);
void t_mlist_prepend (TMList * list, tpointer data);
void t_mlist_append (TMList * list, tpointer data);
TBoolean t_mlist_is_empty (TMList * list);

#endif /* __T_MLIST_H__ */
