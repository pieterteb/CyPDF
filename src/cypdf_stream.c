#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cypdf_stream.h"
#include "cypdf_consts.h"
#include "cypdf_dict.h"
#include "cypdf_number.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_utils.h"



CYPDF_ObjStream* CYPDF_NewStream(const bool indirect) {
    CYPDF_ObjStream* stream = CYPDF_NewObj(indirect, CYPDF_OCLASS_STREAM);
    stream->dict = CYPDF_NewDict(CYPDF_FALSE);

    return stream;
}

void CYPDF_PrintToStream(CYPDF_ObjStream* const stream, const char format[restrict static 1], ...) {
    if (stream) {
        va_list args;
        va_start(args, format);
        size_t size = (size_t)vsnprintf(NULL, 0, format, args);
        
        va_list args_;
        va_copy(args_, args);
        stream->val = CYPDF_srealloc(stream->val, (stream->val_size + size) * sizeof(unsigned char));
        vsnprintf((char*)(stream->val + stream->val_size), size + 1, format, args_);

        va_end(args);
        va_end(args_);

        stream->val_size += size;
    }
}

void CYPDF_PrintStream(FILE* restrict fp, CYPDF_Object* const obj) {
    CYPDF_ObjStream* stream = (CYPDF_ObjStream*)obj;

    CYPDF_ObjNumber* length = CYPDF_NewNumber(CYPDF_FALSE, (int)stream->val_size);
    CYPDF_DictAppend(stream->dict, "Length", length);
    CYPDF_PrintObjDirect(fp, stream->dict);
    CYPDF_PrintNL(fp);
    CYPDF_fprintfNL(fp, "stream");

    fwrite(stream->val, sizeof(stream->val[0]), stream->val_size, fp);

    CYPDF_PrintNL(fp);
    fprintf(fp, "endstream");
}

void CYPDF_FreeStream(CYPDF_Object* const obj) {
    CYPDF_ObjStream* stream = (CYPDF_ObjStream*)obj;

    CYPDF_FreeObj(stream->dict, CYPDF_FALSE);
    free(stream->val);
    free(stream);
}
