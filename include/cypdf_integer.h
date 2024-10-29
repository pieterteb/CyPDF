#ifndef CYPDF_INTEGER_H
#define CYPDF_INTEGER_H


#include "cypdf_memory.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_types.h"



#define CYPDF_PRINT_INTEGER CYPDF_PrintInteger


typedef struct CYPDF_ObjInteger {
    CYPDF_ObjHeader header;

    int             value;
} CYPDF_ObjInteger;


CYPDF_ObjInteger* CYPDF_NewInteger(CYPDF_MemMgr* const restrict memmgr, const int value);

void CYPDF_FreeInteger(CYPDF_Object* obj);

void CYPDF_PrintInteger(CYPDF_Channel* const restrict channel, const CYPDF_Object* const obj);


void CYPDF_IntegerSetValue(CYPDF_ObjInteger* const restrict integer, const int value);

int CYPDF_IntegerGetValue(const CYPDF_ObjInteger* const restrict integer);



#endif /* CYPDF_INTEGER_H */
