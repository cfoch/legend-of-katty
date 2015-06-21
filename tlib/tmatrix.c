#include "tlib.h"

TMatrix *
t_matrix_new (int width, int height)
{
  TMatrix *matrix;
  TArray *parent;
  int i;

  matrix = malloc (sizeof (TMatrix));

  parent = t_array_new_with_length (width);
  for (i = 0; i < width; i++) {
    TArray *child;
    child = t_array_new_with_length (height);
    parent->vector[i] = child;
  }

  matrix->parent = parent;
  matrix->height = height;
  matrix->width = width;

  return matrix;
}

void
t_matrix_insert (TMatrix * matrix, tpointer data, int i, int j)
{
  TArray *child;
  child = T_ARRAY (t_array_index (matrix->parent, i));
  t_array_insert (child, j, data);
}

tpointer
t_matrix_get (TMatrix * matrix, int i, int j)
{
  TArray *child;
  child = T_ARRAY (t_array_index (matrix->parent, i));
  return t_array_index (child, j);
}

void
t_matrix_free (TMatrix * matrix)
{
  int i;
  for (i = 0; i < matrix->width; i++) {
    TArray *child;
    child = T_ARRAY (t_array_index (matrix->parent, i));
    t_array_free (child, NULL);
  }
  t_array_free (matrix->parent, NULL);
  free (matrix);
}
