#include <stdio.h>
#include <stdlib.h>

#include "cypdf_doc.h"
#include "cypdf_catalog.h"
#include "cypdf_consts.h"
#include "cypdf_log.h"
#include "cypdf_memmgr.h"
#include "cypdf_null.h"
#include "cypdf_object.h"
#include "cypdf_pages.h"
#include "cypdf_path_operators.h"
#include "cypdf_print.h"
#include "cypdf_time.h"
#include "cypdf_trailer.h"
#include "cypdf_version.h"
#include "cypdf_xref.h"



CYPDF_Doc* CYPDF_NewDoc(void) {
    CYPDF_TRACE;

    CYPDF_Doc* pdf = CYPDF_malloc(sizeof(CYPDF_Doc));

    if (pdf) {
        pdf->memmgr = CYPDF_NewMemMgr(CYPDF_FreeObj);

        pdf->page_root = CYPDF_NewPageNode(pdf->memmgr, NULL);   /* Page root. */
        pdf->catalog = CYPDF_NewCatalog(pdf->memmgr, pdf->page_root);

        char* creation_date = CYPDF_Date();
        pdf->info = CYPDF_NewInfo(pdf->memmgr, "Test", "Alice & Bob", "Test", "CyPDF", "CyProducer", creation_date);
        free(creation_date);

        pdf->objs = NULL;
        pdf->obj_count = 0;
        pdf->offsets = NULL;

        CYPDF_DocAppendObject(pdf, pdf->catalog);
        CYPDF_DocAppendObject(pdf, pdf->page_root);
        CYPDF_DocAppendObject(pdf, pdf->info);
    }

    return pdf;
}

void CYPDF_FreeDoc(CYPDF_Doc* pdf) {
    CYPDF_TRACE;

    if (pdf) {
        CYPDF_DestroyMemMgr(pdf->memmgr);

        free(pdf->objs);
        free(pdf->offsets);

        free(pdf);
    }
}

void CYPDF_PrintDoc(CYPDF_Doc* const restrict pdf, const char file_path[restrict static 1]) {
    CYPDF_TRACE;

    if (pdf) {
        FILE* fp = fopen(file_path, "wb");
        CYPDF_Channel* file_channel = CYPDF_NewChannel(fp, CYPDF_CHANNEL_FILE);

        /* header */
        CYPDF_ChannelPrintComment(file_channel, CYPDF_PDF_VERSION);
        CYPDF_ChannelPrintNL(file_channel);
        CYPDF_ChannelPrintComment(file_channel, CYPDF_HIVAL_BYTES);
        CYPDF_ChannelPrintNL(file_channel);

        CYPDF_Object** objs = pdf->objs;
        pdf->offsets = CYPDF_malloc(pdf->obj_count * sizeof(pdf->offsets[0]));
        for (size_t i = 0; i < pdf->obj_count; ++i) {
            pdf->offsets[i] = (size_t)CYPDF_Channeltell(file_channel);
            CYPDF_PrintObjDef(file_channel, objs[i]);
        }

        size_t xref_offset = (size_t)CYPDF_Channeltell(file_channel);
        CYPDF_PrintXref(file_channel, pdf);
        CYPDF_PrintTrailer(file_channel, pdf, file_path, xref_offset);

        free(file_channel);
        fclose(fp);
    }
}


void CYPDF_DocAppendObject(CYPDF_Doc* const restrict pdf, CYPDF_Object* const restrict obj) {
    CYPDF_TRACE;

    if (pdf) {
        pdf->objs = CYPDF_realloc(pdf->objs, (pdf->obj_count + 1) * sizeof(CYPDF_Object*));
        pdf->objs[pdf->obj_count] = obj;
        ++pdf->obj_count;

        /* Once an object has been appended to the pdf document, it can receive an object number. */
        ((CYPDF_ObjNull*)obj)->header.obj_num = (unsigned int)(pdf->obj_count & 0x7FFFFF);
        ((CYPDF_ObjNull*)obj)->header.indirect = true;
    }
}

CYPDF_ObjPage* CYPDF_AppendPage(CYPDF_Doc* const restrict pdf) {
    CYPDF_TRACE;

    if (pdf) {
        CYPDF_ObjPage* page =  CYPDF_NewPage(pdf->memmgr, pdf->page_root, CYPDF_A4_MEDIABOX);
        CYPDF_DocAppendObject(pdf, page);

        return page;
    }

    return NULL;
}

void CYPDF_AddPathToPage(CYPDF_Doc* const restrict pdf, CYPDF_ObjPage* const restrict page, const CYPDF_Path* const restrict path) {
    CYPDF_TRACE;

    if (path && pdf) {
        CYPDF_ObjStream* stream = CYPDF_NewStream(pdf->memmgr);

        CYPDF_Channel* channel = CYPDF_NewChannel(stream, CYPDF_CHANNEL_OBJSTREAM);
        CYPDF_PrintPath(channel, path);
        free(channel);

        CYPDF_PageAddContent(page, stream);
        CYPDF_DocAppendObject(pdf, stream);
    }
}
