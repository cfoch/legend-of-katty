#ifndef __T_LIST_H__
#define __T_LIST_H__

typedef TList struct _TList;

struct _TList {
  tpointer data;
  TList * next;
  TList * prev;
};

TList * t_list_prepend (TList * list, tpointer data);
void t_list_free (TList * list);
TBoolean t_list_is_empty (TList * list);

#endif /* __T_LIST_H__ */
