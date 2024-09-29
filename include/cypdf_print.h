#ifndef CYPDF_PRINT_H
#define CYPDF_PRINT_H


#include <stddef.h>



enum CYPDF_CHANNEL_TYPE {
    CYPDF_CHANNEL_FILE,
    CYPDF_CHANNEL_OBJSTREAM,
};


typedef struct CYPDF_Channel {
    enum CYPDF_CHANNEL_TYPE type;
    void*                   stream;
} CYPDF_Channel;


CYPDF_Channel* CYPDF_NewChannel(void* const restrict stream, const enum CYPDF_CHANNEL_TYPE type);


int CYPDF_ChannelPrint(CYPDF_Channel* const restrict channel, const char format[restrict static 1], ...);

size_t CYPDF_ChannelWrite(CYPDF_Channel* const restrict channel, const void* restrict buffer, size_t size, size_t count);

int CYPDF_ChannelPrintNL(CYPDF_Channel* const restrict channel);

int CYPDF_ChannelPrintComment(CYPDF_Channel* const restrict channel, const char format[restrict static 1], ...);

int CYPDF_ChannelPrintLine(CYPDF_Channel* const restrict channel, const char format[restrict static 1], ...);


long CYPDF_Channeltell(CYPDF_Channel* const restrict channel);



#endif /* CYPDF_PRINT_H */
