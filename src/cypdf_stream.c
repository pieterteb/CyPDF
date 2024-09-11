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



CYPDF_ObjStream* CYPDF_NewStream(bool indirect) {
    CYPDF_ObjStream* stream = CYPDF_NewObj(indirect, CYPDF_OCLASS_STREAM);
    stream->dict = CYPDF_NewDict(CYPDF_FALSE);

    return stream;
}

void CYPDF_PrintToStream(CYPDF_ObjStream* stream, unsigned char* val, size_t val_size) {
    if (stream) {
        stream->val = CYPDF_srealloc(stream->val, (stream->val_size + val_size) * sizeof(unsigned char));
        memcpy(&stream->val[stream->val_size], val, val_size);
        stream->val_size += val_size;
    }
}

void CYPDF_PrintStream(FILE* fp, CYPDF_Object* obj) {
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

void CYPDF_FreeStream(CYPDF_Object* obj) {
    CYPDF_ObjStream* stream = (CYPDF_ObjStream*)obj;

    CYPDF_FreeObj(stream->dict, CYPDF_FALSE);
    free(stream->val);
}
