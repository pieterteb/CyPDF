#ifndef CYPDF_NULL_H
#define CYPDF_NULL_H


#include <stdbool.h>
#include <stdio.h>

#include "cypdf_mmgr.h"
#include "cypdf_object.h"
#include "cypdf_types.h"



#define CYPDF_PRINT_NULL            CYPDF_PrintNull
#define CYPDF_FREE_NULL             CYPDF_FreeNull


typedef struct CYPDF_ObjNull {
    CYPDF_ObjHeader header;
} CYPDF_ObjNull;


CYPDF_ObjNull* CYPDF_New_Null(CYPDF_MMgr* const mmgr);

void CYPDF_PrintNull(FILE* restrict fp, const CYPDF_Object* const obj __attribute_maybe_unused__);

void CYPDF_FreeNull(CYPDF_Object* obj);



#endif /* CYPDF_NULL_H */
