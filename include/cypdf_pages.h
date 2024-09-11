#ifndef CYPDF_PAGES_H
#define CYPDF_PAGES_H


#include <stdbool.h>

#include "cypdf_array.h"
#include "cypdf_dict.h"
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

    CYPDF_ObjPNode* parent;
    CYPDF_ObjDict*  resources;
    CYPDF_ObjArray* mediabox;
    CYPDF_ObjArray* contents;

    CYPDF_ObjDict*  dict;
} CYPDF_ObjPage;


typedef struct CYPDF_ObjPageNode {
    CYPDF_ObjHeader header;

    CYPDF_ObjPNode* parent;
    CYPDF_ObjArray* kids;
    int             leaf_count; /* The number of leaf nodes (page objects) that are descendants of this node within the page tree. */

    CYPDF_ObjDict*  dict;
} CYPDF_ObjPNode;


/**
 * @brief Creates new CYPDF_Obj_Page.
 * 
 * @param indirect 
 * @param ID 
 * @param parent 
 * @param mediabox 
 * @return CYPDF_Obj_Page* | Returns NULL if object creation fails.
 */
CYPDF_ObjPage* CYPDF_NewPage(bool indirect, CYPDF_ObjPNode* parent, int page_number, CYPDF_Rect mediabox);

/**
 * @brief Creates new CYPDF_Obj_PNode.
 * 
 * @param indirect 
 * @param ID 
 * @param parent 
 * @return CYPDF_Obj_PNode* | Returns NULL if object creation fails.
 */
CYPDF_ObjPNode* CYPDF_NewPNode(bool indirect, CYPDF_ObjPNode* parent);

/**
 * @brief Adds a new page to page_tree.
 * 
 * @param tree_root 
 * @param ID 
 * @param mediabox 
 */
CYPDF_ObjPage* CYPDF_AddPage(CYPDF_ObjPNode* page_tree, CYPDF_Rect mediabox);

CYPDF_ObjPage* CYPDF_PageAtNumber(CYPDF_ObjPNode* page_tree, int page_number);

void CYPDF_PageAddContent(CYPDF_ObjPage* page, CYPDF_ObjStream* stream);

/**
 * @brief Writes obj to fp. Does nothing if fp == NULL or obj == NULL.
 * 
 * @param fp 
 * @param obj 
 */
void CYPDF_PrintPage(FILE* fp, CYPDF_Object* obj);

/**
 * @brief Write obj to fp. Does nothing if fp == NULL or obj == NULL.
 * 
 * @param fp 
 * @param obj 
 */
void CYPDF_PrintPNode(FILE* fp, CYPDF_Object* obj);


/**
 * @brief Frees obj. Does nothing if obj is NULL.
 * 
 * @param obj 
 */
void CYPDF_FreePage(CYPDF_Object* obj);

/**
 * @brief Frees obj. Does nothing if obj is NULL.
 * 
 * @param obj 
 */
void CYPDF_FreePNode(CYPDF_Object* obj);



#endif /* CYPDF_PAGES_H */
