#ifndef CYPDF_COLOR_H
#define CYPDF_COLOR_H



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


enum CYPDF_COLOR_SPACE_TYPE {
    CYPDF_COLOR_SPACE_DEVGRAY,
    CYPDF_COLOR_SPACE_DEVRGB,
    CYPDF_COLOR_SPACE_DEVCMYK,
    CYPDF_COLOR_SPACE_CIERGB,
    CYPDF_COLOR_SPACE_CIELAB,
    CYPDF_COLOR_SPACE_CIEICC,
    CYPDF_COLOR_SPACE_INDEXED,
    CYPDF_COLOR_SPACE_PATTERN,
    CYPDF_COLOR_SPACE_SEPARATION,
    CYPDF_COLOR_SPACE_DEVICEN,

    CYPDF_COLOR_SPACE_COUNT,
};

#define CYPDF_COLOR_SPACE_DEFAULT       CYPDF_COLOR_SPACE_DEVGRAY



/* Currently, only the device color spaces are supported. These don't require any additional parameters. */
typedef struct CYPDF_ColorSpace {
    enum CYPDF_COLOR_SPACE_TYPE type;
    // union {
        
    // }                        params;
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