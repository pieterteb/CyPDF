#ifndef CYPDF_LIMITS_H
#define CYPDF_LIMITS_H


#include <float.h>
#include <limits.h>



/* PDF implementation limits for integer values. */
#define CYPDF_INTEGER_MAX                           INT32_MAX
#define CYPDF_INTEGER_MIN                           INT32_MIN

/* PDF implementation limits for real values. */
#define CYPDF_REAL_MAX                              FLT_MAX
#define CYPDF_REAL_MIN                              FLT_MIN

/* PDF implementation limit for significant digits of the fractional part of a real value. */
#define CYPDF_REAL_FRACTIONAL_DIGITS_MAX            5


/* PDF implementation limit for the length of a string (in a content stream). */
#define CYPDF_STRING_LENGTH_MAX                     32767


/* PDF implementation limit for the length of a name. */
#define CYPDF_NAME_LENGTH_MAX                       127


/* PDF implementation limit for the amount of indirect objects that can exist in a single PDF file. */
#define CYPDF_INDIRECT_OBJECT_MAX                   8388607
#define CYPDF_OBJECT_NUMBER_MAX                     (CYPDF_INDIRECT_OBJECT_MAX - 1)

/* PDF implementation limit for the amount of times an object can be reused. */
#define CYPDF_GENERATION_NUMBER_MAX                 65535


/* PDF implementation limit for graphics state nesting by q and Q operators. */
#define CYPDF_GRAPHICS_STATE_NESTING_DEPTH_MAX      28


/* PDF implementation limit for the value of a CID (character identifier). */
#define CYPDF_CID_MAX                               65535



#endif /* CYPDF_LIMITS_H */