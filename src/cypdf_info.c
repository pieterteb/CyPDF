#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cypdf_info.h"
#include "cypdf_consts.h"
#include "cypdf_dict.h"
#include "cypdf_object.h"
#include "cypdf_string.h"
#include "cypdf_utils.h"



CYPDF_ObjInfo* CYPDF_NewInfo(bool indirect, const char* title, const char* author, const char* subject, const char* creator, const char* producer, const char* creation_date) {
    CYPDF_ObjInfo* info = (CYPDF_ObjInfo*)CYPDF_NewObj(indirect, CYPDF_OCLASS_INFO);

    if (info) {
        snprintf(info->title, CYPDF_INFO_MAX_SIZE, "%s", title);
        snprintf(info->author, CYPDF_INFO_MAX_SIZE, "%s", author);
        snprintf(info->subject, CYPDF_INFO_MAX_SIZE, "%s", subject);
        snprintf(info->creator, CYPDF_INFO_MAX_SIZE, "%s", creator);
        snprintf(info->producer, CYPDF_INFO_MAX_SIZE, "%s", producer);
        snprintf(info->creation_date, CYPDF_INFO_MAX_SIZE, "%s", creation_date);

        info->dict = CYPDF_NewDict(CYPDF_FALSE);
    }

    return info;
}

void CYPDF_PrintInfo(FILE* fp, CYPDF_Object* obj) {
    if (fp == NULL || obj == NULL) {
        return;
    }

    CYPDF_ObjInfo* info = (CYPDF_ObjInfo*)obj;
    CYPDF_ObjDict* dict = info->dict;
    CYPDF_ObjString* string = CPYDF_NewString(CYPDF_FALSE, CYPDF_STRTYPE_STRING, (unsigned char*)info->title, strlen(info->title));
    CYPDF_DictAppend(dict, "Title", string);
    string = CPYDF_NewString(CYPDF_FALSE, CYPDF_STRTYPE_STRING, (unsigned char*)info->author, strlen(info->author));
    CYPDF_DictAppend(dict, "Author", string);
    string = CPYDF_NewString(CYPDF_FALSE, CYPDF_STRTYPE_STRING, (unsigned char*)info->subject, strlen(info->subject));
    CYPDF_DictAppend(dict, "Subject", string);
    string = CPYDF_NewString(CYPDF_FALSE, CYPDF_STRTYPE_STRING, (unsigned char*)info->creator, strlen(info->creator));
    CYPDF_DictAppend(dict, "Creator", string);
    string = CPYDF_NewString(CYPDF_FALSE, CYPDF_STRTYPE_STRING, (unsigned char*)info->producer, strlen(info->producer));
    CYPDF_DictAppend(dict, "Producer", string);
    string = CPYDF_NewString(CYPDF_FALSE, CYPDF_STRTYPE_STRING, (unsigned char*)info->creation_date, strlen(info->creation_date));
    CYPDF_DictAppend(dict, "CreationDate", string);

    CYPDF_PrintObjDirect(fp, dict);
}

void CYPDF_FreeInfo(CYPDF_Object* obj) {
    if (obj) {
        CYPDF_ObjInfo* info = (CYPDF_ObjInfo*)obj;
        
        CYPDF_FreeObj(info->dict, CYPDF_FALSE);

        free(info);
    }
}
