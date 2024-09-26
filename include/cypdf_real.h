#ifndef CYPDF_REAL_H
#define CYPDF_REAL_H


#include <stdbool.h>
#include <stdio.h>

#include "cypdf_mmgr.h"
#include "cypdf_object.h"
#include "cypdf_types.h"



#define CYPDF_PRINT_REAL                CYPDF_PrintReal
#define CYPDF_FREE_REAL                 CYPDF_FreeReal


typedef struct CYPDF_ObjReal {
    CYPDF_ObjHeader header;
    float           value;
} CYPDF_ObjReal;


CYPDF_ObjReal* CYPDF_NewReal(CYPDF_MMgr* const mmgr, const float value);

void CYPDF_RealSetValue(CYPDF_ObjReal* const real, const float value);

float CYPDF_RealGetValue(const CYPDF_ObjReal* const real);

void CYPDF_PrintReal(FILE* restrict fp, const CYPDF_Object* const obj);

void CYPDF_FreeReal(CYPDF_Object* obj);



#endif /* CYPDF_REAL_H */
