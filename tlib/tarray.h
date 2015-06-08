#ifndef __T_ARRAY_H__
#define __T_ARRAY_H__
#include "tlib.h"

struct _TArray
{
  tpointer *vector;
  int len;
  TFunc free_func;
};

typedef struct _TArray TArray;

TArray * t_array_new ();
void t_array_foreach (TArray * array, TFunc func, tpointer user_data);
void t_array_append (TArray * array, tpointer data);
tpointer t_array_index (TArray * array, int index);
int t_array_length (TArray * array);
void t_array_merge_sort (TArray * array, TCompFunc cmp_func);
void t_array_insertion_sort (TArray * array, TCompFunc cmp_func);
void t_array_merge_sort_with_data (TArray * array, TCompDataFunc cmp_func,
    tpointer cmp_data);
void t_array_insertion_sort_with_data (TArray * array, TCompDataFunc cmp_func,
    tpointer cmp_data);
TArray * t_array_filter2_with_data (TArray * array, tpointer target,
    TEqDataFunc eq_func, tpointer user_data);
TArray * t_array_filter_with_data (TArray * array, tpointer target,
    TCompDataFunc cmp_func, tpointer user_data);
int persona_cmp_binary (tpointer pers1, tpointer target, tpointer crits);
void t_array_set_free_func (TArray * array, TFunc free_func);
void t_array_free (TArray * array, tpointer user_data);
void t_array_insert_sorted (TArray * array, tpointer element,
    TCompDataFunc cmp_func, tpointer user_data);
void t_array_tim_sort_with_data (TArray * array, TCompDataFunc cmp_func,
    tpointer cmp_data);
void t_array_remove_last (TArray * array);
void t_array_insert_sorted (TArray * array, tpointer element,
    TCompDataFunc cmp_func, tpointer user_data);
int t_array_binary_lookup_index_with_data (TArray * array, tpointer element,
    TCompDataFunc cmp_func, tpointer user_data, TBoolean * found);
TArray * t_array_new_with_length (int length);
void t_array_insert (TArray * array, int index, tpointer data);

#define T_ARRAY(t)           (TArray *) (t)

#endif /* __T_ARRAY_H__ */
