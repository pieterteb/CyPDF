#ifndef CYPDF_NAME_H
#define CYPDF_NAME_H


#include <stdbool.h>
#include <stdio.h>

#include "cypdf_mmgr.h"
#include "cypdf_object.h"
#include "cypdf_types.h"



#define CYPDF_TYPE_NAME                 "Type"


#define CYPDF_PRINT_NAME                CYPDF_PrintName
#define CYPDF_FREE_NAME                 CYPDF_FreeName


#define CYPDF_MAX_NAME_LEN              128


typedef struct CYPDF_ObjName {
    CYPDF_ObjHeader header;
    char            val[CYPDF_MAX_NAME_LEN + 1];
} CYPDF_ObjName;


CYPDF_ObjName* CYPDF_NewName(CYPDF_MMgr* const mmgr, char val[restrict static 1]);

void CYPDF_PrintName(FILE* restrict fp, const CYPDF_Object* const obj);

void CYPDF_FreeName(CYPDF_Object* obj);



#endif /* CYPDF_NAME_H */
