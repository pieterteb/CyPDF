#ifndef CYPDF_IMAGE_H
#define CYPDF_IMAGE_H


#include <stdbool.h>

#include "cypdf_types.h"
#include "cypdf_xobject.h"



typedef struct CYPDF_Image {
    char                file_path[256];

    CYPDF_TransMatrix   trans_matrix;

    CYPDF_ObjXObject*   xobject;
} CYPDF_Image;



#endif /* CYPDF_IMAGE_H */