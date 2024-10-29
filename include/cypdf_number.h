#ifndef CYPDF_NUMBER_H
#define CYPDF_NUMBER_H


#include "cypdf_memory.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_types.h"



#define CYPDF_PRINT_NUMBER  CYPDF_PrintNumber


typedef struct CYPDF_ObjNumber {
    CYPDF_ObjHeader header;

    float           value;
} CYPDF_ObjNumber;


CYPDF_ObjNumber* CYPDF_NewNumber(CYPDF_MemMgr* const restrict memmgr, const float value);

void CYPDF_PrintNumber(CYPDF_Channel* const restrict channel, const CYPDF_Object* const obj);


void CYPDF_NumberSetValue(CYPDF_ObjNumber* const restrict number, const float value);

float CYPDF_NumberGetValue(const CYPDF_ObjNumber* const number);



#endif /* CYPDF_NUMBER_H */
