#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cypdf_pages.h"
#include "cypdf_array.h"
#include "cypdf_dict.h"
#include "cypdf_graphics_state.h"
#include "cypdf_mmgr.h"
#include "cypdf_name.h"
#include "cypdf_null.h"
#include "cypdf_number.h"
#include "cypdf_object.h"
#include "cypdf_stream.h"
#include "cypdf_types.h"



CYPDF_ObjPage* CYPDF_NewPage(CYPDF_MMgr* const mmgr, CYPDF_ObjPNode* const parent, const int page_number, const CYPDF_Rect mediabox) {
    CYPDF_ObjPage* page = (CYPDF_ObjPage*)CYPDF_GetMem(mmgr, sizeof(CYPDF_ObjPage));

    if (page) {
        CYPDF_InitHeader(page, CYPDF_OCLASS_PAGE);
        page->page_number = page_number;
        page->parent = parent;
        page->resources = CYPDF_NewDict(mmgr);
        page->mediabox = CYPDF_ArrayFromRect(mmgr, mediabox);
        page->contents = CYPDF_NewArray(mmgr);

        page->dict = CYPDF_NewDict(mmgr);
        if (page->dict) {
            CYPDF_ObjName* type = CYPDF_NewName(mmgr, "Page");
            CYPDF_DictAppend(mmgr, page->dict, CYPDF_TYPE_NAME, type);
            CYPDF_DictAppend(mmgr, page->dict, "Parent", page->parent);
            CYPDF_DictAppend(mmgr, page->dict, "Resources", page->resources);
            CYPDF_DictAppend(mmgr, page->dict, "MediaBox", page->mediabox);
            CYPDF_DictAppend(mmgr, page->dict, "Contents", page->contents);
        }

        //page->state = CYPDF_NewGFXState(mmgr);
    }

    return page;
}

CYPDF_ObjPNode* CYPDF_NewPNode(CYPDF_MMgr* const mmgr, CYPDF_ObjPNode* const parent) {
    CYPDF_ObjPNode* pnode = (CYPDF_ObjPNode*)CYPDF_GetMem(mmgr, sizeof(CYPDF_ObjPNode));

    if (pnode) {
        CYPDF_InitHeader(pnode, CYPDF_OCLASS_PNODE);
        pnode->parent = parent;
        pnode->kids = CYPDF_NewArray(mmgr);
        pnode->leaf_count = CYPDF_NewNumber(mmgr, 0);

        pnode->dict = CYPDF_NewDict(mmgr);
        if (pnode->dict) {
            CYPDF_ObjName* type = CYPDF_NewName(mmgr, "Pages");
            CYPDF_DictAppend(mmgr, pnode->dict, CYPDF_TYPE_NAME, type);
            if (parent) {
                CYPDF_DictAppend(mmgr, pnode->dict, "Parent", pnode->parent);
            }
            CYPDF_DictAppend(mmgr, pnode->dict, "Kids", pnode->kids);
            CYPDF_DictAppend(mmgr, pnode->dict, "Count", pnode->leaf_count);
        }
    }

    return pnode;
}

CYPDF_ObjPage* CYPDF_AddPage(CYPDF_MMgr* const mmgr, CYPDF_ObjPNode* const page_tree, const CYPDF_Rect mediabox) {
    CYPDF_ObjPage* page = CYPDF_NewPage(mmgr, page_tree, CYPDF_NumberGetValue(page_tree->leaf_count) + 1, mediabox);

    if (page) {
        CYPDF_ArrayAppend(page_tree->kids, page);
        CYPDF_NumberSetValue(page_tree->leaf_count, CYPDF_NumberGetValue(page_tree->leaf_count) + 1);
    }

    return page;
}

CYPDF_ObjPage* CYPDF_PageAtNumber(const CYPDF_ObjPNode* const page_tree, const int page_number) {
    if (page_tree) {
        if (page_number > CYPDF_NumberGetValue(page_tree->leaf_count)) {
            return NULL;
        }

        CYPDF_ObjArray* kids = page_tree->kids;
        CYPDF_ObjPage* kid = NULL;
        for (size_t i = 0; i < kids->obj_count; ++i) {
            kid = (CYPDF_ObjPage*)kids->objs[i];

            if (kid->page_number == page_number) {
                return kid;
            }
        }
    }

    return NULL;
}

void CYPDF_PageAddContent(CYPDF_ObjPage* const page, CYPDF_ObjStream* const stream) {
    if (stream && page) {
        /* The contents entry in the page dictionary can only be of type stream and array. As of now only array has been implemented. */
        CYPDF_ArrayAppend(page->contents, stream);
    }
}

void CYPDF_PrintPage(FILE* restrict fp, const CYPDF_Object* const obj) {
    if (fp && obj) {
        CYPDF_ObjPage* page = (CYPDF_ObjPage*)obj;

        CYPDF_PrintObjDirect(fp, page->dict);
    }
}

void CYPDF_PrintPNode(FILE* restrict fp, const CYPDF_Object* const obj) {
    if (fp && obj) {
        CYPDF_ObjPNode* page_node = (CYPDF_ObjPNode*)obj;

        CYPDF_PrintObjDirect(fp, page_node->dict);
    }        
}

void CYPDF_FreePage(CYPDF_Object* obj) {
    if (obj) {
        CYPDF_ObjPage* page = (CYPDF_ObjPage*)obj;

        // CYPDF_FreeGFXState(page->state);

        free(page);
    }
}

void CYPDF_FreePNode(CYPDF_Object* obj) {
    if (obj) {
        CYPDF_ObjPNode* page_node = (CYPDF_ObjPNode*)obj;

        free(page_node);
    }
}
