#include "cypdf_catalog.h"
#include "cypdf_dict.h"
#include "cypdf_dict_parameters.h"
#include "cypdf_log.h"
#include "cypdf_memory.h"
#include "cypdf_name.h"
#include "cypdf_pages.h"



CYPDF_ObjCatalog* CYPDF_NewCatalog(CYPDF_MemMgr* const memmgr, CYPDF_ObjPageNode* const pages) {
    CYPDF_TRACE;

    CYPDF_ObjCatalog* catalog = CYPDF_NewDict(memmgr);

    catalog->header.subclass = CYPDF_OBJ_SUBCLASS_CATALOG;

    CYPDF_DictSetAtIndex(catalog, CYPDF_TYPE_I, CYPDF_TYPE_K, CYPDF_NewName(catalog->memmgr, CYPDF_CATALOG_TYPE_K));
    CYPDF_DictSetAtIndex(catalog, CYPDF_CATALOG_PAGE_ROOT_I, CYPDF_CATALOG_PAGE_ROOT_K, pages);

    return catalog;
}
