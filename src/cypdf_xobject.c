#include "cypdf_xobject.h"
#include "cypdf_dict.h"
#include "cypdf_dict_parameters.h"
#include "cypdf_log.h"
#include "cypdf_memory.h"
#include "cypdf_name.h"
#include "cypdf_object.h"
#include "cypdf_stream.h"



CYPDF_ObjXObject* CYPDF_NewXObject(CYPDF_MemMgr* const memmgr, const enum CYPDF_XOBJECT_TYPE type) {
    CYPDF_TRACE;

    CYPDF_ObjXObject* xobject = CYPDF_NewStream(memmgr);
    CYPDF_ObjDict* dict = xobject->dict;

    CYPDF_ObjName* subtype = NULL;
    switch  (type)
    {
    case CYPDF_XOBJECT_IMAGE:
        subtype = CYPDF_NewName(dict->memmgr, CYPDF_XOBJECT_IMAGE_K);
        break;
    default:
        subtype = CYPDF_NewName(dict->memmgr, CYPDF_XOBJECT_FORM_K);
        break;
    }
    CYPDF_DictSetAtIndex(dict, CYPDF_XOBJECT_SUBTYPE_I, CYPDF_XOBJECT_SUBTYPE_K, subtype);

    return xobject;
}
