#include <stdlib.h>
#include <string.h>

#include "cypdf_trailer.h"
#include "cypdf_array.h"
#include "cypdf_dict.h"
#include "cypdf_dict_parameters.h"
#include "cypdf_doc.h"
#include "cypdf_integer.h"
#include "cypdf_log.h"
#include "cypdf_memory.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_string.h"
#include "cypdf_time.h"
#include "md5.h"



void CYPDF_PrintTrailer(CYPDF_Channel* const restrict channel, const CYPDF_Doc* const restrict pdf, const char* restrict file_path, const size_t xref_offset) {
    CYPDF_TRACE;

    CYPDF_ObjDict* dict = CYPDF_NewDict(pdf->obj_memmgr);

    if (dict) {
        CYPDF_DictSetAtIndex(dict, CYPDF_TRAILER_SIZE_I, CYPDF_TRAILER_SIZE_K, CYPDF_NewInteger(dict->memmgr, (int)pdf->obj_list->element_count + 1)); /* + 1 for the free object entry (0000000000 65535 f) */
        CYPDF_DictSetAtIndex(dict, CYPDF_TRAILER_CATALOG_I, CYPDF_TRAILER_CATALOG_K, pdf->catalog);
        CYPDF_DictSetAtIndex(dict, CYPDF_TRAILER_INFO_I, CYPDF_TRAILER_INFO_K, pdf->info);

        char* string_to_hash = CYPDF_malloc(1024 * sizeof(char));
        CYPDF_ObjInfo* info = pdf->info;
        char* date = CYPDF_Date();
        sprintf(string_to_hash, "%s%s%ld%s%s%s%s%s%s",
                date, file_path, CYPDF_Channeltell(channel),
                CYPDF_StringGet(CYPDF_DictValueAtIndex(info, CYPDF_INFO_AUTHOR_I)),
                CYPDF_StringGet(CYPDF_DictValueAtIndex(info, CYPDF_INFO_TITLE_I)),
                CYPDF_StringGet(CYPDF_DictValueAtIndex(info, CYPDF_INFO_SUBJECT_I)),
                CYPDF_StringGet(CYPDF_DictValueAtIndex(info, CYPDF_INFO_CREATOR_I)),
                CYPDF_StringGet(CYPDF_DictValueAtIndex(info, CYPDF_INFO_PRODUCER_I)),
                CYPDF_StringGet(CYPDF_DictValueAtIndex(info, CYPDF_INFO_CREATION_DATE_I)));
        char* id = md5_string(string_to_hash);
        free(string_to_hash);

        CYPDF_ObjArray* array = CYPDF_NewArray(dict->memmgr);
        CYPDF_ObjString* ID = CPYDF_NewString(array->memmgr, CYPDF_STRTYPE_BYTE, id);
        free(id);
        CYPDF_ArrayAppend(array, ID);
        CYPDF_ArrayAppend(array, ID);
        CYPDF_DictSetAtIndex(dict, CYPDF_TRAILER_ID_I, CYPDF_TRAILER_ID_K, array);
    }

    CYPDF_ChannelPrintLine(channel, "trailer");

    CYPDF_PrintObjDirect(channel, dict);
    CYPDF_ChannelPrintNL(channel);

    CYPDF_ChannelPrintLine(channel, "startxref");
    CYPDF_ChannelPrintLine(channel, "%zu", xref_offset);
    CYPDF_ChannelPrint(channel, "%%%%EOF");
}
