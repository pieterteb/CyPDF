#ifndef CYPDF_COLOR_H
#define CYPDF_COLOR_H


#include <stdint.h>



/* Color space names */

/* DEVICE */
#define CYPDF_COLOR_SPACE_DEVGRAY_N     "DeviceGray"
#define CYPDF_COLOR_SPACE_DEVRGB_N      "DeviceRGB"
#define CYPDF_COLOR_SPACE_DEVCMYK_N     "DeviceCMYK"

/* CIE-BASED */
#define CYPDF_COLOR_SPACE_CIEGRAY_N     "CalGray"
#define CYPDF_COLOR_SPACE_CIERGB_N      "CalRGB"
#define CYPDF_COLOR_SPACE_CIELAB_N      "Lab"
#define CYPDF_COLOR_SPACE_CIEICC_N      "ICCBased"

/* SPECIAL */
#define CYPDF_COLOR_SPACE_INDEXED_N     "Indexed"
#define CYPDF_COLOR_SPACE_PATTERN_N     "Pattern"
#define CYPDF_COLOR_SPACE_SEPARATION_N  "Separation"
#define CYPDF_COLOR_SPACE_DEVICEN_N     "DeviceN"


/* Color space types */
#define CYPDF_COLOR_SPACE_DEVGRAY       0x0001
#define CYPDF_COLOR_SPACE_DEVRGB        0x0002
#define CYPDF_COLOR_SPACE_DEVCMYK       0x0003
#define CYPDF_COLOR_SPACE_CIEGRAY       0x0010
#define CYPDF_COLOR_SPACE_CIERGB        0x0020
#define CYPDF_COLOR_SPACE_CIELAB        0x0030
#define CYPDF_COLOR_SPACE_CIEICC        0x0040
#define CYPDF_COLOR_SPACE_INDEXED       0x0100
#define CYPDF_COLOR_SPACE_PATTERN       0x0200
#define CYPDF_COLOR_SPACE_SEPARATION    0x0300
#define CYPDF_COLOR_SPACE_DEVICEN       0x0400

#define CYPDF_COLOR_SPACE_DEVICE        0x000F
#define CYPDF_COLOR_SPACE_CIE_BASED     0x00F0
#define CYPDF_COLOR_SPACE_SPECIAL       0x0F00

#define CYPDF_COLOR_SPACE_DEFAULT       CYPDF_COLOR_SPACE_DEVGRAY



/* Currently, only the device color spaces are supported. These don't require any additional parameters. */
typedef struct CYPDF_ColorSpace {
    uint16_t    type;
    // union {
        
    // }           params;
} CYPDF_ColorSpace;


typedef struct CYPDF_RGB {
    float   red;
    float   green;
    float   blue;
} CYPDF_RGB;

typedef struct CYPDF_CMYK {
    float   cyan;
    float   magenta;
    float   yellow;
    float   black;
} CYPDF_CMYK;



#endif /* CYPDF_COLOR_H */