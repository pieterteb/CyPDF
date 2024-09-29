#ifndef CYPDF_PAGES_H
#define CYPDF_PAGES_H


#include "cypdf_dict.h"
#include "cypdf_memmgr.h"
#include "cypdf_stream.h"
#include "cypdf_types.h"



typedef CYPDF_ObjDict CYPDF_ObjPage;
typedef CYPDF_ObjDict CYPDF_ObjPageNode;


CYPDF_ObjPage* CYPDF_NewPage(CYPDF_MemMgr* const restrict memmgr, CYPDF_ObjPageNode* const restrict parent, const CYPDF_Rect media_box);

CYPDF_ObjPageNode* CYPDF_NewPageNode(CYPDF_MemMgr* const restrict memmgr, CYPDF_ObjPageNode* const restrict parent);


void CYPDF_PageNodeAddKid(CYPDF_ObjPageNode* const restrict page_node, CYPDF_ObjPage* const restrict page);

void CYPDF_PageAddContent(CYPDF_ObjPage* const restrict page, CYPDF_ObjStream* const restrict stream);



#endif /* CYPDF_PAGES_H */
