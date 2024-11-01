#ifndef CYPDF_IMAGE_H
#define CYPDF_IMAGE_H


#include "cypdf_types.h"
#include "cypdf_xobject.h"



typedef struct CYPDF_Image {
    char                file_path[256];

    CYPDF_TransMatrix   trans_matrix;

    CYPDF_ObjXObject*   xobject;
} CYPDF_Image;


CYPDF_Image* CYPDF_NewImage(CYPDF_MemMgr* restrict const memmgr, const char path[restrict static 1], const CYPDF_TransMatrix matrix);



#endif /* CYPDF_IMAGE_H */
