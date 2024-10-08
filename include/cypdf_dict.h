#ifndef CYPDF_DICT_H
#define CYPDF_DICT_H


#include <stddef.h>

#include "cypdf_memmgr.h"
#include "cypdf_name.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_types.h"



#define CYPDF_FREE_DICT     CYPDF_FreeDict
#define CYPDF_PRINT_DICT    CYPDF_PrintDict


typedef struct CYPDF_ObjDict {
    CYPDF_ObjHeader header;

    CYPDF_ObjName** keys;
    CYPDF_Object**  values;
    size_t          count;

    CYPDF_MemMgr*   memmgr;
} CYPDF_ObjDict;


CYPDF_ObjDict* CYPDF_NewDict(CYPDF_MemMgr* const restrict memmgr);

void CYPDF_FreeDict(CYPDF_Object* obj);

void CYPDF_PrintDict(CYPDF_Channel* const restrict channel, const CYPDF_Object* const obj);


void CYPDF_DictAppend(CYPDF_ObjDict* const restrict dict, const char key_name[restrict static 1], CYPDF_Object* const restrict value);

void CYPDF_DictSetAtIndex(CYPDF_ObjDict* const restrict dict, const size_t index, const char* restrict key_name, CYPDF_Object* const restrict value);

CYPDF_Object* CYPDF_DictGetValueName(CYPDF_ObjDict* const restrict dict, const char key_name[restrict static 1]);

CYPDF_Object* CYPDF_DictGetValueIndex(CYPDF_ObjDict* const restrict dict, const size_t index) ;



#endif /* CYPDF_DICT_H */
