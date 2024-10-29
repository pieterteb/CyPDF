#ifndef CYPDF_LIST_H
#define CYPDF_LIST_H


#include <stddef.h>

#include "cypdf_memory.h"
#include "cypdf_types.h"



#define CYPDF_LIST_DEFAULT_BLOCK_SIZE    16


typedef struct CYPDF_List {
    void**  elements;
    size_t  element_count;
    size_t  block_size;
    size_t  tot_size;
} CYPDF_List;


CYPDF_List* CYPF_NewList(const size_t block_size);

void CYPDF_FreeList(CYPDF_List* const list);

void CYPDF_PrintList(CYPDF_List* const list, CYPDF_Channel* const channel, const CYPDF_PrintFunc print);


void CYPFD_ListAppend(CYPDF_List* const list, void* const element);

void* CYPDF_ListAtIndex(CYPDF_List* const list, const size_t index);

void CYPDF_ListSetAtIndex(CYPDF_List* const list, const size_t index, void* const value);

size_t CYPDF_ListLength(const CYPDF_List* const list);



#endif /* CYPDF_LIST_H */