#ifndef CYPDF_XOBJECT_H
#define CYPDF_XOBJECT_H


#include "cypdf_dict.h"



#define CYPDF_XOBJECT_IMAGE_K   "Image"
#define CYPDF_XOBJECT_FORM_K    "Form"


enum CYPDF_XOBJECT_TYPE {
    CYPDF_XOBJECT_IMAGE = 0,
    CYPDF_XOBJECT_FORM
};


typedef CYPDF_ObjDict CYPDF_XObject;


CYPDF_XObject* CYPDF_NewXObject(CYPDF_MemMgr* const memmgr, const enum CYPDF_XOBJECT_TYPE type);



#endif /* CYPDF_XOBJECT_H */