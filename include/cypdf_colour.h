#ifndef CYPDF_COLOUR_H
#define CYPDF_COLOUR_H



/* Color space names */

/* DEVICE */
#define CYPDF_CPN_DEVGRAY           "DeviceGray"
#define CYPDF_CPN_DEVRGB            "DeviceRGB"
#define CYPDF_CPN_DEVCMYK           "DeviceCMYK"

/* CIE-BASED */
#define CYPDF_CPN_CIEGRAY           "CalGray"
#define CYPDF_CPN_CIERGB            "CalRGB"
#define CYPDF_CPN_CIELAB            "Lab"
#define CYPDF_CPN_CIEICC            "ICCBased"

/* SPECIAL */
#define CYPDF_CPN_SPECINDEXED       "Indexed"
#define CYPDF_CPN_SPECPATTERN       "Pattern"
#define CYPDF_CPN_SPECSEP           "Separation"
#define CYPDF_CPN_SPECDEVN          "DeviceN"


/* Color space types */
#define CYPDF_CP_DEVGRAY            0x0001
#define CYPDF_CP_DEVRGB             0x0002
#define CYPDF_CP_DEVCMYK            0x0003
#define CYPDF_CP_CIEGRAY            0x0010
#define CYPDF_CP_CIERGB             0x0020
#define CYPDF_CP_CIELAB             0x0030
#define CYPDF_CP_CIEICC             0x0040
#define CYPDF_CP_SPECINDEXED        0x0100
#define CYPDF_CP_SPECPATTERN        0x0200
#define CYPDF_CP_SPECSEP            0x0300
#define CYPDF_CP_SPECDEVN           0x0400

#define CYPDF_CP_DEVICE             0x000F
#define CYPDF_CP_CIE_BASED          0x00F0
#define CYPDF_CP_SPECIAL            0x0F00



#endif /* CYPDF_COLOUR_H */