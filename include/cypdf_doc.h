#ifndef CYPDF_DOC_H
#define CYPDF_DOC_H


#include <stdint.h>
#include <stdio.h>

#include "cypdf_catalog.h"
#include "cypdf_header.h"
#include "cypdf_info.h"
#include "cypdf_pages.h"
#include "cypdf_path_operators.h"



typedef struct CYPDF_Doc {
    CYPDF_FileHeader*   file_header;

    CYPDF_ObjCatalog*   catalog;
    CYPDF_ObjPNode*     page_tree;
    CYPDF_ObjInfo*      info;
    
    CYPDF_Object**      objs;
    uint32_t	        obj_count;

    size_t*             offsets; /* Byte offsets of the objects in objs. */
} CYPDF_Doc;


/**
 * @brief Creates new CYPDF_Doc.
 * 
 * @return CYPDF_Doc* | Returns NULL if memory allocation fails.
 */
CYPDF_Doc* CYPDF_NewDoc();

/**
 * @brief Append a new page to pdf.
 * 
 * @param pdf 
 */
void CYPDF_AppendPage(CYPDF_Doc* pdf);

void CYPDF_AddPath(CYPDF_Doc* pdf, int page_number, CYPDF_Path* path);

void CYPDF_PrintDoc(CYPDF_Doc* pdf, const char* file_path);

/**
 * @brief Frees pdf. Does nothing if pdf is NULL.
 * 
 * @param pdf 
 */
void CYPDF_FreeDoc(CYPDF_Doc* pdf);



#endif /* CYPDF_DOC_H */
