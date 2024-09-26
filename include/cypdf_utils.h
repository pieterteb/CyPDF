#ifndef CYPDF_UTILS_H
#define CYPDF_UTILS_H


#include <ctype.h>



#define MAX(a, b) ((a) > (b) ? (a) : (b))


void* CYPDF_smalloc(size_t size);

void* CYPDF_scalloc(size_t element_count, size_t element_size);

void* CYPDF_srealloc(void* ptr, size_t size);



#endif /* CYPDF_UTILS_H */
