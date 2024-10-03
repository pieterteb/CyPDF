#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "cypdf_stream.h"
#include "cypdf_dict.h"
#include "cypdf_dict_parameters.h"
#include "cypdf_integer.h"
#include "cypdf_log.h"
#include "cypdf_memmgr.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_types.h"



CYPDF_ObjStream* CYPDF_NewStream(CYPDF_MemMgr* const restrict memmgr) {
    CYPDF_TRACE;

    CYPDF_ObjStream* stream = (CYPDF_ObjStream*)CYPDF_GetMem(memmgr, sizeof(CYPDF_ObjStream));

    if (stream) {
        stream->header.class = CYPDF_OBJ_CLASS_STREAM;
        stream->bytes = NULL;
        stream->length = 0;

        stream->dict = CYPDF_NewDict(memmgr);
    }

    return stream;
}

void CYPDF_FreeStream(CYPDF_Object* obj) {
    CYPDF_TRACE;

    CYPDF_ObjStream* stream = (CYPDF_ObjStream*)obj;

    /* stream->dict is controlled by a memory manager. */
    free(stream->bytes);

    free(stream);
}

void CYPDF_PrintStream(CYPDF_Channel* const restrict channel, const CYPDF_Object* const obj) {
    CYPDF_TRACE;

    if (channel && obj) {
        CYPDF_ObjStream* stream = (CYPDF_ObjStream*)obj;

        CYPDF_DictSetAtIndex(stream->dict, CYPDF_STREAM_LENGTH_I, CYPDF_STREAM_LENGTH_K, CYPDF_NewInteger(stream->dict->memmgr, (int)stream->length));

        CYPDF_PrintObjDirect(channel, stream->dict);
        CYPDF_ChannelPrintNL(channel);
        CYPDF_ChannelPrintLine(channel, "stream");

        CYPDF_ChannelWrite(channel, stream->bytes, sizeof(unsigned char), stream->length);

        CYPDF_ChannelPrintNL(channel);
        CYPDF_ChannelPrint(channel, "endstream");
    }
}


int CYPDF_PrintToStream(CYPDF_ObjStream* const restrict stream, const char format[restrict static 1], va_list args) {
    CYPDF_TRACE;

    int ret = 0;

    if (stream) {
        va_list args_copy;
        va_copy(args_copy, args);

        size_t size = (size_t)vsnprintf(NULL, 0, format, args_copy);
        

        va_end(args_copy);

        stream->bytes = CYPDF_realloc(stream->bytes, (stream->length + size + 1) * sizeof(unsigned char));
        ret = vsnprintf((char*)(stream->bytes + stream->length), size + 1, format, args);
        stream->bytes = CYPDF_realloc(stream->bytes, (stream->length + size) * sizeof(unsigned char));

        stream->length += size;
    }

    return ret;
}

size_t CYPDF_WriteToStream(CYPDF_ObjStream* const restrict stream, const void* restrict buffer, const size_t size, size_t count) {
    CYPDF_TRACE;

    if (stream) {
        count *= size;
        stream->bytes = CYPDF_realloc(stream->bytes, stream->length + count);
        memcpy(stream->bytes + stream->length, (unsigned char*)buffer, count);

        stream->length += count;

        return count;
    }

    return 0;
}
