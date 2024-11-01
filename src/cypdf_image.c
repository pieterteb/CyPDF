#include <string.h>

#include "cypdf_image.h"
#include "cypdf_log.h"
#include "cypdf_memory.h"
#include "cypdf_types.h"
#include "cypdf_xobject.h"



CYPDF_Image* CYPDF_NewImage(CYPDF_MemMgr* restrict const memmgr, const char path[restrict static 1], const CYPDF_TransMatrix matrix) {
    CYPDF_TRACE;

    CYPDF_Image* image = CYPDF_malloc(sizeof(CYPDF_Image));

    strcpy(image->file_path, path);
    image->trans_matrix = matrix;
    image->xobject = CYPDF_NewXObject(memmgr, CYPDF_XOBJECT_IMAGE);

    return image;
}
