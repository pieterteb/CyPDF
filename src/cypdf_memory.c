#include <stdlib.h>

#include "cypdf_memory.h"
#include "cypdf_log.h"
#include "cypdf_types.h"



CYPDF_MemMgr* CYPDF_NewMemMgr(const CYPDF_FreeFunc free_func) {
    CYPDF_TRACE;

    CYPDF_MemMgr* memmgr = CYPDF_malloc(sizeof(CYPDF_MemMgr));

    memmgr->ptrs = NULL;
    memmgr->ptr_count = 0;
    memmgr->tot_size = 0;
    memmgr->free_func = free_func;

    return memmgr;
}

static void CYPDF_MemMgrAppend(CYPDF_MemMgr* const restrict memmgr, void* const restrict ptr) {
    CYPDF_TRACE;

    if (memmgr) {
        if (memmgr->ptr_count == memmgr->tot_size) {
            if (!memmgr->tot_size) {
                memmgr->tot_size = 1;
            } else {
                memmgr->tot_size *= 2;
            }
            memmgr->ptrs = CYPDF_realloc(memmgr->ptrs, memmgr->tot_size * sizeof(void*));
        }
        memmgr->ptrs[memmgr->ptr_count] = ptr;
        ++memmgr->ptr_count;
    }
}

void* CYPDF_GetMem(CYPDF_MemMgr* const restrict memmgr, size_t size) {
    CYPDF_TRACE;

    void* mem = NULL;

    if (memmgr) {
        mem = CYPDF_calloc(1, size);

        if (mem) {
            CYPDF_MemMgrAppend(memmgr, mem);
        }
    }

    return mem;
}

void CYPDF_DestroyMemMgr(CYPDF_MemMgr* memmgr) {
    CYPDF_TRACE;

    if (memmgr) {
        for (size_t i = 0; i < memmgr->ptr_count; ++i) {
            memmgr->free_func(memmgr->ptrs[i]);
        }

        free(memmgr->ptrs);
        free(memmgr);
    }
}


void* CYPDF_malloc(size_t size) {
    CYPDF_TRACE;

    void* mem = malloc(size);
    if (!mem) {
        fprintf(stderr, "Failed to allocate %zu bytes of memory.\n", size);
    }

    return mem;
}

void* CYPDF_calloc(size_t element_count, size_t element_size) {
    CYPDF_TRACE;

    void* mem = calloc(element_count, element_size);
    if (!mem) {
        fprintf(stderr, "Failed to allocate %zu bytes of memory.\n", element_count * element_size);
    }

    return mem;
}

void* CYPDF_realloc(void* ptr, size_t size) {
    CYPDF_TRACE;

    void* mem = realloc(ptr, size);
    if (mem == NULL) {
        fprintf(stderr, "Failed to reallocate %p to a size of %zu.\n", ptr, size);
    }

    return mem;
}
