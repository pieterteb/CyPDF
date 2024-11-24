#ifndef CYPDF_PAGES_H
#define CYPDF_PAGES_H


#include "cypdf_dict.h"
#include "cypdf_graphics.h"
#include "cypdf_list.h"
#include "cypdf_memory.h"
#include "cypdf_object.h"
#include "cypdf_resource.h"
#include "cypdf_stream.h"
#include "cypdf_text.h"
#include "cypdf_types.h"



#define CYPDF_FREE_PAGE     CYPDF_FreePage
#define CYPDF_PRINT_PAGE    CYPDF_PrintPage


typedef struct CYPDF_ObjPage {
    CYPDF_ObjHeader header;

    CYPDF_ObjDict*  dict;

    CYPDF_List*     graphic_list;
} CYPDF_ObjPage;

typedef CYPDF_ObjDict CYPDF_ObjPageNode;


CYPDF_ObjPage* CYPDF_NewPage(CYPDF_MemMgr* const memmgr, CYPDF_ObjPageNode* const parent, const CYPDF_Rect media_box);

void CYPDF_FreePage(CYPDF_Object* obj);

void CYPDF_PrintPage(CYPDF_Channel* const channel, const CYPDF_Object* obj);

CYPDF_ObjPageNode* CYPDF_NewPageNode(CYPDF_MemMgr* const memmgr, CYPDF_ObjPageNode* const parent);


void CYPDF_PageAddContent(CYPDF_ObjPage* const page, CYPDF_ObjStream* const stream);

void CYPDF_PageAddGraphic(CYPDF_ObjPage* const page, CYPDF_Graphic* const graphic);

void CYPDF_PageAddText(CYPDF_ObjPage* const page, CYPDF_Text* const text);


void CYPDF_PageSetResources(CYPDF_ObjPage* const page, CYPDF_ObjResource* const resources);



#endif /* CYPDF_PAGES_H */
