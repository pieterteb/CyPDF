#include <stdarg.h>
#include <stdio.h>

#include "cypdf_print.h"
#include "cypdf_consts.h"
#include "cypdf_log.h"
#include "cypdf_memory.h"
#include "cypdf_stream.h"



static int CYPDF_ChannelVPrint(CYPDF_Channel* const restrict channel, const char format[restrict static 1], va_list args);


CYPDF_Channel* CYPDF_NewChannel(void* const restrict stream, const enum CYPDF_CHANNEL_TYPE type) {
    CYPDF_TRACE;

    CYPDF_Channel* channel = CYPDF_malloc(sizeof(CYPDF_Channel));

    if (channel) {
        channel->type = type;
        channel->stream = stream;
    }

    return channel;
}


int CYPDF_ChannelPrint(CYPDF_Channel* const restrict channel, const char format[restrict static 1], ...) {
    CYPDF_TRACE;

    int characters_printed = 0;

    if (channel) {
        va_list args;
        va_start(args, format);

        CYPDF_ChannelVPrint(channel, format, args);

        va_end(args);
    }

    return characters_printed;
}

size_t CYPDF_ChannelWrite(CYPDF_Channel* const restrict channel, const void* restrict buffer, size_t size, size_t count) {
    CYPDF_TRACE;

    size_t objects_written = 0;

    if (channel) {
        switch (channel->type)
        {
        case CYPDF_CHANNEL_FILE:
            objects_written = fwrite(buffer, size, count, (FILE*)channel->stream);
            break;
        case CYPDF_CHANNEL_OBJSTREAM:
            objects_written = CYPDF_WriteToStream((CYPDF_ObjStream*)channel->stream, buffer, size, count);
            break;
        default:
            break;
        }
    }

    return objects_written;
}

int CYPDF_ChannelPrintNL(CYPDF_Channel* const restrict channel) {
    CYPDF_TRACE;

    int characters_printed = 0;

    if (channel) {
        characters_printed = (int)CYPDF_ChannelWrite(channel, CYPDF_NEW_LINE, sizeof(char), CYPDF_NEW_LINE_SIZE);
    }

    return characters_printed;
}

int CYPDF_ChannelPrintComment(CYPDF_Channel* const restrict channel, const char format[restrict static 1], ...) {
    CYPDF_TRACE;

    int characters_printed = 0;

    if (channel) {
        va_list args;
        va_start(args, format);

        characters_printed += CYPDF_ChannelPrint(channel, "%%");
        characters_printed += CYPDF_ChannelVPrint(channel, format, args);

        va_end(args);
    }

    return characters_printed;
}

int CYPDF_ChannelPrintLine(CYPDF_Channel* const restrict channel, const char format[restrict static 1], ...) {
    CYPDF_TRACE;

    int characters_printed = 0;

    if (channel) {
        va_list args;
        va_start(args, format);

        characters_printed += CYPDF_ChannelVPrint(channel, format, args);
        characters_printed += CYPDF_ChannelPrintNL(channel);

        va_end(args);
    }

    return characters_printed;
}

static int CYPDF_ChannelVPrint(CYPDF_Channel* const restrict channel, const char format[restrict static 1], va_list args) {
    CYPDF_TRACE;

    int characters_printed = 0;

    if (channel) {
        switch (channel->type)
        {
        case CYPDF_CHANNEL_FILE:
            characters_printed = vfprintf((FILE*)channel->stream, format, args);
            break;
        case CYPDF_CHANNEL_OBJSTREAM:
            characters_printed = CYPDF_PrintToStream((CYPDF_ObjStream*)channel->stream, format, args);
            break;
        default:
            break;
        }
    }

    return characters_printed;
}


long CYPDF_Channeltell(CYPDF_Channel* const restrict channel) {
    CYPDF_TRACE;

    long current_position = 0;

    if (channel) {
        switch (channel->type)
        {
        case CYPDF_CHANNEL_FILE:
            current_position = ftell((FILE*)channel->stream);
            break;
        case CYPDF_CHANNEL_OBJSTREAM:
            current_position = (long)((CYPDF_ObjStream*)channel->stream)->length;
            break;
        default:
            break;
        }
    }

    return current_position;
}
