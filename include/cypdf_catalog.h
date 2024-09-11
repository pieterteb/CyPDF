#ifndef CYPDF_CATALOG_H
#define CYPDF_CATALOG_H


#include <stdbool.h>
#include <stdio.h>

#include "cypdf_dict.h"
#include "cypdf_object.h"
#include "cypdf_pages.h"



#define CYPDF_PRINT_CATALOG             CYPDF_PrintCatalog
#define CYPDF_FREE_CATALOG              CYPDF_FreeCatalog


typedef struct CYPDF_ObjCatalog {
    CYPDF_ObjHeader header;
    CYPDF_ObjDict*  dict;
} CYPDF_ObjCatalog;


/**
 * @brief Creates new CYPDF_ObjCatalog.
 * 
 * @param indirect 
 * @param ID 
 * @return CYPDF_ObjCatalog* | Returns NULL if object creation fails.
 */
CYPDF_ObjCatalog* CYPDF_NewCatalog(bool indirect, CYPDF_ObjPNode* pages);

/**
 * @brief Writes obj to fp. Does nothing if fp == NULL or obj == NULL.
 * 
 * @param fp 
 * @param obj 
 */
void CYPDF_PrintCatalog(FILE* fp, CYPDF_Object* obj);

/**
 * @brief Frees obj. Does nothing if obj is NULL.
 * 
 * @param obj 
 */
void CYPDF_FreeCatalog(CYPDF_Object* obj);



#endif /* CYPDF_CATALOG_H */
