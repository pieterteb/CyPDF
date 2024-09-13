#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "cypdf_doc.h"
#include "cypdf_array.h"
#include "cypdf_catalog.h"
#include "cypdf_consts.h"
#include "cypdf_dict.h"
#include "cypdf_header.h"
#include "cypdf_mmgr.h"
#include "cypdf_null.h"
#include "cypdf_object.h"
#include "cypdf_pages.h"
#include "cypdf_path_operators.h"
#include "cypdf_print.h"
#include "cypdf_trailer.h"
#include "cypdf_utils.h"
#include "cypdf_xref.h"



static void CYPDF_DocAppendObject(CYPDF_Doc* const pdf, CYPDF_Object* const obj) {
    if (pdf) {
        pdf->objs = CYPDF_srealloc(pdf->objs, (pdf->obj_count + 1) * sizeof(CYPDF_Object*));
        pdf->objs[pdf->obj_count] = obj;
        ++pdf->obj_count;

        /* Once an object has been appended to the pdf document, it can receive an object number. */
        CYPDF_ObjSetOnum(obj, pdf->obj_count);
        CYPDF_ObjSetIndirect(obj, true);
    }
}

CYPDF_Doc* CYPDF_NewDoc(void) {
    CYPDF_Doc* pdf = CYPDF_smalloc(sizeof(CYPDF_Doc));

    if (pdf) {
        pdf->file_header = CYPDF_NewFileHeader();

        pdf->obj_mmgr = CYPDF_NewMMgr(CYPDF_FreeObj);

        pdf->page_tree = CYPDF_NewPNode(pdf->obj_mmgr, NULL);   /* Page root. */
        pdf->catalog = CYPDF_NewCatalog(pdf->obj_mmgr, pdf->page_tree);

        char* creation_date = CYPDF_GetDate();
        pdf->info = CYPDF_NewInfo(pdf->obj_mmgr, "Test", "Bob", "Test", "CyPDF", "CyProducer", creation_date);
        free(creation_date);

        pdf->objs = NULL;
        pdf->obj_count = 0;
        pdf->offsets = NULL;

        CYPDF_DocAppendObject(pdf, pdf->catalog);
        CYPDF_DocAppendObject(pdf, pdf->page_tree);
        CYPDF_DocAppendObject(pdf, pdf->info);
    }

    return pdf;
}

void CYPDF_AppendPage(CYPDF_Doc* const pdf) {
    CYPDF_ObjPage* page = CYPDF_AddPage(pdf->obj_mmgr, pdf->page_tree, CYPDF_A4_MEDIABOX);
    CYPDF_DocAppendObject(pdf, page);
}

void CYPDF_AddPath(CYPDF_Doc* const pdf, const int page_number, const CYPDF_Path* const path) {
    if (path && pdf) {
        CYPDF_ObjStream* stream = CYPDF_NewStream(pdf->obj_mmgr);
        CYPDF_PrintPathToStream(stream, path);

        CYPDF_ObjPage* page = CYPDF_PageAtNumber(pdf->page_tree, page_number);
        CYPDF_PageAddContent(page, stream);

        CYPDF_DocAppendObject(pdf, stream);
    }
}

void CYPDF_PrintDoc(CYPDF_Doc* const pdf, const char file_path[restrict static 1]) {
    if (pdf) {
        FILE* fp = fopen("../out/test.txt", "wb");

        CYPDF_PrintFileHeader(fp, pdf->file_header);

        CYPDF_Object** objs = pdf->objs;
        pdf->offsets = CYPDF_smalloc(pdf->obj_count * sizeof(pdf->offsets[0]));
        for (size_t i = 0; i < pdf->obj_count; ++i) {
            pdf->offsets[i] = (size_t)ftell(fp);
            CYPDF_PrintObjDef(fp, objs[i]);
        }

        size_t xref_offset = (size_t)ftell(fp);
        CYPDF_PrintXref(fp, pdf);
        CYPDF_PrintTrailer(fp, pdf, file_path, xref_offset);

        fclose(fp);
    }
}

void CYPDF_FreeDoc(CYPDF_Doc* pdf) {
    if (pdf) {
        CYPDF_FreeFileHeader(pdf->file_header);

        CYPDF_DestroyMMgr(pdf->obj_mmgr);

        free(pdf->objs);
        free(pdf->offsets);
        free(pdf);
    }
}
