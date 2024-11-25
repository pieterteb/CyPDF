#include <stdio.h>
#include <stdlib.h>

#include "cypdf_doc.h"
#include "cypdf_array.h"
#include "cypdf_catalog.h"
#include "cypdf_consts.h"
#include "cypdf_dict_parameters.h"
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

static void CYPDF_DocAddObject(CYPDF_Doc* const restrict pdf, CYPDF_Object* const restrict obj);


CYPDF_Doc* CYPDF_NewDoc(void) {
    CYPDF_TRACE;

    CYPDF_Doc* pdf = CYPDF_malloc(sizeof(CYPDF_Doc));

    if (pdf) {
        pdf->obj_memmgr = CYPDF_NewMemMgr(CYPDF_FreeObj);

        pdf->obj_list = CYPF_NewList(100);
        pdf->page_list = CYPF_NewList(10);
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

        CYPDF_FreeList(pdf->obj_list);
        CYPDF_FreeList(pdf->page_list);
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

    CYPDF_List* page_list = pdf->page_list;

    CYPDF_ObjPage* page = NULL;
    CYPDF_Channel* channel = CYPDF_NewChannel(NULL, CYPDF_CHANNEL_OBJSTREAM);
    for (size_t i = 0; i < page_list->element_count; ++i) {
        page = page_list->elements[i];

        CYPDF_ObjStream* stream = CYPDF_NewStream(pdf->obj_memmgr);
        CYPDF_DocAddObject(pdf, stream);
        channel->stream = stream;

        CYPDF_List* graphic_list = page->graphic_list;
        for (size_t j = 0; j < graphic_list->element_count; ++j) {
            CYPDF_PrintGraphic(channel, graphic_list->elements[j]);
            if (j == graphic_list->element_count - 1) {
                break;
            }
            CYPDF_ChannelPrintNL(channel);
        }

        CYPDF_PageAddContent(page, stream);
    }
}


static void CYPDF_DocAddObject(CYPDF_Doc* const restrict pdf, CYPDF_Object* const restrict obj) {
    CYPDF_TRACE;

    if (pdf) {
        CYPFD_ListAppend(pdf->obj_list, obj);

        /* Once an object has been appended to the pdf document, it can receive an object number. */
        ((CYPDF_ObjNull*)obj)->header.obj_num = (unsigned int)(CYPDF_ListLength(pdf->obj_list) & 0x7FFFFF);
        ((CYPDF_ObjNull*)obj)->header.indirect = true;
    }
}

CYPDF_ObjPage* CYPDF_AppendPage(CYPDF_Doc* const restrict pdf, CYPDF_Rect dimensions) {
    CYPDF_TRACE;

    if (pdf) {
        CYPDF_ObjPage* page =  CYPDF_NewPage(pdf->obj_memmgr, pdf->page_root, dimensions);
        CYPDF_DocAddObject(pdf, page);
        CYPFD_ListAppend(pdf->page_list, page);

        return page;
    }

    return NULL;
}
