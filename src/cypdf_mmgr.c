#include <stdlib.h>

#include "cypdf_mmgr.h"
#include "cypdf_types.h"
#include "cypdf_utils.h"



CYPDF_MMgr* CYPDF_NewMMgr(const CYPDF_FreeFunc free_func) {
    CYPDF_MMgr* mmgr = CYPDF_smalloc(sizeof(CYPDF_MMgr));

    mmgr->ptrs = NULL;
    mmgr->ptr_count = 0;
    mmgr->tot_size = 0;
    mmgr->free_func = free_func;

    return mmgr;
}

static void CYPDF_MMgrAppend(CYPDF_MMgr* const mmgr, void* const ptr) {
    if (mmgr && ptr) {
        if (mmgr->ptr_count == mmgr->tot_size) {
            if (!mmgr->tot_size) {
                mmgr->tot_size = 1;
            } else {
                mmgr->tot_size *= 2;
            }
            mmgr->ptrs = CYPDF_srealloc(mmgr->ptrs, mmgr->tot_size * sizeof(void*));
        }

        mmgr->ptrs[mmgr->ptr_count] = ptr;
        ++mmgr->ptr_count;
    }
}

void* CYPDF_GetMem(CYPDF_MMgr* const mmgr, const size_t size) {
    void* mem = NULL;

    if (mmgr) {
        mem = CYPDF_smalloc(size);

        if (mem) {
            CYPDF_MMgrAppend(mmgr, mem);
        }
    }

    return mem;
}

void CYPDF_DestroyMMgr(CYPDF_MMgr* mmgr) {
    if (mmgr) {
        for (size_t i = 0; i < mmgr->ptr_count; ++i) {
            mmgr->free_func(mmgr->ptrs[i]);
        }

        free(mmgr->ptrs);
        free(mmgr);
    }
}
