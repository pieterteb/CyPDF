#include <stdio.h>
#include <stdlib.h>

#include "cypdf_doc.h"
#include "cypdf_array.h"
#include "cypdf_catalog.h"
#include "cypdf_consts.h"
#include "cypdf_dict_parameters.h"
#include "cypdf_image.h"
#include "cypdf_list.h"
#include "cypdf_log.h"
#include "cypdf_memory.h"
#include "cypdf_null.h"
#include "cypdf_object.h"
#include "cypdf_pages.h"
#include "cypdf_print.h"
#include "cypdf_time.h"
#include "cypdf_trailer.h"
#include "cypdf_types.h"
#include "cypdf_version.h"
#include "cypdf_xref.h"



static void CYPDF_DocConstructContents(CYPDF_Doc* const pdf);


CYPDF_Doc* CYPDF_NewDoc(void) {
    CYPDF_TRACE;

    CYPDF_Doc* pdf = CYPDF_malloc(sizeof(CYPDF_Doc));

    if (pdf) {
        pdf->obj_memmgr = CYPDF_NewMemMgr(CYPDF_FreeObj);
        pdf->graphic_memmgr = CYPDF_NewMemMgr(CYPDF_FreeGraphic);

        pdf->obj_list = CYPF_NewList(100);
        pdf->graphic_list = CYPF_NewList(100);
        pdf->offsets = NULL;

        pdf->page_root = CYPDF_NewPageNode(pdf->obj_memmgr, NULL);   /* Page root. */
        pdf->catalog = CYPDF_NewCatalog(pdf->obj_memmgr, pdf->page_root);

        char* creation_date = CYPDF_Date();
        pdf->info = CYPDF_NewInfo(pdf->obj_memmgr, "Test", "Alice & Bob", "Test", "CyPDF", "CyProducer", creation_date);
        free(creation_date);

        CYPDF_DocAddObject(pdf, pdf->catalog);
        CYPDF_DocAddObject(pdf, pdf->page_root);
        CYPDF_DocAddObject(pdf, pdf->info);
    }

    return pdf;
}

void CYPDF_FreeDoc(CYPDF_Doc* pdf) {
    CYPDF_TRACE;

    if (pdf) {
        CYPDF_DestroyMemMgr(pdf->obj_memmgr);
        CYPDF_DestroyMemMgr(pdf->graphic_memmgr);

        CYPDF_FreeList(pdf->obj_list);
        CYPDF_FreeList(pdf->graphic_list);
        free(pdf->offsets);

        free(pdf);
    }
}

void CYPDF_PrintDoc(CYPDF_Doc* const restrict pdf, const char file_path[restrict static 1]) {
    CYPDF_TRACE;

    if (pdf) {
        FILE* fp = fopen(file_path, "wb");
        CYPDF_Channel* file_channel = CYPDF_NewChannel(fp, CYPDF_CHANNEL_FILE);

        CYPDF_DocConstructContents(pdf);

        /* header */
        CYPDF_ChannelPrintComment(file_channel, CYPDF_PDF_VERSION);
        CYPDF_ChannelPrintNL(file_channel);
        CYPDF_ChannelPrintComment(file_channel, CYPDF_HIVAL_BYTES);
        CYPDF_ChannelPrintNL(file_channel);

        CYPDF_List* obj_list = pdf->obj_list;
        size_t list_length = CYPDF_ListLength(pdf->obj_list);
        pdf->offsets = CYPDF_malloc(list_length * sizeof(size_t));
        for (size_t i = 0; i < list_length; ++i) {
            pdf->offsets[i] = (size_t)CYPDF_Channeltell(file_channel);
            CYPDF_PrintObjDef(file_channel, CYPDF_ListAtIndex(obj_list, i));
        }

        size_t xref_offset = (size_t)CYPDF_Channeltell(file_channel);
        CYPDF_PrintXref(file_channel, pdf);
        CYPDF_PrintTrailer(file_channel, pdf, file_path, xref_offset);

        free(file_channel);
        fclose(fp);
    }
}


static void CYPDF_DocConstructContents(CYPDF_Doc* const pdf) {
    CYPDF_TRACE;

    CYPDF_List* graphic_list = pdf->graphic_list;

    CYPDF_Channel* channel = CYPDF_NewChannel(NULL, CYPDF_CHANNEL_OBJSTREAM);
    for (size_t i = 0; i < graphic_list->element_count; ++i) {
        CYPDF_ObjStream* stream = CYPDF_NewStream(pdf->obj_memmgr);
        CYPDF_DocAddObject(pdf, stream);
        channel->stream = stream;

        CYPDF_Graphic* graphic = CYPDF_ListAtIndex(pdf->graphic_list, i);
        size_t graphic_length = CYPDF_ListLength(graphic->operator_list);
        for (size_t j = 0; j < graphic_length; ++j) {
            CYPDF_Operator* operator = CYPDF_ListAtIndex(graphic->operator_list, j);
            if (operator->type == CYPDF_OPERATOR_XOBJECT) {
                CYPDF_ObjResource* resource = CYPDF_DictValueAtIndex(graphic->display_page, CYPDF_PAGE_RESOURCE_I);
                CYPDF_ObjXObject* xobject = CYPDF_ListAtIndex(operator->operand_list, 0);
                CYPDF_ResourceAddXObject(resource, xobject);
                CYPDF_ListSetAtIndex(operator->operand_list, 0, CYPDF_ResourceGetName(resource, CYPDF_RESOURCE_XOBJECT_I, xobject));
            }
        }

        CYPDF_PrintGraphic(channel, graphic);

        CYPDF_PageAddContent(graphic->display_page, stream);
    }
}


void CYPDF_DocAddObject(CYPDF_Doc* const restrict pdf, CYPDF_Object* const restrict obj) {
    CYPDF_TRACE;

    if (pdf) {
        CYPFD_ListAppend(pdf->obj_list, obj);

        /* Once an object has been appended to the pdf document, it can receive an object number. */
        ((CYPDF_ObjNull*)obj)->header.obj_num = (unsigned int)(CYPDF_ListLength(pdf->obj_list) & 0x7FFFFF);
        ((CYPDF_ObjNull*)obj)->header.indirect = true;
    }
}

void CYPDF_DocAddGraphic(CYPDF_Doc* const pdf, CYPDF_ObjPage* const page, CYPDF_Graphic* const graphic) {
    CYPDF_TRACE;

    CYPFD_ListAppend(pdf->graphic_list, graphic);
    CYPDF_GraphicSetPage(graphic, page);
}

CYPDF_ObjImage* CYPDF_DocAddImage(CYPDF_Doc* restrict const pdf, const char image_path[restrict static 1]) {
    CYPDF_TRACE;

    CYPDF_ObjImage* image = CYPDF_NewImage(pdf->obj_memmgr, image_path);
    CYPDF_DocAddObject(pdf, image);

    return image;
}

CYPDF_ObjPage* CYPDF_AppendPage(CYPDF_Doc* const restrict pdf, CYPDF_Rect dimensions) {
    CYPDF_TRACE;

    if (pdf) {
        CYPDF_ObjPage* page =  CYPDF_NewPage(pdf->obj_memmgr, pdf->page_root, dimensions);
        CYPDF_DocAddObject(pdf, page);

        return page;
    }

    return NULL;
}
