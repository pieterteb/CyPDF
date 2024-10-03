#include "cypdf_info.h"
#include "cypdf_dict.h"
#include "cypdf_dict_parameters.h"
#include "cypdf_log.h"
#include "cypdf_memmgr.h"
#include "cypdf_string.h"



CYPDF_ObjInfo* CYPDF_NewInfo(CYPDF_MemMgr* const restrict memmgr, char title[static 1], char author[static 1], char subject[static 1], char creator[static 1], char producer[static 1], char creation_date[restrict static 1]) {
    CYPDF_TRACE;

    CYPDF_ObjInfo* info = CYPDF_NewDict(memmgr);

    if (info) {
        info->header.subclass = CYPDF_OBJ_SUBCLASS_INFO;

        CYPDF_DictSetAtIndex(info, CYPDF_INFO_TITLE_I, CYPDF_INFO_TITLE_K, CPYDF_NewString(info->memmgr, CYPDF_STRTYPE_STRING, title));                 /* The document’s title. */
        CYPDF_DictSetAtIndex(info, CYPDF_INFO_AUTHOR_I, CYPDF_INFO_AUTHOR_K, CPYDF_NewString(info->memmgr, CYPDF_STRTYPE_STRING, author));               /* The name of the person who created the document. */
        CYPDF_DictSetAtIndex(info, CYPDF_INFO_SUBJECT_I, CYPDF_INFO_SUBJECT_K, CPYDF_NewString(info->memmgr, CYPDF_STRTYPE_STRING, subject));             /* The subject of the document. */
        CYPDF_DictSetAtIndex(info, CYPDF_INFO_CREATOR_I, CYPDF_INFO_CREATOR_K, CPYDF_NewString(info->memmgr, CYPDF_STRTYPE_STRING, creator));             /* If the document was converted to PDF from another format, the name of the application (for example, VSCode) that created the original document from which it was converted. */
        CYPDF_DictSetAtIndex(info, CYPDF_INFO_PRODUCER_I, CYPDF_INFO_PRODUCER_K, CPYDF_NewString(info->memmgr, CYPDF_STRTYPE_STRING, producer));           /* If the document was converted to PDF from another format, the name of the application (for example, CyProducer) that converted it to PDF. */
        CYPDF_DictSetAtIndex(info, CYPDF_INFO_CREATION_DATE_I, CYPDF_INFO_CREATION_DATE_K, CPYDF_NewString(info->memmgr, CYPDF_STRTYPE_STRING, creation_date)); /* The date and time the document was created, in human-readable form. */
        CYPDF_DictSetAtIndex(info, CYPDF_INFO_MOD_DATE_I, CYPDF_INFO_MOD_DATE_K, CPYDF_NewString(info->memmgr, CYPDF_STRTYPE_STRING, creation_date));      /* The date and time the document was most recently modified, in human-readable form. */
    }

    return info;
}
