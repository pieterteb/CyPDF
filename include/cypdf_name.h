#ifndef CYPDF_NAME_H
#define CYPDF_NAME_H


#include "cypdf_memory.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_types.h"



#define CYPDF_PRINT_NAME    CYPDF_PrintName


#define CYPDF_MAX_NAME_LEN  128


typedef struct CYPDF_ObjName {
    CYPDF_ObjHeader header;

    char            value[CYPDF_MAX_NAME_LEN + 1];
} CYPDF_ObjName;


CYPDF_ObjName* CYPDF_NewName(CYPDF_MemMgr* const restrict memmgr, const char* restrict value);

void CYPDF_PrintName(CYPDF_Channel* const restrict channel, const CYPDF_Object* const obj);



#endif /* CYPDF_NAME_H */
