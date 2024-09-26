#ifndef CYPDF_PAGES_H
#define CYPDF_PAGES_H


#include <stdbool.h>

#include "cypdf_array.h"
#include "cypdf_dict.h"
#include "cypdf_graphics_state.h"
#include "cypdf_mmgr.h"
#include "cypdf_number.h"
#include "cypdf_object.h"
#include "cypdf_stream.h"
#include "cypdf_types.h"



#define CYPDF_PRINT_PAGE                    CYPDF_PrintPage
#define CYPDF_FREE_PAGE                     CYPDF_FreePage

#define CYPDF_PRINT_PNODE                   CYPDF_PrintPNode
#define CYPDF_FREE_PNODE                    CYPDF_FreePNode


typedef struct CYPDF_ObjPageNode CYPDF_ObjPNode;

typedef struct CYPDF_ObjPage {
    CYPDF_ObjHeader header;
    int             page_number;

    CYPDF_GFXState* state;

    CYPDF_ObjPNode* parent;
    CYPDF_ObjDict*  resources;
    CYPDF_ObjArray* mediabox;
    CYPDF_ObjArray* contents;

    CYPDF_ObjDict*  dict;
} CYPDF_ObjPage;


typedef struct CYPDF_ObjPageNode {
    CYPDF_ObjHeader     header;

    CYPDF_ObjPNode*     parent;
    CYPDF_ObjArray*     kids;
    CYPDF_ObjNumber*    leaf_count; /* The number of leaf nodes (page objects) that are descendants of this node within the page tree. */

    CYPDF_ObjDict*      dict;
} CYPDF_ObjPNode;


CYPDF_ObjPage* CYPDF_NewPage(CYPDF_MMgr* const mmgr, CYPDF_ObjPNode* const parent, const int page_number, const CYPDF_Rect mediabox);

CYPDF_ObjPNode* CYPDF_NewPNode(CYPDF_MMgr* const mmgr, CYPDF_ObjPNode* const parent);

CYPDF_ObjPage* CYPDF_AddPage(CYPDF_MMgr* const mmgr, CYPDF_ObjPNode* const page_tree, const CYPDF_Rect mediabox);

CYPDF_ObjPage* CYPDF_PageAtNumber(const CYPDF_ObjPNode* const page_tree, const int page_number);

void CYPDF_PageAddContent(CYPDF_ObjPage* const page, CYPDF_ObjStream* const stream);

void CYPDF_PrintPage(FILE* restrict fp, const CYPDF_Object* const obj);

void CYPDF_PrintPNode(FILE* restrict fp, const CYPDF_Object* const obj);


void CYPDF_FreePage(CYPDF_Object* obj);

void CYPDF_FreePNode(CYPDF_Object* obj);



#endif /* CYPDF_PAGES_H */
