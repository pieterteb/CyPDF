#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cypdf_trailer.h"
#include "cypdf_array.h"
#include "cypdf_consts.h"
#include "cypdf_dict.h"
#include "cypdf_doc.h"
#include "cypdf_number.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_string.h"
#include "cypdf_utils.h"
#include "md5.h"



void CYPDF_PrintTrailer(FILE* fp, CYPDF_Doc* pdf, const char* file_path, uint64_t xref_offset) {
    CYPDF_ObjDict* dict = CYPDF_NewDict(CYPDF_FALSE);

    if (dict) {
        CYPDF_ObjNumber* size = CYPDF_NewNumber(CYPDF_FALSE, (int)pdf->obj_count + 1); /* +1 for the free object entry (0000000000 65535 f) */
        CYPDF_DictAppend(dict, "Size", size);
        CYPDF_DictAppend(dict, "Root", pdf->catalog);
        CYPDF_DictAppend(dict, "Info", pdf->info);

        char* string_to_hash = CYPDF_smalloc(1024 * sizeof(char));
        CYPDF_ObjInfo* info = pdf->info;
        char* date = info->creation_date;
        sprintf(string_to_hash, "%s%s%ld%s%s%s%s%s%s",
                date, file_path, ftell(fp),
                info->title,
                info->author,
                info->subject,
                info->creator,
                info->producer,
                info->creation_date);
        char* id = md5_string(string_to_hash);
        free(string_to_hash);

        CYPDF_ObjString* ID = CPYDF_NewString(CYPDF_FALSE, CYPDF_STRTYPE_BYTE, (unsigned char*)id, strlen(id));
        free(id);
        CYPDF_ObjArray* array = CYPDF_NewArray(CYPDF_FALSE);
        CYPDF_ArrayAppend(array, ID);
        CYPDF_ArrayAppend(array, ID);
        CYPDF_DictAppend(dict, "ID", array);
    }

    CYPDF_fprintfNL(fp, "trailer");

    CYPDF_PrintObjDirect(fp, dict);
    CYPDF_FreeObj(dict, CYPDF_FALSE);
    CYPDF_PrintNL(fp);

    CYPDF_fprintfNL(fp, "startxref");
    CYPDF_fprintfNL(fp, "%lld", xref_offset);
    fprintf(fp, "%%%%EOF");
}
