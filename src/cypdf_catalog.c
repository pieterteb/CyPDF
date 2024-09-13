#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cypdf_catalog.h"
#include "cypdf_consts.h"
#include "cypdf_dict.h"
#include "cypdf_mmgr.h"
#include "cypdf_name.h"
#include "cypdf_object.h"
#include "cypdf_pages.h"



CYPDF_ObjCatalog* CYPDF_NewCatalog(CYPDF_MMgr* const mmgr, CYPDF_ObjPNode* const pages) {
    CYPDF_ObjCatalog* catalog = (CYPDF_ObjCatalog*)CYPDF_GetMem(mmgr, sizeof(CYPDF_ObjCatalog));

    if (catalog) {
        CYPDF_InitHeader(catalog, CYPDF_OCLASS_CATALOG);
        catalog->pages = pages;
        catalog->dict = CYPDF_NewDict(mmgr);

        if (catalog->dict) {
            CYPDF_ObjName* type = CYPDF_NewName(mmgr, "Catalog");
            CYPDF_DictAppend(mmgr, catalog->dict, CYPDF_TYPE_NAME, type);
            CYPDF_DictAppend(mmgr, catalog->dict, "Pages", pages);
        }
    }

    return catalog;
}

void CYPDF_PrintCatalog(FILE* restrict fp, const CYPDF_Object* const obj) {
    if (fp && obj) {
        CYPDF_ObjCatalog* catalog = (CYPDF_ObjCatalog*)obj;
        CYPDF_PrintObjDirect(fp, catalog->dict);
    }
}

void CYPDF_FreeCatalog(CYPDF_Object* obj) {
    if (obj) {
        CYPDF_ObjCatalog* catalog = (CYPDF_ObjCatalog*)obj;

        free(catalog);
    }
}
