#include <stdio.h>
#include <stdlib.h>

#include "cypdf_doc.h"
#include "cypdf_array.h"
#include "cypdf_catalog.h"
#include "cypdf_consts.h"
#include "cypdf_dict.h"
#include "cypdf_graphics.h"
#include "cypdf_header.h"
#include "cypdf_null.h"
#include "cypdf_object.h"
#include "cypdf_pages.h"
#include "cypdf_print.h"
#include "cypdf_trailer.h"
#include "cypdf_utils.h"
#include "cypdf_xref.h"



static void CYPDF_Doc_Append_Object(CYPDF_Doc* pdf, CYPDF_Object* obj) {
    if (pdf) {
        ++pdf->obj_count;
        pdf->objs = CYPDF_srealloc(pdf->objs, pdf->obj_count * sizeof(CYPDF_Object*));
        pdf->objs[pdf->obj_count - 1] = obj;

        /* Once an object has been appended to the pdf document, it can receive an object number. */
        CYPDF_Obj_Set_Onum(obj, pdf->obj_count);
    }
}

CYPDF_Doc* CYPDF_New_Doc() {
    CYPDF_Doc* pdf = CYPDF_smalloc(sizeof(CYPDF_Doc));
    if (pdf) {
        pdf->file_header = CYPDF_New_File_Header();
        pdf->obj_count = 0;
        pdf->offsets = NULL;

        pdf->page_tree = CYPDF_New_PNode(CYPDF_TRUE, NULL);                     /* Page root. */
        pdf->catalog = CYPDF_New_Catalog(CYPDF_TRUE, pdf->page_tree);
        

        char* creation_date = CYPDF_Get_Date();
        pdf->info = CYPDF_New_Info(CYPDF_TRUE, "Test", "Bob", "Test", "CyPDF", "CyProducer", creation_date);
        free(creation_date);

        CYPDF_Doc_Append_Object(pdf, pdf->catalog);
        CYPDF_Doc_Append_Object(pdf, pdf->page_tree);
        CYPDF_Doc_Append_Object(pdf, pdf->info);
    }

    return pdf;
}

void CYPDF_Append_Page(CYPDF_Doc* pdf) {
    CYPDF_Obj_Page* page = CYPDF_Add_Page(pdf->page_tree, CYPDF_A4_MEDIABOX);
    CYPDF_Doc_Append_Object(pdf, page);
}

void CYPDF_Add_Path(CYPDF_Doc* pdf, CYPDF_INT page_number, CYPDF_Path* path) {
    if (path && pdf) {
        CYPDF_Obj_Stream* stream = CYPDF_New_Stream(CYPDF_TRUE);
        CYPDF_Write_Path_To_Stream(stream, path);

        CYPDF_Obj_Page* page = CYPDF_Page_At_Number(pdf->page_tree, page_number);
        CYPDF_Page_Add_Content(page, stream);

        CYPDF_Doc_Append_Object(pdf, stream);
    }
}

void CYPDF_Write_Doc(FILE* fp, CYPDF_Doc* pdf, const char* file_path) {
    if (fp == NULL || pdf == NULL) {
        return;
    }

    CYPDF_Write_File_Header(fp, pdf->file_header);

    CYPDF_Object** objs = pdf->objs;
    pdf->offsets = CYPDF_smalloc(pdf->obj_count * sizeof(CYPDF_INT64));
    for (size_t i = 0; i < pdf->obj_count; ++i) {
        pdf->offsets[i] = ftell(fp);
        CYPDF_Write_Obj_Def(fp, objs[i]);
    }

    CYPDF_INT64 xref_offset = ftell(fp);
    CYPDF_Write_Xref(fp, pdf);
    CYPDF_Write_Trailer(fp, pdf, file_path, xref_offset);
}

void CYPDF_Free_Doc(CYPDF_Doc* pdf) {
    if (pdf) {
        CYPDF_Free_File_Header(pdf->file_header);

        for (size_t i = 0; i < pdf->obj_count; ++i) {
            CYPDF_Free_Obj(pdf->objs[i], CYPDF_TRUE);
        }
        free(pdf->objs);
        
        free(pdf->offsets);
        free(pdf);
    }
}
