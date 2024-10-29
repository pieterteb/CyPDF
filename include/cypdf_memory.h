#ifndef CYPDF_MEMORY_H
#define CYPDF_MEMORY_H


#include <stddef.h>

#include "cypdf_types.h"



typedef struct CYPDF_MemMgr CYPDF_MemMgr;
struct CYPDF_MemMgr {
    void**          ptrs;
    size_t          ptr_count;  /* Number of void* in ptrs. */
    size_t          tot_size;   /* Total amount of void pointers that can be stored. */

    CYPDF_FreeFunc  free_func;
};


CYPDF_MemMgr* CYPDF_NewMemMgr(const CYPDF_FreeFunc free_func);

void* CYPDF_GetMem(CYPDF_MemMgr* const restrict memmgr, size_t size);

void CYPDF_DestroyMemMgr(CYPDF_MemMgr* memmgr);


void* CYPDF_malloc(size_t size);

void* CYPDF_calloc(size_t element_count, size_t element_size);

void* CYPDF_realloc(void* ptr, size_t size);



#endif /* CYPDF_MEMORY_H */