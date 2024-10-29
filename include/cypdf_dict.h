#ifndef CYPDF_DICT_H
#define CYPDF_DICT_H


#include <stddef.h>

#include "cypdf_list.h"
#include "cypdf_memory.h"
#include "cypdf_name.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_types.h"



#define CYPDF_FREE_DICT     CYPDF_FreeDict
#define CYPDF_PRINT_DICT    CYPDF_PrintDict


typedef struct CYPDF_ObjDict {
    CYPDF_ObjHeader header;

    CYPDF_List*     key_list;
    CYPDF_List*     value_list;

    CYPDF_MemMgr*   memmgr;
} CYPDF_ObjDict;


CYPDF_ObjDict* CYPDF_NewDict(CYPDF_MemMgr* const memmgr);

void CYPDF_FreeDict(CYPDF_Object* obj);

void CYPDF_PrintDict(CYPDF_Channel* const channel, const CYPDF_Object* const obj);


void CYPDF_DictAppend(CYPDF_ObjDict* const restrict dict, const char* restrict key_name, CYPDF_Object* const restrict value);

void CYPDF_DictSetAtIndex(CYPDF_ObjDict* const restrict dict, const size_t index, const char* restrict key_name, CYPDF_Object* const restrict value);

CYPDF_ObjName* CYPDF_DictKeyAtIndex(CYPDF_ObjDict* const dict, const size_t index);

CYPDF_Object* CYPDF_DictValueAtIndex(CYPDF_ObjDict* const dict, const size_t index);

CYPDF_Object* CYPDF_DictValueAtName(CYPDF_ObjDict* const restrict dict, const char key_name[restrict static 1]);

size_t CYPDF_DictLength(CYPDF_ObjDict* const dict);



#endif /* CYPDF_DICT_H */
