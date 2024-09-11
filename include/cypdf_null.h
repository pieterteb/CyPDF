#ifndef CYPDF_NULL_H
#define CYPDF_NULL_H


#include <stdbool.h>
#include <stdio.h>

#include "cypdf_object.h"



#define CYPDF_PRINT_NULL            CYPDF_PrintNull
#define CYPDF_FREE_NULL             CYPDF_FreeNull


typedef struct CYPDF_ObjNull {
    CYPDF_ObjHeader header;
} CYPDF_ObjNull;


/**
 * @brief Creates new CYPDF_ObjNull.
 * 
 * @param ID 
 * @param indirect 
 * @return CYPDF_ObjNull* | Returns NULL if object creation fails.
 */
CYPDF_ObjNull* CYPDF_NewNull(bool indirect);

/**
 * @brief Writes obj to fp.
 * 
 * @param fp Stream to be written to.
 * @param obj 
 */
void CYPDF_PrintNull(FILE* fp, CYPDF_Object* obj __attribute_maybe_unused__);

/**
 * @brief Frees NULL. Does nothing if obj is NULL.
 * 
 * @param obj 
 */
void CYPDF_FreeNull(CYPDF_Object* obj);



#endif /* CYPDF_NULL_H */
