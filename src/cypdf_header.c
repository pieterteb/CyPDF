#include "cypdf_header.h"
#include "cypdf_print.h"
#include "cypdf_version.h"



void CYPDF_PrintFileHeader(CYPDF_Channel* const restrict channel) {
    if (channel) {
        CYPDF_ChannelPrintComment(channel, CYPDF_PDF_VERSION);
        CYPDF_ChannelPrintNL(channel);
        CYPDF_ChannelPrintComment(channel, CYPDF_HIVAL_BYTES);
        CYPDF_ChannelPrintNL(channel);
    }
}
