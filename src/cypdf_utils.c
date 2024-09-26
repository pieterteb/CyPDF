#include <stdio.h>
#include <stdlib.h>

#include "cypdf_utils.h"



void* CYPDF_smalloc(size_t size) {
    void* mem = malloc(size);
    if (!mem) {
        fprintf(stderr, "Failed to allocate %zu bytes of memory.\n", size);
    }

    return mem;
}

void* CYPDF_scalloc(size_t element_count, size_t element_size) {
    void* mem = calloc(element_count, element_size);
    if (!mem) {
        fprintf(stderr, "Failed to allocate %zu bytes of memory.\n", element_count * element_size);
    }

    return mem;
}

void* CYPDF_srealloc(void* ptr, size_t size) {
    void* mem = realloc(ptr, size);
    if (mem == NULL) {
        fprintf(stderr, "Failed to reallocate %p to a size of %zu.\n", ptr, size);
    }

    return mem;
}
