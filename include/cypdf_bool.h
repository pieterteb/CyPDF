#ifndef CYPDF_BOOL_H
#define CYPDF_BOOL_H


#include <stdbool.h>
#include <stdio.h>

#include "cypdf_mmgr.h"
#include "cypdf_object.h"
#include "cypdf_types.h"



#define CYPDF_PRINT_BOOL            CYPDF_PrintBool
#define CYPDF_FREE_BOOL             CYPDF_FreeBool


typedef struct CYPDF_ObjBool {
    CYPDF_ObjHeader header;
    bool            val;
} CYPDF_ObjBool;


CYPDF_ObjBool* CYPDF_NewBool(CYPDF_MMgr* const mmgr, const bool val);

void CYPDF_PrintBool(FILE* restrict fp, const CYPDF_Object* const obj);

void CYPDF_FreeBool(CYPDF_Object* obj);



#endif /* CYPDF_BOOL_H */
