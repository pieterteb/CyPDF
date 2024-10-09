#ifndef CYPDF_DOC_H
#define CYPDF_DOC_H


#include <stddef.h>

#include "cypdf_catalog.h"
#include "cypdf_info.h"
#include "cypdf_memmgr.h"
#include "cypdf_pages.h"
#include "cypdf_path_operators.h"
#include "cypdf_types.h"



typedef struct CYPDF_Doc {
    CYPDF_MemMgr*       memmgr;

    CYPDF_ObjCatalog*   catalog;
    CYPDF_ObjPageNode*  page_root;
    CYPDF_ObjInfo*      info;
    
    CYPDF_Object**      objs;       /* Indirect objects. */
    size_t	            obj_count;  /* Number of indirect objects. */

    size_t*             offsets; /* Byte offsets of the objects in objs. */
} CYPDF_Doc;


CYPDF_Doc* CYPDF_NewDoc(void);

void CYPDF_FreeDoc(CYPDF_Doc* pdf);

void CYPDF_PrintDoc(CYPDF_Doc* const restrict pdf, const char file_path[restrict static 1]);


void CYPDF_DocAppendObject(CYPDF_Doc* const restrict pdf, CYPDF_Object* const restrict obj);

CYPDF_ObjPage* CYPDF_AppendPage(CYPDF_Doc* const restrict pdf);

void CYPDF_AddPathToPage(CYPDF_Doc* const restrict pdf, CYPDF_ObjPage* const restrict page, const CYPDF_Path* const restrict path);



#endif /* CYPDF_DOC_H */
