#include <stdio.h>

#include "cypdf_xref.h"
#include "cypdf_consts.h"
#include "cypdf_doc.h"
#include "cypdf_object.h"
#include "cypdf_print.h"



void CYPDF_Write_Xref(FILE* fp, CYPDF_Doc* pdf) {
    if (pdf) {
        CYPDF_fprintf_NL(fp, "xref");
        CYPDF_fprintf_NL(fp, "0 %zu", pdf->obj_count + 1);

        CYPDF_fprintf_NL(fp, "%.10zu %.5hu f", 0UL, CYPDF_OGEN_MAX);
        for (size_t i = 0; i < pdf->obj_count; ++i) {
            CYPDF_Object* obj = pdf->objs[i];
            CYPDF_fprintf_NL(fp, "%.10llu %.5hu n", pdf->offsets[i], CYPDF_Obj_Get_Ogen(obj));
        }
    }
}
