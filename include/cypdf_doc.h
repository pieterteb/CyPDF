#ifndef CYPDF_DOC_H
#define CYPDF_DOC_H


#include <stdint.h>
#include <stdio.h>

#include "cypdf_catalog.h"
#include "cypdf_header.h"
#include "cypdf_info.h"
#include "cypdf_mmgr.h"
#include "cypdf_pages.h"
#include "cypdf_path_operators.h"



typedef struct CYPDF_Doc {
    CYPDF_FileHeader*   file_header;

    CYPDF_MMgr*         obj_mmgr;

    CYPDF_ObjCatalog*   catalog;
    CYPDF_ObjPNode*     page_tree;
    CYPDF_ObjInfo*      info;
    
    CYPDF_Object**      objs;       /* Indirect objects. */
    uint32_t	        obj_count;  /* Number of indirect objects. */

    size_t*             offsets; /* Byte offsets of the objects in objs. */
} CYPDF_Doc;


CYPDF_Doc* CYPDF_NewDoc(void);

void CYPDF_AppendPage(CYPDF_Doc* const pdf);

void CYPDF_AddPath(CYPDF_Doc* const pdf, const int page_number, const CYPDF_Path* const path);

void CYPDF_PrintDoc(CYPDF_Doc* const pdf, const char file_path[restrict static 1]);

void CYPDF_FreeDoc(CYPDF_Doc* pdf);



#endif /* CYPDF_DOC_H */
