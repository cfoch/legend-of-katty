#ifndef __T_TYPES_H__
#define __T_TYPES_H__

#include <stdlib.h>

#define INT_TO_TPOINTER(i)     (tpointer) (long) (i)
#define TPOINTER_TO_INT(i)     (int) (long) (i)

#define t_alloc(a,t,sz)        realloc(a, sz * sizeof (t))
#define t_swap(a, b)           do { typeof(a) t; t = a; a = b; b = t; } while(0)

#ifndef TRUE
#define TRUE  1
#define FALSE !TRUE
#endif


typedef int TBoolean;
typedef void * tpointer;
typedef char tchar;

typedef void (*TFunc)           (tpointer data,
                                 tpointer user_data);
typedef int  (*TCompFunc)       (tpointer a,
                                 tpointer b);
typedef int  (*TCompDataFunc)   (tpointer a,
                                 tpointer b,
                                 tpointer user_data);
typedef int  (*TEqDataFunc)     (tpointer a,
                                 tpointer b,
                                 tpointer user_data);

typedef struct _TArray TArray;
typedef struct _TList TList;
typedef struct _TMatrix TMatrix;
typedef struct _TMList TMList;

#endif /* __T_TYPES_H__ */


