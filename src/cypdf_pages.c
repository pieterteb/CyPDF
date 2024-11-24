#include <stdlib.h>

#include "cypdf_pages.h"
#include "cypdf_array.h"
#include "cypdf_dict.h"
#include "cypdf_dict_parameters.h"
#include "cypdf_graphics.h"
#include "cypdf_graphics_state.h"
#include "cypdf_integer.h"
#include "cypdf_log.h"
#include "cypdf_memory.h"
#include "cypdf_name.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_resource.h"
#include "cypdf_stream.h"
#include "cypdf_text.h"
#include "cypdf_types.h"



static void CYPDF_PageNodeAddKid(CYPDF_ObjPageNode* const page_node, CYPDF_ObjPage* const page);


CYPDF_ObjPage* CYPDF_NewPage(CYPDF_MemMgr* const memmgr, CYPDF_ObjPageNode* const parent, const CYPDF_Rect media_box) {
    CYPDF_TRACE;

    CYPDF_ObjPage* page = (CYPDF_ObjPage*)CYPDF_GetMem(memmgr, sizeof(CYPDF_ObjPage));

    page->header.class = CYPDF_OBJ_CLASS_PAGE;

    page->dict = CYPDF_NewDict(memmgr);
    CYPDF_ObjDict* page_dict = page->dict;
    page_dict->header.subclass = CYPDF_OBJ_SUBCLASS_PAGE;

    CYPDF_DictSetAtIndex(page_dict, CYPDF_TYPE_I, CYPDF_TYPE_K, CYPDF_NewName(page_dict->memmgr, CYPDF_PAGE_TYPE_K));
    CYPDF_DictSetAtIndex(page_dict, CYPDF_PAGE_PARENT_I, CYPDF_PAGE_PARENT_K, parent);
    CYPDF_DictSetAtIndex(page_dict, CYPDF_PAGE_RESOURCE_I, CYPDF_PAGE_RESOURCE_K, CYPDF_NewResource(page_dict->memmgr));
    CYPDF_DictSetAtIndex(page_dict, CYPDF_PAGE_MEDIABOX_I, CYPDF_PAGE_MEDIABOX_K, CYPDF_ArrayFromRect(page_dict->memmgr, media_box));
    CYPDF_DictSetAtIndex(page_dict, CYPDF_PAGE_CONTENTS_I, CYPDF_PAGE_CONTENTS_K, CYPDF_NewArray(page_dict->memmgr));

    page->graphic_list = CYPF_NewList(100);

    CYPDF_PageNodeAddKid(parent, page);

    return page;
}

void CYPDF_FreePage(CYPDF_Object* obj) {
    CYPDF_TRACE;

    CYPDF_ObjPage* page = (CYPDF_ObjPage*)obj;

    CYPDF_FreeObj(page->dict);
    CYPDF_FreeList(page->graphic_list);

    free(page);
}

void CYPDF_PrintPage(CYPDF_Channel* const channel, const CYPDF_Object* obj) {
    CYPDF_TRACE;

    CYPDF_ObjPage* page = (CYPDF_ObjPage*)obj;
    CYPDF_PrintObjDirect(channel, page->dict);
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
        CYPDF_ObjArray* contents = CYPDF_DictValueAtIndex(page->dict, CYPDF_PAGE_CONTENTS_I);
        CYPDF_ArrayAppend(contents, stream);
    }
}

void CYPDF_PageAddGraphic(CYPDF_ObjPage* const page, CYPDF_Graphic* const graphic) {
    CYPDF_TRACE;

    CYPFD_ListAppend(page->graphic_list, graphic);
}

void CYPDF_PageAddText(CYPDF_ObjPage* const page, CYPDF_Text* const text) {
    CYPDF_TRACE;

    CYPDF_PageAddGraphic(page, text);
}

void CYPDF_PageSetResources(CYPDF_ObjPage* const page, CYPDF_ObjResource* const resources) {
    CYPDF_TRACE;

    if (page) {
        CYPDF_DictSetAtIndex(page->dict, CYPDF_PAGE_RESOURCE_I, CYPDF_PAGE_RESOURCE_K, resources);
    }
}
