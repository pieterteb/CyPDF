#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cypdf_stream.h"
#include "cypdf_consts.h"
#include "cypdf_dict.h"
#include "cypdf_number.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_types.h"
#include "cypdf_utils.h"



CYPDF_Obj_Stream* CYPDF_New_Stream(CYPDF_BOOL indirect) {
    CYPDF_Obj_Stream* stream = CYPDF_New_Obj(indirect, CYPDF_OCLASS_STREAM);
    stream->dict = CYPDF_New_Dict(CYPDF_FALSE);

    return stream;
}

void CYPDF_Write_To_Stream(CYPDF_Obj_Stream* stream, CYPDF_BYTE* val, CYPDF_SIZE val_size) {
    if (stream) {
        stream->val = CYPDF_srealloc(stream->val, (stream->val_size + val_size) * sizeof(CYPDF_BYTE));
        memcpy(&stream->val[stream->val_size], val, val_size);
        stream->val_size += val_size;
    }
}

void CYPDF_Write_Stream(FILE* fp, CYPDF_Object* obj) {
    CYPDF_Obj_Stream* stream = (CYPDF_Obj_Stream*)obj;

    CYPDF_Obj_Number* length = CYPDF_New_Number(CYPDF_FALSE, (CYPDF_INT)stream->val_size);
    CYPDF_Dict_Append(stream->dict, "Length", length);
    CYPDF_Write_Obj_Direct(fp, stream->dict);
    CYPDF_Write_NL(fp);
    CYPDF_fprintf_NL(fp, "stream");

    fwrite(stream->val, sizeof(stream->val[0]), stream->val_size, fp);

    CYPDF_Write_NL(fp);
    fprintf(fp, "endstream");
}

void CYPDF_Free_Stream(CYPDF_Object* obj) {
    CYPDF_Obj_Stream* stream = (CYPDF_Obj_Stream*)obj;

    CYPDF_Free_Obj(stream->dict, CYPDF_FALSE);
    free(stream->val);
}
