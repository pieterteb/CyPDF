#ifndef CYPDF_BOOL_H
#define CYPDF_BOOL_H


#include <stdbool.h>

#include "cypdf_memmgr.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_types.h"



#define CYPDF_PRINT_BOOL    CYPDF_PrintBool


typedef struct CYPDF_ObjBool {
    CYPDF_ObjHeader header;

    bool            value;
} CYPDF_ObjBool;


CYPDF_ObjBool* CYPDF_NewBool(CYPDF_MemMgr* const restrict memmgr, const bool value);

void CYPDF_PrintBool(CYPDF_Channel* const restrict channel, const CYPDF_Object* const obj);



#endif /* CYPDF_BOOL_H */
