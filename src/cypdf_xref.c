#include "cypdf_xref.h"
#include "cypdf_consts.h"
#include "cypdf_doc.h"
#include "cypdf_log.h"
#include "cypdf_object.h"
#include "cypdf_print.h"



void CYPDF_PrintXref(CYPDF_Channel* const restrict channel, CYPDF_Doc* const restrict pdf) {
    CYPDF_TRACE;

    if (channel) {
        CYPDF_ChannelPrintLine(channel, "xref");
        CYPDF_ChannelPrintLine(channel, "0 %zu", pdf->obj_list->element_count + 1);

        CYPDF_ChannelPrintLine(channel, "%.10zu %.5hu f", 0UL, CYPDF_OGEN_MAX);
        for (size_t i = 0; i < pdf->obj_list->element_count; ++i) {
            CYPDF_Object* obj = CYPDF_ListAtIndex(pdf->obj_list, i);
            CYPDF_ChannelPrintLine(channel, "%.10llu %.5hu n", pdf->offsets[i], CYPDF_ObjGetObjGen(obj));
        }
    }
}
