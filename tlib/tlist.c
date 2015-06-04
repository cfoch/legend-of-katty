#include "tlist.h"

TList *
t_list_new ()
{
  return NULL;
}

TList *
t_list_prepend (TList * list, tpointer data)
{
  TList * new_list;
  new_list = malloc (sizeof (TList));
  new_list->data = data;
  new_list->next = list;
  new_list->prev = NULL;
  return new_list;
}

void
t_list_free (TList * list)
{
  TList *l;
  if (!list)
    return;
  l = list;
  while (l) {
    l = list->next;
    free (list);
  }
}

TBoolean
t_list_is_empty (TList * list)
{
  return list == NULL;
}


