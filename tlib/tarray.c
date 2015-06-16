#include "tarray.h"

#define _t_alloc_array()     malloc(sizeof (TArray))
#define _t_realloc_vector(a, sz)   t_alloc(a,tpointer,sz)

TArray *
t_array_new ()
{
  TArray *array;

  array = _t_alloc_array ();
  array->len = 0;
  array->vector = NULL;

  return array;
}

TArray *
t_array_new_with_length (int length)
{
  TArray *array;
  int i;

  array = t_array_new ();
  for (i = 0; i < length; i++)
    t_array_append (array, NULL);

  return array;
}

void
t_array_set_free_func (TArray * array, TFunc free_func)
{
  array->free_func = free_func;
}

void
t_array_foreach (TArray * array, TFunc func, tpointer user_data)
{
  int i;
  for (i = 0; i < array->len; i++)
    func (array->vector[i], user_data);
}

void
t_array_append (TArray * array, tpointer data)
{
  array->len++;
  array->vector = realloc (array->vector, sizeof (tpointer) * array->len);
  array->vector[array->len - 1] = data;  
}

void
t_array_free (TArray * array, tpointer user_data)
{
  t_array_foreach (array, array->free_func, user_data);
}

tpointer
t_array_index (TArray * array, int index)
{
  return array->vector[index];
}

void
t_array_insert (TArray * array, int index, tpointer data)
{
  array->vector[index] = data;
}

int
t_array_length (TArray * array)
{
  return array->len;
}

void
t_array_remove_last (TArray * array)
{
  array->len--;
  array->vector = realloc (array, sizeof (tpointer) * array->len);
}

/* t_array_binary_lookup_index_with_data
 * Lookup for the index of a given target element using binary search.
 */
int
t_array_binary_lookup_index_with_data (TArray * array, tpointer target,
    TCompDataFunc cmp_func, tpointer user_data, TBoolean * found)
{
  int start_index = 0, end_index = t_array_length (array) - 1, mid;
  *found = FALSE;

  mid = 0;
  while ((start_index <= end_index) && (!(*found))) {
    tpointer elem;
    mid = (start_index + end_index) / 2;
    elem = t_array_index (array, mid);
    if (cmp_func (elem, target, user_data) == 0)
      *found = TRUE;
    else if (cmp_func (elem, target, user_data) < 0)
      start_index = mid + 1;
    else
      end_index = mid - 1;
  }
  return mid;
}

/*
 * t_array_filter2_with_data
 * Filter a given target element for non-ordered arrays.
 */
TArray *
t_array_filter2_with_data (TArray * array, tpointer target, TEqDataFunc eq_func,
    tpointer user_data)
{
  int i;
  TArray *ret;
  ret = t_array_new ();

  for (i = 0; i < t_array_length (array); i++) {
    tpointer elem;
    elem = t_array_index (array, i);
    if (eq_func (elem, target, user_data))
      t_array_append (ret, elem);
  }
  return ret;
}

/*
 * t_array_filter_with_data
 * Filter a given target element for ordered arrays using binary search method.
 */
TArray *
t_array_filter_with_data (TArray * array, tpointer target,
    TCompDataFunc cmp_func, tpointer user_data)
{
  TArray *ret = t_array_new ();
  tpointer elem;
  int mid;
  TBoolean found;

  mid = t_array_binary_lookup_index_with_data (array, target, cmp_func,
      user_data, &found);

  if (found) {
    int i = mid - 1, j = mid + 1;

    elem = array->vector[mid];
    t_array_append (ret, elem);
    elem = t_array_index (array, i);
    while ((i >= 0) && (cmp_func (elem, target, user_data) == 0)){
      t_array_append (ret, elem);
      i--;
      elem = t_array_index (array, i);
    }

    elem = t_array_index (array, j);
    while ((j <= t_array_length (array) - 1) && 
        (cmp_func (elem, target, user_data) == 0)){
      t_array_append (ret, elem);
      j++;
      elem = t_array_index (array, j);
    }
  }
  return ret;
}


static void
_t_array_merge (TArray * array, int start_index, int middle_index,
    int end_index, TCompFunc cmp_func)
{
  int i, j, k, len_dummy;
  tpointer * dummy;

  dummy = malloc (sizeof (tpointer) * (end_index - start_index + 1));

  i = start_index;
  j = middle_index + 1;
  len_dummy = 0;
  while ((i <= middle_index) && (j <= end_index))
    if (cmp_func (array->vector[i], array->vector[j]) > 0)
      dummy[len_dummy++] = array->vector[j++];
    else
      dummy[len_dummy++] = array->vector[i++];

  if (i > middle_index)
    for (k = j; k <= end_index; k++)
      dummy[len_dummy++] = array->vector[k];

  if (j > end_index)
    for (k = i; k <= middle_index; k++)
      dummy[len_dummy++] = array->vector[k];

  for (i = 0; i < len_dummy; i++)
    array->vector[i + start_index] = dummy[i];
}

static void
_t_array_merge_sort (TArray * array, int start_index, int end_index,
    TCompFunc cmp_func)
{
  int middle_index;
  if (start_index == end_index)
    return;
  middle_index = (start_index + end_index) / 2;
  _t_array_merge_sort (array, start_index, middle_index, cmp_func);
  _t_array_merge_sort (array, middle_index + 1, end_index, cmp_func);
  _t_array_merge (array, start_index, middle_index, end_index, cmp_func);
}

void
t_array_merge_sort (TArray * array, TCompFunc cmp_func)
{
  _t_array_merge_sort (array, 0, array->len - 1, cmp_func);
}

void
t_array_insertion_sort (TArray * array, TCompFunc cmp_func)
{
  int i, j;
  for (i = 1; i < array->len; i++) {
    j = i;
    while ((j > 0) && (cmp_func (array->vector[j], array->vector[j - 1]) < 0)) {
      t_swap (array->vector[j - 1], array->vector[j]);
      j--;
    }
  }
}

/* TODO: this is *really* ugly! Make me more beatiful */

static void
_t_array_merge_with_data (TArray * array, int start_index, int middle_index,
    int end_index, TCompDataFunc cmp_func, tpointer cmp_data)
{
  int i, j, k, len_dummy;
  tpointer * dummy;

  dummy = malloc (sizeof (tpointer) * (end_index - start_index + 1));

  i = start_index;
  j = middle_index + 1;
  len_dummy = 0;
  while ((i <= middle_index) && (j <= end_index))
    if (cmp_func (array->vector[i], array->vector[j], cmp_data) > 0)
      dummy[len_dummy++] = array->vector[j++];
    else
      dummy[len_dummy++] = array->vector[i++];

  if (i > middle_index)
    for (k = j; k <= end_index; k++)
      dummy[len_dummy++] = array->vector[k];

  if (j > end_index)
    for (k = i; k <= middle_index; k++)
      dummy[len_dummy++] = array->vector[k];

  for (i = 0; i < len_dummy; i++)
    array->vector[i + start_index] = dummy[i];
}

static void
_t_array_merge_sort_with_data (TArray * array, int start_index, int end_index,
    TCompDataFunc cmp_func, tpointer cmp_data)
{
  int middle_index;
  if (start_index == end_index)
    return;
  middle_index = (start_index + end_index) / 2;
  _t_array_merge_sort_with_data (array, start_index, middle_index, cmp_func,
      cmp_data);
  _t_array_merge_sort_with_data (array, middle_index + 1, end_index, cmp_func,
      cmp_data);
  _t_array_merge_with_data (array, start_index, middle_index, end_index,
      cmp_func, cmp_data);
}

void
t_array_merge_sort_with_data (TArray * array, TCompDataFunc cmp_func,
    tpointer cmp_data)
{
  _t_array_merge_sort_with_data (array, 0, array->len - 1, cmp_func, cmp_data);
}

void
t_array_insertion_sort_with_data (TArray * array, TCompDataFunc cmp_func,
    tpointer cmp_data)
{
  int i, j;
  for (i = 1; i < array->len; i++) {
    j = i;
    while ((j > 0) &&
      (cmp_func (array->vector[j], array->vector[j - 1], cmp_data) < 0)) {
      t_swap (array->vector[j - 1], array->vector[j]);
      j--;
    }
  }
}

/* TIM SORT */

static int
_calc_minrun(int n){
    int r = 0;
    while (n >= 64){
      r |= n & 1;
    n >>= 1;
  }
  return n + r;
}


/*
 * t_array_insert_sorted
 * Insert elements to an array keeping them sorted.
 */
void
t_array_insert_sorted (TArray * array, tpointer element, TCompDataFunc cmp_func,
    tpointer user_data)
{
  int i, pos;
  TBoolean found;
  int cmp;

  pos = t_array_binary_lookup_index_with_data (array, element, cmp_func,
      user_data, &found);

  t_array_append (array, NULL);

  if (array->len > 1) {
    cmp = cmp_func (t_array_index (array, pos), element, user_data);

    if (cmp < 0)
      pos++;
    for (i = array->len - 1; i >= pos + 1; i--)
      array->vector[i] = array->vector[i - 1];
  }

  array->vector[pos] = element;
}

static TArray *
_get_run_with_data (TArray *array, int * i, int minrun,
    TCompDataFunc cmp_func, tpointer cmp_data)
{
  TArray *run;
  run = t_array_new ();
  
  /*el ultimo elemento*/
  if (*i == array->len- 1){
    t_array_append (run, array->vector[*i]);
		(*i)++;
    return run;
  }
    
  
  /*swap first and second*/
  if (cmp_func (array->vector[*i], array->vector[*i + 1], cmp_data) > 0){
		t_array_append (run, array->vector[*i + 1]);		
		t_array_append (run, array->vector[*i]);
	} else {
	  t_array_append (run, array->vector[*i]);
  	t_array_append (run, array->vector[*i + 1]);
	}
  (*i)++;         
  
	if (*i == array->len - 1){
			(*i)++;
			return run;
	}
  /*add*/
  while (cmp_func(run->vector[run->len - 1],
			array->vector[*i + 1], cmp_data)<=0) {
    t_array_append (run, array->vector[*i + 1]);
    (*i)++;
		if (*i == array->len - 1){
			(*i)++;
			return run;
		}
  }
	if (run->len >= minrun){
		(*i)++;
		return run;
	}

  while ((*i < array->len - 1) && (run->len < minrun)) {
    t_array_insert_sorted (run, array->vector[*i + 1], cmp_func, cmp_data);
    (*i)++;
		if (*i == array->len - 1){
			(*i)++;
			return run;
		}
  }

  /*add*/
  while ((run->len >= minrun) && (cmp_func (run->vector[run->len - 1], 
			array->vector[*i + 1], cmp_data) <= 0)){
		
    t_array_append (run, array->vector[*i + 1]);
    (*i)++;
		if (*i == array->len - 1){
			(*i)++;
			return run;
		}
  }
	(*i)++;
  return run;
}


static TArray *
_timsort_merge (TArray * a, TArray * b,TCompDataFunc cmp_func, tpointer cmp_data)
{
  int i, j, k, first_end, second_end;
  TArray *result;
  result = t_array_new();

  i = 0;
  j = 0;
  first_end = a->len;
  second_end = b->len;
  while ((i < first_end) && (j < second_end))
    if (cmp_func (a->vector[i], b->vector[j], cmp_data) > 0)
      t_array_append(result ,b->vector[j++]);
    else
      t_array_append(result ,a->vector[i++]);

  if (i >= first_end)
    for (k = j; k < second_end; k++)
      t_array_append(result ,b->vector[k]);

  if (j >= second_end)
    for (k = i; k < first_end ; k++)
      t_array_append(result ,a->vector[k]);

  return result;
}

void
t_array_tim_sort_with_data (TArray * array, TCompDataFunc cmp_func,
    tpointer cmp_data)
{
  TArray *run_x, *run_y, *run_z;
	TArray *runs;
  int i = 0; /* indice para el array*/
  int minrun;
  
  if (array->len < 64) {
    t_array_insertion_sort_with_data (array,cmp_func, cmp_data);
    return;
  }

  minrun = _calc_minrun(array->len); /*Definido */

  
  runs = t_array_new ();
  TArray *run;

  while (i < array->len) {
		TArray *merged;
    run = _get_run_with_data (array, &i, minrun, cmp_func, cmp_data);
    t_array_append (runs, run);
    if (runs->len >= 3) {
      run_x = t_array_index (runs, 2); /*primero*/
      run_y = t_array_index (runs, 1); /*segundo*/
      run_z = t_array_index (runs, 0); /*tercero*/
      if (!(run_x->len > run_y->len + run_z->len && run_y->len > run_z->len)) {
        TArray *smaller, *larger;
    
        if (run_x->len < run_z->len) {
            smaller = run_x;
            larger = run_z;
        } else { 
            smaller = run_z;
            larger = run_x;
        }
				/*Remove all
				t_array_remove_last (runs);
        t_array_remove_last (runs);
        t_array_remove_last (runs);
				*/
        free (runs);
				runs = t_array_new (); /*clean*/
        merged = _timsort_merge (run_y, smaller, cmp_func, cmp_data);
        t_array_append(runs, merged);
        t_array_append(runs, larger);
      } else {
				merged = _timsort_merge (run_x, run_y, cmp_func, cmp_data);
				/*Remove all
				t_array_remove_last (runs);
        t_array_remove_last (runs);
        t_array_remove_last (runs);
				*/
        free (runs);
				runs = t_array_new (); /*clean*/
				t_array_append(runs, merged);
        t_array_append(runs, run_z);
			}		
    }
  }
  run_x = t_array_index (runs, 1); /*primero*/
  run_y = t_array_index (runs, 0); /*segundo*/
  array->vector = _timsort_merge(run_x, run_y, cmp_func, cmp_data)->vector; /*mezcla final*/
}

