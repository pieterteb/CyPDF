#ifndef CYPDF_PAGES_H
#define CYPDF_PAGES_H


#include "cypdf_dict.h"
#include "cypdf_memory.h"
#include "cypdf_resource.h"
#include "cypdf_stream.h"
#include "cypdf_types.h"



typedef CYPDF_ObjDict CYPDF_ObjPage;
typedef CYPDF_ObjDict CYPDF_ObjPageNode;


CYPDF_ObjPage* CYPDF_NewPage(CYPDF_MemMgr* const memmgr, CYPDF_ObjPageNode* const parent, const CYPDF_Rect media_box);

CYPDF_ObjPageNode* CYPDF_NewPageNode(CYPDF_MemMgr* const memmgr, CYPDF_ObjPageNode* const parent);


void CYPDF_PageAddContent(CYPDF_ObjPage* const page, CYPDF_ObjStream* const stream);


void CYPDF_PageSetResources(CYPDF_ObjPage* const page, CYPDF_ObjResource* const resources);



#endif /* CYPDF_PAGES_H */
