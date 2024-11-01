#ifndef CYPDF_UTILS_H
#define CYPDF_UTILS_H


#include "cypdf_types.h"



CYPDF_TransMatrix* CYPDF_TransMatrixTranslate(CYPDF_TransMatrix* const mat, const CYPDF_Point origin);

CYPDF_TransMatrix* CYPDF_TransMatrixScale(CYPDF_TransMatrix* const mat, const float scale_x, const float scale_y);

CYPDF_TransMatrix* CYPDF_TransMatrixRotate(CYPDF_TransMatrix* const mat, const float angle);

CYPDF_TransMatrix* CYPDF_TransMatrixSkew(CYPDF_TransMatrix* const mat, const float skew_x, const float skew_y);



#endif /* CYPDF_UTILS_H */
