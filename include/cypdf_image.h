#ifndef CYPDF_IMAGE_H
#define CYPDF_IMAGE_H


#include <stdbool.h>

#include "cypdf_types.h"
#include "cypdf_xobject.h"



typedef struct CYPDF_Image {
    char                file_path[256];

    float               rotation;
    float               skew;
    float               x_stretch;
    float               y_stretch;
    bool                reflection;
    CYPDF_Point         translation;

    CYPDF_ObjXObject*   xobject;
} CYPDF_Image;



#endif /* CYPDF_IMAGE_H */