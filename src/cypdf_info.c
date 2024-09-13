#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cypdf_info.h"
#include "cypdf_consts.h"
#include "cypdf_dict.h"
#include "cypdf_mmgr.h"
#include "cypdf_string.h"
#include "cypdf_types.h"
#include "cypdf_utils.h"



CYPDF_ObjInfo* CYPDF_NewInfo(CYPDF_MMgr* const mmgr, char title[static 1], char author[static 1], char subject[static 1], char creator[static 1], char producer[static 1], char creation_date[restrict static 1]) {
    CYPDF_ObjInfo* info = (CYPDF_ObjInfo*)CYPDF_GetMem(mmgr, sizeof(CYPDF_ObjInfo));

    if (info) {
        CYPDF_InitHeader(info, CYPDF_OCLASS_INFO);
        info->dict = CYPDF_NewDict(mmgr);

        info->title = CPYDF_NewString(mmgr, CYPDF_STRTYPE_STRING, title);
        CYPDF_DictAppend(mmgr, info->dict, "Title", info->title);
        info->author = CPYDF_NewString(mmgr, CYPDF_STRTYPE_STRING, author);
        CYPDF_DictAppend(mmgr, info->dict, "Author", info->author);
        info->subject = CPYDF_NewString(mmgr, CYPDF_STRTYPE_STRING, subject);
        CYPDF_DictAppend(mmgr, info->dict, "Subject", info->subject);
        info->creator = CPYDF_NewString(mmgr, CYPDF_STRTYPE_STRING, creator);
        CYPDF_DictAppend(mmgr, info->dict, "Creator", info->creator);
        info->producer = CPYDF_NewString(mmgr, CYPDF_STRTYPE_STRING, producer);
        CYPDF_DictAppend(mmgr, info->dict, "Producer", info->producer);
        info->creation_date = CPYDF_NewString(mmgr, CYPDF_STRTYPE_STRING, creation_date);
        CYPDF_DictAppend(mmgr, info->dict, "CreationDate", info->creation_date);
    }

    return info;
}

void CYPDF_PrintInfo(FILE* restrict fp, const CYPDF_Object* const obj) {
    if (fp && obj) {
        CYPDF_ObjInfo* info = (CYPDF_ObjInfo*)obj;

        CYPDF_PrintObjDirect(fp, info->dict);
    }
}

void CYPDF_FreeInfo(CYPDF_Object* obj) {
    if (obj) {
        CYPDF_ObjInfo* info = (CYPDF_ObjInfo*)obj;

        free(info);
    }
}
