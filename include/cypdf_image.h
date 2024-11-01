#ifndef CYPDF_IMAGE_H
#define CYPDF_IMAGE_H


#include "cypdf_xobject.h"



typedef CYPDF_ObjXObject CYPDF_ObjImage;


CYPDF_ObjImage* CYPDF_NewImage(CYPDF_MemMgr* restrict const memmgr, const char path[restrict static 1]);



#endif /* CYPDF_IMAGE_H */
