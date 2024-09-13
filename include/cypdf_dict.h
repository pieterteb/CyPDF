#ifndef CYPDF_DICT_H
#define CYPDF_DICT_H


#include <stdbool.h>
#include <stdio.h>

#include "cypdf_mmgr.h"
#include "cypdf_name.h"
#include "cypdf_object.h"
#include "cypdf_types.h"



#define CYPDF_PRINT_DICT                CYPDF_PrintDict
#define CYPDF_FREE_DICT                 CYPDF_FreeDict


typedef struct CYPDF_ObjDict {
    CYPDF_ObjHeader header;
    CYPDF_ObjName** keys;
    CYPDF_Object**  values;
    size_t          count;
} CYPDF_ObjDict;


CYPDF_ObjDict* CYPDF_NewDict(CYPDF_MMgr* const mmgr);

void CYPDF_DictAppend(CYPDF_MMgr* const mmgr, CYPDF_ObjDict* const dict, char key_name[restrict static 1], CYPDF_Object* const value);

void CYPDF_PrintDict(FILE* restrict fp, const CYPDF_Object* const obj);

void CYPDF_FreeDict(CYPDF_Object* obj);



#endif /* CYPDF_DICT_H */
