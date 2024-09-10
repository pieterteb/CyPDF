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



CYPDF_Obj_Page* CYPDF_New_Page(CYPDF_BOOL indirect, CYPDF_Obj_PNode* parent, CYPDF_INT page_number, CYPDF_Rect mediabox) {
    CYPDF_Obj_Page* page = (CYPDF_Obj_Page*)CYPDF_New_Obj(indirect, CYPDF_OCLASS_PAGE);
    if (page) {
        page->page_number = page_number;
        page->parent = parent;
        page->resources = CYPDF_New_Dict(CYPDF_FALSE);
        page->mediabox = CYPDF_Array_From_Rect(mediabox, CYPDF_FALSE);
        page->contents = CYPDF_New_Array(CYPDF_FALSE);

        page->dict = CYPDF_New_Dict(CYPDF_FALSE);
        if (page->dict) {
            /* The type of the PDF object that this dictionary describes. */
            CYPDF_Obj_Name* type = CYPDF_New_Name(CYPDF_FALSE, "Page");
            CYPDF_Dict_Append(page->dict, CYPDF_TYPE_NAME, type);
        }
    }

    return page;
}

CYPDF_Obj_PNode* CYPDF_New_PNode(CYPDF_BOOL indirect, CYPDF_Obj_PNode* parent) {
    CYPDF_Obj_PNode* page_node = (CYPDF_Obj_PNode*)CYPDF_New_Obj(indirect, CYPDF_OCLASS_PNODE);
    if (page_node) {
        page_node->parent = parent;
        page_node->kids = CYPDF_New_Array(CYPDF_FALSE);
        page_node->leaf_count = 0;

        page_node->dict = CYPDF_New_Dict(CYPDF_FALSE);
        if (page_node->dict) {
            /* The type of the PDF object that this dictionary describes. */
            CYPDF_Obj_Name* type = CYPDF_New_Name(CYPDF_FALSE, "Pages");
            CYPDF_Dict_Append(page_node->dict, CYPDF_TYPE_NAME, type);
        }
    }

    return page_node;
}

CYPDF_Obj_Page* CYPDF_Add_Page(CYPDF_Obj_PNode* page_tree, CYPDF_Rect mediabox) {
    CYPDF_Obj_Page* page = CYPDF_New_Page(CYPDF_TRUE, page_tree, page_tree->leaf_count + 1, mediabox);

    if (page) {
        CYPDF_Array_Append(page_tree->kids, page);
        ++page_tree->leaf_count;
    }

    return page;
}

CYPDF_Obj_Page* CYPDF_Page_At_Number(CYPDF_Obj_PNode* page_tree, CYPDF_INT page_number) {
    if (page_tree) {
        CYPDF_Obj_Array* kids = page_tree->kids;
        if ((CYPDF_SIZE)page_number > kids->obj_count) {
            return NULL;
        }

        CYPDF_Obj_Page* kid = NULL;
        for (size_t i = 0; i < kids->obj_count; ++i) {
            kid = (CYPDF_Obj_Page*)kids->objs[i];

            if (kid->page_number == page_number) {
                return kid;
            }
        }
    }

    return NULL;
}

void CYPDF_Page_Add_Content(CYPDF_Obj_Page* page, CYPDF_Obj_Stream* stream) {
    if (stream && page) {
        /* The contents entry in the page dictionary can only be of type stream and array. As of now only array has been implemented. */

        CYPDF_Array_Append(page->contents, stream);
    }
}

void CYPDF_Write_Page(FILE* fp, CYPDF_Object* obj) {
    if (fp == NULL || obj == NULL) {
        return;
    }

    CYPDF_Obj_Page* page = (CYPDF_Obj_Page*)obj;

    CYPDF_Dict_Append(page->dict, "Parent", page->parent);
    // if (page->resources->count) {
        CYPDF_Dict_Append(page->dict, "Resources", page->resources); /* If no resources are present, they are inherited from parent. If no resources are required, this should be an empty dictionary. */
    // }
    CYPDF_Dict_Append(page->dict, "MediaBox", page->mediabox);
    if (page->contents->obj_count) {
        CYPDF_Dict_Append(page->dict, "Contents", page->contents);
    }

    CYPDF_Write_Obj_Direct(fp, page->dict);
}

void CYPDF_Write_PNode(FILE* fp, CYPDF_Object* obj) {
    if (fp == NULL || obj == NULL) {
        return;
    }

    CYPDF_Obj_PNode* page_node = (CYPDF_Obj_PNode*)obj;

    if (page_node->parent) {
        CYPDF_Dict_Append(page_node->dict, "Parent", page_node->parent);
    }
    CYPDF_Dict_Append(page_node->dict, "Kids", page_node->kids);
    CYPDF_Obj_Number* leaf_count = CYPDF_New_Number(CYPDF_FALSE, page_node->leaf_count);
    CYPDF_Dict_Append(page_node->dict, "Count", leaf_count);

    CYPDF_Write_Obj_Direct(fp, page_node->dict);
}

void CYPDF_Free_Page(CYPDF_Object* obj) {
    if (obj) {
        CYPDF_Obj_Page* page = (CYPDF_Obj_Page*)obj;
    
        CYPDF_Free_Obj(page->parent, CYPDF_FALSE);
        CYPDF_Free_Obj(page->resources, CYPDF_FALSE);
        CYPDF_Free_Obj(page->mediabox, CYPDF_FALSE);
        CYPDF_Free_Obj(page->contents, CYPDF_FALSE);
        CYPDF_Free_Obj(page->dict, CYPDF_FALSE);

        free(page);
    }
}

void CYPDF_Free_PNode(CYPDF_Object* obj) {
    if (obj) {
        CYPDF_Obj_PNode* page_node = (CYPDF_Obj_PNode*)obj;

        CYPDF_Free_Obj(page_node->parent, CYPDF_FALSE);
        CYPDF_Free_Obj(page_node->kids, CYPDF_FALSE);
        CYPDF_Free_Obj(page_node->dict, CYPDF_FALSE);

        free(page_node);
    }
}
