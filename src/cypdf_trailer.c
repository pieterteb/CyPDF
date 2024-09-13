#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cypdf_trailer.h"
#include "cypdf_array.h"
#include "cypdf_consts.h"
#include "cypdf_dict.h"
#include "cypdf_doc.h"
#include "cypdf_mmgr.h"
#include "cypdf_number.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_string.h"
#include "cypdf_utils.h"
#include "md5.h"



void CYPDF_PrintTrailer(FILE* fp, CYPDF_Doc* pdf, const char* file_path, uint64_t xref_offset) {
    CYPDF_MMgr* mmgr = pdf->obj_mmgr;
    CYPDF_ObjDict* dict = CYPDF_NewDict(mmgr);

    if (dict) {
        CYPDF_ObjNumber* size = CYPDF_NewNumber(mmgr, (int)pdf->obj_count + 1); /* +1 for the free object entry (0000000000 65535 f) */
        CYPDF_DictAppend(mmgr, dict, "Size", size);
        CYPDF_DictAppend(mmgr, dict, "Root", pdf->catalog);
        CYPDF_DictAppend(mmgr, dict, "Info", pdf->info);

        char* string_to_hash = CYPDF_smalloc(1024 * sizeof(char));
        CYPDF_ObjInfo* info = pdf->info;
        char* date = CYPDF_GetDate();
        sprintf(string_to_hash, "%s%s%ld%s%s%s%s%s%s",
                date, file_path, ftell(fp),
                CYPDF_GetString(info->title),
                CYPDF_GetString(info->author),
                CYPDF_GetString(info->subject),
                CYPDF_GetString(info->creator),
                CYPDF_GetString(info->producer),
                CYPDF_GetString(info->creation_date));
        char* id = md5_string(string_to_hash);
        free(string_to_hash);

        CYPDF_ObjString* ID = CPYDF_NewString(mmgr, CYPDF_STRTYPE_BYTE, id);
        free(id);
        CYPDF_ObjArray* array = CYPDF_NewArray(mmgr);
        CYPDF_ArrayAppend(array, ID);
        CYPDF_ArrayAppend(array, ID);
        CYPDF_DictAppend(mmgr, dict, "ID", array);
    }

    CYPDF_fprintfNL(fp, "trailer");

    CYPDF_PrintObjDirect(fp, dict);
    CYPDF_PrintNL(fp);

    CYPDF_fprintfNL(fp, "startxref");
    CYPDF_fprintfNL(fp, "%lld", xref_offset);
    fprintf(fp, "%%%%EOF");
}
