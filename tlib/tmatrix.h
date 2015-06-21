#ifndef __T_MATRIX_H__
#define __T_MATRIX_H__

#include "ttypes.h"

struct _TMatrix {
  TArray *parent;
  int width;
  int height;
};

TMatrix * t_matrix_new (int width, int height);
void t_matrix_new_insert (TMatrix * matrix, tpointer data, int i, int j);
tpointer t_matrix_get (TMatrix * matrix, int i, int j);
void t_matrix_free (TMatrix * matrix);

#endif /* __T_MATRIX_H__ */
