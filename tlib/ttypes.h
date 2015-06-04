#ifndef __T_TYPES_H__
#define __T_TYPES_H__

#define TRUE  1
#define FALSE !TRUE

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

#endif /* __T_TYPES_H__ */


