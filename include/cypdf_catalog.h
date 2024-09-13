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

    CYPDF_ObjPNode* pages;

    CYPDF_ObjDict*  dict;
} CYPDF_ObjCatalog;


CYPDF_ObjCatalog* CYPDF_NewCatalog(CYPDF_MMgr* const mmgr, CYPDF_ObjPNode* const pages);

void CYPDF_PrintCatalog(FILE* restrict fp, const CYPDF_Object* const obj);

void CYPDF_FreeCatalog(CYPDF_Object* obj);



#endif /* CYPDF_CATALOG_H */
