#ifndef CYPDF_DOC_H
#define CYPDF_DOC_H


#include <stddef.h>

#include "cypdf_catalog.h"
#include "cypdf_graphics.h"
#include "cypdf_info.h"
#include "cypdf_list.h"
#include "cypdf_memory.h"
#include "cypdf_pages.h"
#include "cypdf_types.h"



typedef struct CYPDF_Doc {
    CYPDF_ObjCatalog*   catalog;
    CYPDF_ObjPageNode*  page_root;
    CYPDF_ObjInfo*      info;
    
    CYPDF_List*         obj_list;       /* Indirect objects. */
    CYPDF_List*         page_list;

    CYPDF_MemMgr*       obj_memmgr;

    size_t*             offsets;        /* Byte offsets of the objects in obj_list. */
} CYPDF_Doc;


CYPDF_Doc* CYPDF_NewDoc(void);

void CYPDF_FreeDoc(CYPDF_Doc* pdf);

void CYPDF_PrintDoc(CYPDF_Doc* const restrict pdf, const char file_path[restrict static 1]);


CYPDF_ObjPage* CYPDF_AppendPage(CYPDF_Doc* const restrict pdf, CYPDF_Rect dimensions);



#endif /* CYPDF_DOC_H */
