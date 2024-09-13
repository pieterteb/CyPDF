#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cypdf_stream.h"
#include "cypdf_dict.h"
#include "cypdf_mmgr.h"
#include "cypdf_number.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_types.h"
#include "cypdf_utils.h"



CYPDF_ObjStream* CYPDF_NewStream(CYPDF_MMgr* const mmgr) {
    CYPDF_ObjStream* stream = (CYPDF_ObjStream*)CYPDF_GetMem(mmgr, sizeof(CYPDF_ObjStream));

    if (stream) {
        CYPDF_InitHeader(stream, CYPDF_OCLASS_STREAM);
        stream->bytes = NULL;
        stream->length = CYPDF_NewNumber(mmgr, 0);

        stream->dict = CYPDF_NewDict(mmgr);
        if (stream->dict) {
            CYPDF_DictAppend(mmgr, stream->dict, "Length", stream->length);
        }
    }

    return stream;
}

void CYPDF_PrintToStream(CYPDF_ObjStream* const stream, const char format[restrict static 1], ...) {
    if (stream) {
        va_list args;
        va_start(args, format);
        size_t size = (size_t)vsnprintf(NULL, 0, format, args);
        
        va_list args_;
        va_copy(args_, args);
        size_t curr_len = (size_t)CYPDF_GetNumber(stream->length);
        stream->bytes = CYPDF_srealloc(stream->bytes, (curr_len + size) * sizeof(unsigned char));
        vsnprintf((char*)(stream->bytes + curr_len), size + 1, format, args_);

        va_end(args);
        va_end(args_);

        CYPDF_SetNumber(stream->length, (int)(curr_len + size));
    }
}

void CYPDF_PrintStream(FILE* restrict fp, const CYPDF_Object* const obj) {
    CYPDF_ObjStream* stream = (CYPDF_ObjStream*)obj;

    CYPDF_PrintObjDirect(fp, stream->dict);
    CYPDF_PrintNL(fp);
    CYPDF_fprintfNL(fp, "stream");

    fwrite(stream->bytes, sizeof(stream->bytes[0]), (size_t)CYPDF_GetNumber(stream->length), fp);

    CYPDF_PrintNL(fp);
    fprintf(fp, "endstream");
}

void CYPDF_FreeStream(CYPDF_Object* obj) {
    CYPDF_ObjStream* stream = (CYPDF_ObjStream*)obj;

    free(stream->bytes);
    free(stream);
}
