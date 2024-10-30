#include "cypdf_pages.h"
#include "cypdf_array.h"
#include "cypdf_dict.h"
#include "cypdf_dict_parameters.h"
#include "cypdf_graphics_state.h"
#include "cypdf_log.h"
#include "cypdf_memory.h"
#include "cypdf_name.h"
#include "cypdf_integer.h"
#include "cypdf_object.h"
#include "cypdf_resource.h"
#include "cypdf_stream.h"
#include "cypdf_types.h"



static void CYPDF_PageNodeAddKid(CYPDF_ObjPageNode* const page_node, CYPDF_ObjPage* const page);


CYPDF_ObjPage* CYPDF_NewPage(CYPDF_MemMgr* const memmgr, CYPDF_ObjPageNode* const parent, const CYPDF_Rect media_box) {
    CYPDF_TRACE;

    CYPDF_ObjPage* page = CYPDF_NewDict(memmgr);

    page->header.subclass = CYPDF_OBJ_SUBCLASS_PAGE;

    CYPDF_DictSetAtIndex(page, CYPDF_TYPE_I, CYPDF_TYPE_K, CYPDF_NewName(page->memmgr, CYPDF_PAGE_TYPE_K));
    CYPDF_DictSetAtIndex(page, CYPDF_PAGE_PARENT_I, CYPDF_PAGE_PARENT_K, parent);
    CYPDF_DictSetAtIndex(page, CYPDF_PAGE_RESOURCES_I, CYPDF_PAGE_RESOURCES_K, CYPDF_NewResource(page->memmgr));
    CYPDF_DictSetAtIndex(page, CYPDF_PAGE_MEDIABOX_I, CYPDF_PAGE_MEDIABOX_K, CYPDF_ArrayFromRect(page->memmgr, media_box));
    CYPDF_DictSetAtIndex(page, CYPDF_PAGE_CONTENTS_I, CYPDF_PAGE_CONTENTS_K, CYPDF_NewArray(page->memmgr));

    CYPDF_PageNodeAddKid(parent, page);

    return page;
}

CYPDF_ObjPageNode* CYPDF_NewPageNode(CYPDF_MemMgr* const memmgr, CYPDF_ObjPageNode* const parent) {
    CYPDF_TRACE;

    CYPDF_ObjPageNode* page_node = CYPDF_NewDict(memmgr);

    page_node->header.subclass = CYPDF_OBJ_SUBCLASS_PAGE_NODE;

    CYPDF_DictSetAtIndex(page_node, CYPDF_TYPE_I, CYPDF_TYPE_K, CYPDF_NewName(page_node->memmgr, CYPDF_PAGE_NODE_TYPE_K));
    if (parent) {
        CYPDF_DictSetAtIndex(page_node, CYPDF_PAGE_NODE_PARENT_I, CYPDF_PAGE_NODE_PARENT_K, parent);
    }
    CYPDF_DictSetAtIndex(page_node, CYPDF_PAGE_NODE_KIDS_I, CYPDF_PAGE_NODE_KIDS_K, CYPDF_NewArray(page_node->memmgr));
    CYPDF_DictSetAtIndex(page_node, CYPDF_PAGE_NODE_COUNT_I, CYPDF_PAGE_NODE_COUNT_K, CYPDF_NewInteger(page_node->memmgr, 0));

    return page_node;
}


static void CYPDF_PageNodeAddKid(CYPDF_ObjPageNode* const page_node, CYPDF_ObjPage* const page) {
    CYPDF_TRACE;

    if (page_node && page) {
        CYPDF_ObjArray* kids = CYPDF_DictValueAtIndex(page_node, CYPDF_PAGE_NODE_KIDS_I);
        CYPDF_ArrayAppend(kids, page);
        CYPDF_ObjInteger* leaf_count = CYPDF_DictValueAtIndex(page_node, CYPDF_PAGE_NODE_COUNT_I);
        CYPDF_IntegerSetValue(leaf_count, CYPDF_IntegerGetValue(leaf_count) + 1);
    }
}

void CYPDF_PageAddContent(CYPDF_ObjPage* const page, CYPDF_ObjStream* const stream) {
    CYPDF_TRACE;

    if (stream && page) {
        CYPDF_ObjArray* contents = CYPDF_DictValueAtIndex(page, CYPDF_PAGE_CONTENTS_I);
        CYPDF_ArrayAppend(contents, stream);
    }
}


void CYPDF_PageSetResources(CYPDF_ObjPage* const page, CYPDF_ObjResource* const resources) {
    CYPDF_TRACE;

    if (page) {
        CYPDF_DictSetAtIndex(page, CYPDF_PAGE_RESOURCES_I, CYPDF_PAGE_RESOURCES_K, resources);
    }
}
