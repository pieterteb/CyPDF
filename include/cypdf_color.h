#ifndef CYPDF_COLOR_H
#define CYPDF_COLOR_H



/* Color Space Keywords */

/* DEVICE */
#define CYPDF_COLOR_SPACE_DEVGRAY_K     "DeviceGray"
#define CYPDF_COLOR_SPACE_DEVRGB_K      "DeviceRGB"
#define CYPDF_COLOR_SPACE_DEVCMYK_K     "DeviceCMYK"

/* CIE-BASED */
#define CYPDF_COLOR_SPACE_CIEGRAY_K     "CalGray"
#define CYPDF_COLOR_SPACE_CIERGB_K      "CalRGB"
#define CYPDF_COLOR_SPACE_CIELAB_K      "Lab"
#define CYPDF_COLOR_SPACE_CIEICC_K      "ICCBased"

/* SPECIAL */
#define CYPDF_COLOR_SPACE_INDEXED_K     "Indexed"
#define CYPDF_COLOR_SPACE_PATTERN_K     "Pattern"
#define CYPDF_COLOR_SPACE_SEPARATION_K  "Separation"
#define CYPDF_COLOR_SPACE_DEVICEN_K     "DeviceN"


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