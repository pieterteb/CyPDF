#ifndef CYPDF_CATALOG_H
#define CYPDF_CATALOG_H


#include "cypdf_dict.h"
#include "cypdf_pages.h"



typedef CYPDF_ObjDict CYPDF_ObjCatalog;


CYPDF_ObjCatalog* CYPDF_NewCatalog(CYPDF_MemMgr* const memmgr, CYPDF_ObjPageNode* const pages);



#endif /* CYPDF_CATALOG_H */
