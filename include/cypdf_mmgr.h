#ifndef CYPDF_MMGR_H
#define CYPDF_MMGR_H


#include "cypdf_mmgr.h"
#include "cypdf_types.h"



typedef struct CYPDF_MMgr {
    void**          ptrs;
    size_t          ptr_count;  /* Number of void* in ptrs. */
    size_t          tot_size;   /* Total amount of void pointers that can be stored. */

    CYPDF_FreeFunc  free_func;
} CYPDF_MMgr;


CYPDF_MMgr* CYPDF_NewMMgr(const CYPDF_FreeFunc free_func);

void* CYPDF_GetMem(CYPDF_MMgr* const mmgr, const size_t size);

void CYPDF_DestroyMMgr(CYPDF_MMgr* const mmgr);



#endif /* CYPDF_MMGR_H */