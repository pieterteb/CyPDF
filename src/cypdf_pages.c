#include "cypdf_pages.h"
#include "cypdf_array.h"
#include "cypdf_dict.h"
#include "cypdf_dict_parameters.h"
#include "cypdf_memmgr.h"
#include "cypdf_name.h"
#include "cypdf_integer.h"
#include "cypdf_object.h"
#include "cypdf_stream.h"
#include "cypdf_types.h"



CYPDF_ObjPage* CYPDF_NewPage(CYPDF_MemMgr* const restrict memmgr, CYPDF_ObjPageNode* const restrict parent, const CYPDF_Rect media_box) {
    CYPDF_ObjPage* page = CYPDF_NewDict(memmgr);

    if (page) {
        page->header.subclass = CYPDF_OBJ_SUBCLASS_PAGE;

        CYPDF_DictAppend(page, CYPDF_TYPE_K, CYPDF_NewName(page->memmgr, CYPDF_PAGE_TYPE_K));
        CYPDF_DictAppend(page, CYPDF_PAGE_PARENT_K, parent);
        CYPDF_DictAppend(page, CYPDF_PAGE_RESOURCES_K, CYPDF_NewDict(page->memmgr));
        CYPDF_DictAppend(page, CYPDF_PAGE_MEDIABOX_K, CYPDF_ArrayFromRect(page->memmgr, media_box));
        CYPDF_DictAppend(page, CYPDF_PAGE_CONTENTS_K, CYPDF_NewArray(page->memmgr));

        CYPDF_PageNodeAddKid(parent, page);
    }

    return page;
}

CYPDF_ObjPageNode* CYPDF_NewPageNode(CYPDF_MemMgr* const restrict memmgr, CYPDF_ObjPageNode* const restrict parent) {
    CYPDF_ObjPageNode* page_node = CYPDF_NewDict(memmgr);

    if (page_node) {
        page_node->header.subclass = CYPDF_OBJ_SUBCLASS_PAGE_NODE;

        CYPDF_DictAppend(page_node, CYPDF_TYPE_K, CYPDF_NewName(page_node->memmgr, CYPDF_PAGE_NODE_TYPE_K));
        if (parent) {
            CYPDF_DictAppend(page_node, CYPDF_PAGE_NODE_PARENT_K, parent);
        }
        CYPDF_DictAppend(page_node, CYPDF_PAGE_NODE_KIDS, CYPDF_NewArray(page_node->memmgr));
        CYPDF_DictAppend(page_node, CYPDF_PAGE_NODE_COUNT, CYPDF_NewInteger(page_node->memmgr, 0));
    }

    return page_node;
}


void CYPDF_PageNodeAddKid(CYPDF_ObjPageNode* const restrict page_node, CYPDF_ObjPage* const restrict page) {
    if (page_node && page) {
        CYPDF_ObjArray* kids = CYPDF_DictGetValue(page_node, CYPDF_PAGE_NODE_KIDS);
        CYPDF_ArrayAppend(kids, page);
        CYPDF_ObjInteger* leaf_count = CYPDF_DictGetValue(page_node, CYPDF_PAGE_NODE_COUNT);
        CYPDF_IntegerSetValue(leaf_count, CYPDF_IntegerGetValue(leaf_count) + 1);
    }
}

void CYPDF_PageAddContent(CYPDF_ObjPage* const restrict page, CYPDF_ObjStream* const restrict stream) {
    if (stream && page) {
        CYPDF_ObjArray* contents = CYPDF_DictGetValue(page, CYPDF_PAGE_CONTENTS_K);
        CYPDF_ArrayAppend(contents, stream);
    }
}
