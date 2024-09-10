#ifndef CYPDF_CONSTS_H
#define CYPDF_CONSTS_H


#include "cypdf_types.h"



/* CYPDF new line string */
#define CYPDF_NEW_LINE              "\x0D\x0A"  /* Carriage return followed by line feed. */


/* CYPDF boolean values */
#define CYPDF_TRUE                  1
#define CYPDF_FALSE                 0


/* CYPDF limits */
#define CYPDF_INDIRECT_OBJ_MAX      8388607     /* 2^23 - 1 */
#define CYPDF_OGEN_MAX              65535       /* 2^16 - 1 */


/* Page sizes (UU: User Unit) */
#define CYPDF_INCH_TO_UU(x)         (CYPDF_REAL)(72 * (x))
#define CYPDF_UU_TO_INCH(x)         ((x) / 72)
#define CYPDF_MM_TO_UU(x)           (CYPDF_REAL)(72 / 25.4 * (x))
#define CYPDF_UU_TO_MM(x)           (25.4 / 72 * (x))

#define CYPDF_MAX_PAGE_SIZE         14400           /* In User Units which equals to 200 inches. */
#define CYPDF_MIN_PAGE_SIZE         3               /* In User Units which equals to 0.04 inches. */

#define CYPDF_A0_WIDTH              (CYPDF_REAL)CYPDF_MM_TO_UU(841)
#define CYPDF_A0_HEIGHT             (CYPDF_REAL)CYPDF_MM_TO_UU(1189)
#define CYPDF_A0_MEDIABOX           CYPDF_TO_RECT(0.0, 0.0, CYPDF_A0_WIDTH, CYPDF_A0_HEIGHT)

#define CYPDF_A1_WIDTH              (CYPDF_REAL)CYPDF_MM_TO_UU(594)
#define CYPDF_A1_HEIGHT             (CYPDF_REAL)CYPDF_MM_TO_UU(841)
#define CYPDF_A1_MEDIABOX           CYPDF_TO_RECT(0.0, 0.0, CYPDF_A1_WIDTH, CYPDF_A1_HEIGHT)

#define CYPDF_A2_WIDTH              (CYPDF_REAL)CYPDF_MM_TO_UU(420)
#define CYPDF_A2_HEIGHT             (CYPDF_REAL)CYPDF_MM_TO_UU(594)
#define CYPDF_A2_MEDIABOX           CYPDF_TO_RECT(0.0, 0.0, CYPDF_A2_WIDTH, CYPDF_A2_HEIGHT)

#define CYPDF_A3_WIDTH              (CYPDF_REAL)CYPDF_MM_TO_UU(297)
#define CYPDF_A3_HEIGHT             (CYPDF_REAL)CYPDF_MM_TO_UU(420)
#define CYPDF_A3_MEDIABOX           CYPDF_TO_RECT(0.0, 0.0, CYPDF_A3_WIDTH, CYPDF_A3_HEIGHT)

#define CYPDF_A4_WIDTH              (CYPDF_REAL)CYPDF_MM_TO_UU(210)
#define CYPDF_A4_HEIGHT             (CYPDF_REAL)CYPDF_MM_TO_UU(297)
#define CYPDF_A4_MEDIABOX           CYPDF_TO_RECT(0.0, 0.0, CYPDF_A4_WIDTH, CYPDF_A4_HEIGHT)

#define CYPDF_A5_WIDTH              (CYPDF_REAL)CYPDF_MM_TO_UU(148)
#define CYPDF_A5_HEIGHT             (CYPDF_REAL)CYPDF_MM_TO_UU(210)
#define CYPDF_A5_MEDIABOX           CYPDF_TO_RECT(0.0, 0.0, CYPDF_A5_WIDTH, CYPDF_A5_HEIGHT)

#define CYPDF_A6_WIDTH              (CYPDF_REAL)CYPDF_MM_TO_UU(105)
#define CYPDF_A6_HEIGHT             (CYPDF_REAL)CYPDF_MM_TO_UU(148)
#define CYPDF_A6_MEDIABOX           CYPDF_TO_RECT(0.0, 0.0, CYPDF_A6_WIDTH, CYPDF_A6_HEIGHT)

#define CYPDF_A7_WIDTH              (CYPDF_REAL)CYPDF_MM_TO_UU(74)
#define CYPDF_A7_HEIGHT             (CYPDF_REAL)CYPDF_MM_TO_UU(105)
#define CYPDF_A7_MEDIABOX           CYPDF_TO_RECT(0.0, 0.0, CYPDF_A7_WIDTH, CYPDF_A7_HEIGHT)

#define CYPDF_A8_WIDTH              (CYPDF_REAL)CYPDF_MM_TO_UU(52)
#define CYPDF_A8_HEIGHT             (CYPDF_REAL)CYPDF_MM_TO_UU(74)
#define CYPDF_A8_MEDIABOX           CYPDF_TO_RECT(0.0, 0.0, CYPDF_A8_WIDTH, CYPDF_A8_HEIGHT)

#define CYPDF_A9_WIDTH              (CYPDF_REAL)CYPDF_MM_TO_UU(37)
#define CYPDF_A9_HEIGHT             (CYPDF_REAL)CYPDF_MM_TO_UU(52)
#define CYPDF_A9_MEDIABOX           CYPDF_TO_RECT(0.0, 0.0, CYPDF_A9_WIDTH, CYPDF_A9_HEIGHT)

#define CYPDF_A10_WIDTH             (CYPDF_REAL)CYPDF_MM_TO_UU(26)
#define CYPDF_A10_HEIGHT            (CYPDF_REAL)CYPDF_MM_TO_UU(37)
#define CYPDF_A10_MEDIABOX          CYPDF_TO_RECT(0.0, 0.0, CYPDF_A10_WIDTH, CYPDF_A10_HEIGHT)


/* Default user space coordinate. */
#define CYPDF_DEFAULT_POINT         CYPDF_TO_POINT(0, 0)


/* PI */
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif



#endif /* CYPDF_CONSTS_H */
