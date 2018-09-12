#ifndef arr_h_INCLUDED
#define arr_h_INCLUDED

#include <stddef.h>

void *arrnew(size_t nmemb, size_t item_size);
void *arrappend(void **dest);
void *arrextend(void **dest, size_t n);
size_t arrlen(const void *data);
void arrfree(void *data);

#define ARRAPPEND(dest) arrappend((void **)dest)
#define ARREXTEND(dest, n) arrextend((void **)dest, n)

#endif  // arr_h_INCLUDED
