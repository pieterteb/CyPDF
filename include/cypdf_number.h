#ifndef CYPDF_NUMBER_H
#define CYPDF_NUMBER_H


#include <stdbool.h>
#include <stdio.h>

#include "cypdf_mmgr.h"
#include "cypdf_object.h"
#include "cypdf_types.h"



#define CYPDF_PRINT_NUMBER              CYPDF_PrintNumber
#define CYDPF_FREE_NUMBER               CYPDF_FreeNumber


typedef struct CYPDF_ObjNumber {
    CYPDF_ObjHeader header;
    int             val;
} CYPDF_ObjNumber;


CYPDF_ObjNumber* CYPDF_NewNumber(CYPDF_MMgr* const mmgr, const int val);

void CYPDF_SetNumber(CYPDF_ObjNumber* const number, const int val);

int CYPDF_GetNumber(const CYPDF_ObjNumber* const number);

void CYPDF_PrintNumber(FILE* restrict fp, const CYPDF_Object* const obj);

void CYPDF_FreeNumber(CYPDF_Object* obj);



#endif /* CYPDF_NUMBER_H */
