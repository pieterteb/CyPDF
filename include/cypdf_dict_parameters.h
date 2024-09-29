#ifndef CYPDF_DICT_PARAMETERS_H
#define CYPDF_DICT_PARAMETERS_H



/*
This header file contains all dictionary parameter keywords.
*/



/* General Parameters Keywords */
#define CYPDF_TYPE_K                        "Type"



/* Stream Dictionary */
#define CYPDF_STREAM_LENGTH_K               "Length"
#define CYPDF_STREAM_FILTER_K               "Filter"
#define CYPDF_STREAM_DECODE_PARAMETERS_K    "DecodeParams"
#define CYPDF_STREAM_DECODED_LENGTH_K       "DL"


/* Trailer Dictionary */
#define CYPDF_TRAILER_SIZE_K                "Size"
#define CYPDF_TRAILER_CATALOG_K             "Root"
#define CYPDF_TRAILER_ENCRYPT_K             "Encrypt"
#define CYPDF_TRAILER_INFO_K                "Info"
#define CYPDF_TRAILER_ID_K                  "ID"


/* Info Dictionary Keywords */
#define CYPDF_INFO_TITLE_K                  "Title"
#define CYPDF_INFO_AUTHOR_K                 "Author"
#define CYPDF_INFO_SUBJECT_K                "Subject"
#define CYPDF_INFO_KEYWORDS_K               "Keywords"
#define CYPDF_INFO_CREATOR_K                "Creator"
#define CYPDF_INFO_PRODUCER_K               "Producer"
#define CYPDF_INFO_CREATION_DATE_K          "CreationDate"
#define CYPDF_INFO_MOD_DATE_K               "ModDate"
#define CYPDF_INFO_TRAPPED_K                "Trapped"


/* Catalog Dictionary Keywords */
#define CYPDF_CATALOG_TYPE_K                "Catalog"
#define CYPDF_CATALOG_PAGE_ROOT_K           "Pages"


/* Page Dictionary Keywords */
#define CYPDF_PAGE_TYPE_K                   "Page"
#define CYPDF_PAGE_PARENT_K                 "Parent"
#define CYPDF_PAGE_RESOURCES_K              "Resources"
#define CYPDF_PAGE_MEDIABOX_K               "MediaBox"
#define CYPDF_PAGE_CONTENTS_K               "Contents"


/* Page Node Dictionary Keywords */
#define CYPDF_PAGE_NODE_TYPE_K              "Pages"
#define CYPDF_PAGE_NODE_PARENT_K            "Parent"
#define CYPDF_PAGE_NODE_KIDS                "Kids"
#define CYPDF_PAGE_NODE_COUNT               "Count"


/* Resource Dictionary Keywords */
#define CYPDF_RESOURCE_GFX_STATE_K          "ExtGState"
#define CYPDF_RESOURCE_COLOR_SPACE_K        "ColorSpace"
#define CYPDF_RESOURCE_PATTERN_K            "Pattern"
#define CYPDF_RESOURCE_SHADING_K            "Shading"
#define CYPDF_RESOURCE_XOBJECT_K            "XObject"
#define CYPDF_RESOURCE_FONT_K               "Font"
#define CYPDF_RESOURCE_PROCEDURE_SET_K      "ProcSet"
#define CYPDF_RESOURCE_PROPERTIES_K         "Properties"


/* Graphics State Parameter Dictionary Keywords */
#define CYPDF_GFX_STATE_TYPE_K              "ExtGState"
#define CYPDF_GFX_STATE_LINE_WIDTH_K        "LW"
#define CYPDF_GFX_STATE_LINE_CAP_K          "LC"
#define CYPDF_GFX_STATE_LINE_JOIN_K         "LJ"
#define CYPDF_GFX_STATE_MITER_LIMIT_K       "ML"
#define CYPDF_GFX_STATE_DASH_PATTERN_K      "D"



#endif /* CYPDF_DICT_PARAMETERS_H */
