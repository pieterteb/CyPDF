#ifndef CYPDF_NULL_H
#define CYPDF_NULL_H


#include "cypdf_memmgr.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_types.h"



#define CYPDF_FREE_NULL     CYPDF_FreeNull
#define CYPDF_PRINT_NULL    CYPDF_PrintNull


typedef struct CYPDF_ObjNull {
    CYPDF_ObjHeader header;
} CYPDF_ObjNull;


CYPDF_ObjNull* CYPDF_NewNull(CYPDF_MemMgr* const restrict memmgr);

void CYPDF_FreeNull(CYPDF_Object* obj);

void CYPDF_PrintNull(CYPDF_Channel* const restrict channel, const CYPDF_Object* const restrict obj __attribute_maybe_unused__);



#endif /* CYPDF_NULL_H */
