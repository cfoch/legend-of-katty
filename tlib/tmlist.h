#ifndef __T_MLIST_H__
#define __T_MLIST_H__

#define T_MLIST(x)      ((TMList *) x)

typedef TMList struct _TMList;

struct _TMList {
  TList *start;
  TList *end;
  int length;
};

TMList * t_mlist_new ();
tpointer t_mlist_pop (TMList * list);
void t_mlist_prepend (TMlist * list, tpointer data);
void t_mlist_append (TMList * list, tpointer data);

#endif /* __T_MLIST_H__ */
