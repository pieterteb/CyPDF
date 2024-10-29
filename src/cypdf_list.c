#include <stdlib.h>
#include <string.h>

#include "cypdf_list.h"
#include "cypdf_log.h"
#include "cypdf_memory.h"
#include "cypdf_print.h"
#include "cypdf_types.h"



static void Resize(CYPDF_List* const list);


CYPDF_List* CYPF_NewList(const size_t block_size) {
    CYPDF_TRACE;

    CYPDF_List* list = CYPDF_malloc(sizeof(CYPDF_List));
    list->elements = NULL;
    list->element_count = 0;
    list->block_size = block_size;
    list->tot_size = 0;

    return list;
}

void CYPDF_FreeList(CYPDF_List* const list) {
    CYPDF_TRACE;

    free(list->elements);

    free(list);
}

void CYPDF_PrintList(CYPDF_List* const list, CYPDF_Channel* const channel, const CYPDF_PrintFunc print) {
    CYPDF_TRACE;

    if (list) {
        size_t length = CYPDF_ListLength(list);
        for (size_t i = 0; i < length; ++i) {
            print(channel, list->elements[i]);
        }
    }
}


void CYPFD_ListAppend(CYPDF_List* const list, void* const element) {
    CYPDF_TRACE;

    if (!list) {
        fprintf(stderr, "List is NULL.\n");
    }
    
    if (list->element_count == list->tot_size) {
        Resize(list);
    }
    list->elements[list->element_count] = element;
    ++list->element_count;
}

static void Resize(CYPDF_List* const list) {
    CYPDF_TRACE;

    list->tot_size += list->block_size;
    list->elements = CYPDF_realloc(list->elements, list->tot_size * sizeof(void*));
}


void* CYPDF_ListAtIndex(CYPDF_List* const list, const size_t index) {
    CYPDF_TRACE;

    if (index < CYPDF_ListLength(list)) {
        return list->elements[index];
    }

    return NULL;
}

void CYPDF_ListSetAtIndex(CYPDF_List* const list, const size_t index, void* const value) {
    CYPDF_TRACE;

    size_t length = CYPDF_ListLength(list);
    if (index >= length) {
        for (size_t i = length; i < index; ++i) {
            CYPFD_ListAppend(list, NULL);
        }
        CYPFD_ListAppend(list, value);
    } else {
        list->elements[index] = value;
    }
}

size_t CYPDF_ListLength(const CYPDF_List* const list) {
    CYPDF_TRACE;

    return list->element_count;
}
