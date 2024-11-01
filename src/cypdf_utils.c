#include <tgmath.h>

#include "cypdf_log.h"
#include "cypdf_types.h"
#include "cypdf_utils.h"



CYPDF_TransMatrix* CYPDF_TransMatrixTranslate(CYPDF_TransMatrix* const mat, const CYPDF_Point origin) {
    CYPDF_TRACE;

    mat->e += origin.x;
    mat->f += origin.y;

    return mat;
}

CYPDF_TransMatrix* CYPDF_TransMatrixScale(CYPDF_TransMatrix* const mat, const float scale_x, const float scale_y) {
    CYPDF_TRACE;

    mat->a *= scale_x;
    mat->c *= scale_x;
    mat->e *= scale_x;
    
    mat->b *= scale_y;
    mat->d *= scale_y;
    mat->f *= scale_y;

    return mat;
}

CYPDF_TransMatrix* CYPDF_TransMatrixRotate(CYPDF_TransMatrix* const mat, const float angle) {
    CYPDF_TRACE;

    float sintheta = sin(angle);
    float costheta = cos(angle);

    mat->a *= costheta;
    mat->b *= costheta;
    mat->c *= costheta;
    mat->d *= costheta;
    mat->e *= costheta;
    mat->f *= costheta;

    mat->a -= mat->b * sintheta;
    mat->b += mat->a * sintheta;
    mat->c -= mat->d * sintheta;
    mat->d += mat->c * sintheta;
    mat->e -= mat->f * sintheta;
    mat->f += mat->e * sintheta;

    return mat;
}

CYPDF_TransMatrix* CYPDF_TransMatrixSkew(CYPDF_TransMatrix* const mat, const float skew_x, const float skew_y) {
    CYPDF_TRACE;

    float tanalpha = tan(skew_x);
    float tanbeta = tan(skew_y);

    mat->a += mat->b * tanbeta;
    mat->c += mat->d * tanbeta;
    mat->e += mat->f * tanbeta;
    
    mat->b += mat->a * tanalpha;
    mat->d += mat->c * tanalpha;
    mat->f += mat->e * tanalpha;

    return mat;
}
