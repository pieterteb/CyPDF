#include "cypdf_catalog.h"
#include "cypdf_dict.h"
#include "cypdf_dict_parameters.h"
#include "cypdf_memmgr.h"
#include "cypdf_name.h"
#include "cypdf_pages.h"



CYPDF_ObjCatalog* CYPDF_NewCatalog(CYPDF_MemMgr* const restrict memmgr, CYPDF_ObjPageNode* const restrict pages) {
    CYPDF_ObjCatalog* catalog = CYPDF_NewDict(memmgr);

    if (catalog) {
        catalog->header.subclass = CYPDF_OBJ_SUBCLASS_CATALOG;

        CYPDF_DictAppend(catalog, CYPDF_TYPE_K, CYPDF_NewName(catalog->memmgr, CYPDF_CATALOG_TYPE_K));
        CYPDF_DictAppend(catalog, CYPDF_CATALOG_PAGE_ROOT_K, pages);
    }

    return catalog;
}
