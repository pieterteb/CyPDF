#ifndef CYPDF_LIMITS_H
#define CYPDF_LIMITS_H



/* PDF implementation limits for integer values. */
#define CYPDF_INTEGER_MAX                           2'147'483'647
#define CYPDF_INTEGER_MIN                           -2'147'483'648

/* PDF implementation limits for real values. */
#define CYPDF_REAL_BIG_MAX                          3.402'823'5E38
#define CYPDF_REAL_BIG_MIN                          -CYPDF_REAL_BIG_MAX
#define CYPDF_REAL_SMALL_MAX                        1.175'494'35e-38
#define CYPDF_REAL_SMALL_MIN                        -CYPDF_REAL_SMALL_MAX

/* PDF implementation limit for significant digits of the fractional part of a real value. */
#define CYPDF_REAL_FRACTIONAL_DIGITS_MAX            5


/* PDF implementation limit for the length of a string (in a content stream). */
#define CYPDF_STRING_LENGTH_MAX                     32'767


/* PDF implementation limit for the length of a name. */
#define CYPDF_NAME_LENGTH_MAX                       127


/* PDF implementation limit for the amount of indirect objects that can exist in a single PDF file. */
#define CYPDF_INDIRECT_OBJECT_MAX                   8'388'607
#define CYPDF_OBJECT_NUMBER_MAX                     (CYPDF_INDIRECT_OBJECT_MAX - 1)

/* PDF implementation limit for the amount of times an object can be reused. */
#define CYPDF_GENERATION_NUMBER_MAX                 65'535


/* PDF implementation limit for graphics state nesting by q and Q operators. */
#define CYPDF_GRAPHICS_STATE_NESTING_DEPTH_MAX      28


/* PDF implementation limit for the value of a CID (character identifier). */
#define CYPDF_CID_MAX                               65'535



#endif /* CYPDF_LIMITS_H */