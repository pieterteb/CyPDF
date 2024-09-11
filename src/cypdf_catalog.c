#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cypdf_catalog.h"
#include "cypdf_consts.h"
#include "cypdf_dict.h"
#include "cypdf_name.h"
#include "cypdf_object.h"
#include "cypdf_pages.h"



CYPDF_ObjCatalog* CYPDF_NewCatalog(bool indirect, CYPDF_ObjPNode* pages) {
    CYPDF_ObjCatalog* catalog = (CYPDF_ObjCatalog*)CYPDF_NewObj(indirect, CYPDF_OCLASS_CATALOG);
    if (catalog) {
        catalog->dict = CYPDF_NewDict(CYPDF_TRUE);
        if (catalog->dict) {
            /* The type of PDF object that this dictionary describes. */
            CYPDF_ObjName* type = CYPDF_NewName(CYPDF_FALSE, "Catalog");
            CYPDF_DictAppend(catalog->dict, CYPDF_TYPE_NAME, type);

            /* The page tree node that is the root of the document’s page tree. */
            CYPDF_DictAppend(catalog->dict, "Pages", pages);
        }
    }

    return catalog;
}

void CYPDF_PrintCatalog(FILE* fp, CYPDF_Object* obj) {
    if (fp == NULL || obj == NULL) {
        return;
    }

    CYPDF_ObjCatalog* catalog = (CYPDF_ObjCatalog*)obj;
    CYPDF_PrintObjDirect(fp, catalog->dict);
}

void CYPDF_FreeCatalog(CYPDF_Object* obj) {
    if (obj) {
        CYPDF_ObjCatalog* catalog = (CYPDF_ObjCatalog*)obj;
        CYPDF_FreeObj(catalog->dict, CYPDF_FALSE);
        free(catalog);
    }
}
