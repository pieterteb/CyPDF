#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cypdf_pages.h"
#include "cypdf_array.h"
#include "cypdf_consts.h"
#include "cypdf_dict.h"
#include "cypdf_name.h"
#include "cypdf_null.h"
#include "cypdf_number.h"
#include "cypdf_object.h"
#include "cypdf_stream.h"
#include "cypdf_types.h"



CYPDF_ObjPage* CYPDF_NewPage(bool indirect, CYPDF_ObjPNode* parent, int page_number, CYPDF_Rect mediabox) {
    CYPDF_ObjPage* page = (CYPDF_ObjPage*)CYPDF_NewObj(indirect, CYPDF_OCLASS_PAGE);
    if (page) {
        page->page_number = page_number;
        page->parent = parent;
        page->resources = CYPDF_NewDict(CYPDF_FALSE);
        page->mediabox = CYPDF_ArrayFromRect(mediabox, CYPDF_FALSE);
        page->contents = CYPDF_NewArray(CYPDF_FALSE);

        page->dict = CYPDF_NewDict(CYPDF_FALSE);
        if (page->dict) {
            /* The type of the PDF object that this dictionary describes. */
            CYPDF_ObjName* type = CYPDF_NewName(CYPDF_FALSE, "Page");
            CYPDF_DictAppend(page->dict, CYPDF_TYPE_NAME, type);
        }
    }

    return page;
}

CYPDF_ObjPNode* CYPDF_NewPNode(bool indirect, CYPDF_ObjPNode* parent) {
    CYPDF_ObjPNode* page_node = (CYPDF_ObjPNode*)CYPDF_NewObj(indirect, CYPDF_OCLASS_PNODE);
    if (page_node) {
        page_node->parent = parent;
        page_node->kids = CYPDF_NewArray(CYPDF_FALSE);
        page_node->leaf_count = 0;

        page_node->dict = CYPDF_NewDict(CYPDF_FALSE);
        if (page_node->dict) {
            /* The type of the PDF object that this dictionary describes. */
            CYPDF_ObjName* type = CYPDF_NewName(CYPDF_FALSE, "Pages");
            CYPDF_DictAppend(page_node->dict, CYPDF_TYPE_NAME, type);
        }
    }

    return page_node;
}

CYPDF_ObjPage* CYPDF_AddPage(CYPDF_ObjPNode* page_tree, CYPDF_Rect mediabox) {
    CYPDF_ObjPage* page = CYPDF_NewPage(CYPDF_TRUE, page_tree, page_tree->leaf_count + 1, mediabox);

    if (page) {
        CYPDF_ArrayAppend(page_tree->kids, page);
        ++page_tree->leaf_count;
    }

    return page;
}

CYPDF_ObjPage* CYPDF_PageAtNumber(CYPDF_ObjPNode* page_tree, int page_number) {
    if (page_tree) {
        CYPDF_ObjArray* kids = page_tree->kids;
        if ((size_t)page_number > kids->obj_count) {
            return NULL;
        }

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

void CYPDF_PageAddContent(CYPDF_ObjPage* page, CYPDF_ObjStream* stream) {
    if (stream && page) {
        /* The contents entry in the page dictionary can only be of type stream and array. As of now only array has been implemented. */

        CYPDF_ArrayAppend(page->contents, stream);
    }
}

void CYPDF_PrintPage(FILE* fp, CYPDF_Object* obj) {
    if (fp == NULL || obj == NULL) {
        return;
    }

    CYPDF_ObjPage* page = (CYPDF_ObjPage*)obj;

    CYPDF_DictAppend(page->dict, "Parent", page->parent);
    // if (page->resources->count) {
        CYPDF_DictAppend(page->dict, "Resources", page->resources); /* If no resources are present, they are inherited from parent. If no resources are required, this should be an empty dictionary. */
    // }
    CYPDF_DictAppend(page->dict, "MediaBox", page->mediabox);
    if (page->contents->obj_count) {
        CYPDF_DictAppend(page->dict, "Contents", page->contents);
    }

    CYPDF_PrintObjDirect(fp, page->dict);
}

void CYPDF_PrintPNode(FILE* fp, CYPDF_Object* obj) {
    if (fp == NULL || obj == NULL) {
        return;
    }

    CYPDF_ObjPNode* page_node = (CYPDF_ObjPNode*)obj;

    if (page_node->parent) {
        CYPDF_DictAppend(page_node->dict, "Parent", page_node->parent);
    }
    CYPDF_DictAppend(page_node->dict, "Kids", page_node->kids);
    CYPDF_ObjNumber* leaf_count = CYPDF_NewNumber(CYPDF_FALSE, page_node->leaf_count);
    CYPDF_DictAppend(page_node->dict, "Count", leaf_count);

    CYPDF_PrintObjDirect(fp, page_node->dict);
}

void CYPDF_FreePage(CYPDF_Object* obj) {
    if (obj) {
        CYPDF_ObjPage* page = (CYPDF_ObjPage*)obj;
    
        CYPDF_FreeObj(page->parent, CYPDF_FALSE);
        CYPDF_FreeObj(page->resources, CYPDF_FALSE);
        CYPDF_FreeObj(page->mediabox, CYPDF_FALSE);
        CYPDF_FreeObj(page->contents, CYPDF_FALSE);
        CYPDF_FreeObj(page->dict, CYPDF_FALSE);

        free(page);
    }
}

void CYPDF_FreePNode(CYPDF_Object* obj) {
    if (obj) {
        CYPDF_ObjPNode* page_node = (CYPDF_ObjPNode*)obj;

        CYPDF_FreeObj(page_node->parent, CYPDF_FALSE);
        CYPDF_FreeObj(page_node->kids, CYPDF_FALSE);
        CYPDF_FreeObj(page_node->dict, CYPDF_FALSE);

        free(page_node);
    }
}
