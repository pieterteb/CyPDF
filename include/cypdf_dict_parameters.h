#ifndef CYPDF_DICT_PARAMETERS_H
#define CYPDF_DICT_PARAMETERS_H



/*
This header file contains all dictionary parameter keywords and indices. Keywords have suffix _K and indices have suffic _I.
*/



/* General Parameters Keywords */
#define CYPDF_TYPE_K                        "Type"

#define CYPDF_TYPE_I                        0



/* Stream Dictionary */
#define CYPDF_STREAM_LENGTH_K               "Length"
#define CYPDF_STREAM_FILTER_K               "Filter"
#define CYPDF_STREAM_DECODE_PARAMETERS_K    "DecodeParams"
#define CYPDF_STREAM_DECODED_LENGTH_K       "DL"

#define CYPDF_STREAM_LENGTH_I               0
#define CYPDF_STREAM_FILTER_I               CYPDF_STREAM_LENGTH_I + 1
#define CYPDF_STREAM_DECODE_PARAMETERS_I    CYPDF_STREAM_FILTER_I + 1
#define CYPDF_STREAM_DECODED_LENGTH_I       CYPDF_STREAM_DECODE_PARAMETERS_I + 1


/* Trailer Dictionary */
#define CYPDF_TRAILER_SIZE_K                "Size"
#define CYPDF_TRAILER_CATALOG_K             "Root"
#define CYPDF_TRAILER_ENCRYPT_K             "Encrypt"
#define CYPDF_TRAILER_INFO_K                "Info"
#define CYPDF_TRAILER_ID_K                  "ID"

#define CYPDF_TRAILER_SIZE_I                0
#define CYPDF_TRAILER_CATALOG_I             1
#define CYPDF_TRAILER_ENCRYPT_I             2
#define CYPDF_TRAILER_INFO_I                3
#define CYPDF_TRAILER_ID_I                  4


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

#define CYPDF_INFO_TITLE_I                  0
#define CYPDF_INFO_AUTHOR_I                 1
#define CYPDF_INFO_SUBJECT_I                2
#define CYPDF_INFO_KEYWORDS_I               3
#define CYPDF_INFO_CREATOR_I                4
#define CYPDF_INFO_PRODUCER_I               5
#define CYPDF_INFO_CREATION_DATE_I          6
#define CYPDF_INFO_MOD_DATE_I               7
#define CYPDF_INFO_TRAPPED_I                8


/* Catalog Dictionary Keywords */
#define CYPDF_CATALOG_TYPE_K                "Catalog"
#define CYPDF_CATALOG_PAGE_ROOT_K           "Pages"

#define CYPDF_CATALOG_PAGE_ROOT_I           1


/* Page Dictionary Keywords */
#define CYPDF_PAGE_TYPE_K                   "Page"
#define CYPDF_PAGE_PARENT_K                 "Parent"
#define CYPDF_PAGE_RESOURCES_K              "Resources"
#define CYPDF_PAGE_MEDIABOX_K               "MediaBox"
#define CYPDF_PAGE_CONTENTS_K               "Contents"

#define CYPDF_PAGE_PARENT_I                 1
#define CYPDF_PAGE_RESOURCES_I              2
#define CYPDF_PAGE_MEDIABOX_I               3
#define CYPDF_PAGE_CONTENTS_I               4


/* Page Node Dictionary Keywords */
#define CYPDF_PAGE_NODE_TYPE_K              "Pages"
#define CYPDF_PAGE_NODE_PARENT_K            "Parent"
#define CYPDF_PAGE_NODE_KIDS_K              "Kids"
#define CYPDF_PAGE_NODE_COUNT_K             "Count"

#define CYPDF_PAGE_NODE_PARENT_I            1
#define CYPDF_PAGE_NODE_KIDS_I              2
#define CYPDF_PAGE_NODE_COUNT_I             3


/* Resource Dictionary Keywords */
#define CYPDF_RESOURCE_GFX_STATE_K          "ExtGState"
#define CYPDF_RESOURCE_COLOR_SPACE_K        "ColorSpace"
#define CYPDF_RESOURCE_PATTERN_K            "Pattern"
#define CYPDF_RESOURCE_SHADING_K            "Shading"
#define CYPDF_RESOURCE_XOBJECT_K            "XObject"
#define CYPDF_RESOURCE_FONT_K               "Font"
#define CYPDF_RESOURCE_PROCEDURE_SET_K      "ProcSet"
#define CYPDF_RESOURCE_PROPERTIES_K         "Properties"

#define CYPDF_RESOURCE_GFX_STATE_I          0
#define CYPDF_RESOURCE_COLOR_SPACE_I        1
#define CYPDF_RESOURCE_PATTERN_I            2
#define CYPDF_RESOURCE_SHADING_I            3
#define CYPDF_RESOURCE_XOBJECT_I            4
#define CYPDF_RESOURCE_FONT_I               5
#define CYPDF_RESOURCE_PROCEDURE_SET_I      6
#define CYPDF_RESOURCE_PROPERTIES_I         7


/* Graphics State Parameter Dictionary Keywords */
#define CYPDF_GFX_STATE_TYPE_K              "ExtGState"
#define CYPDF_GFX_STATE_LINE_WIDTH_K        "LW"
#define CYPDF_GFX_STATE_LINE_CAP_K          "LC"
#define CYPDF_GFX_STATE_LINE_JOIN_K         "LJ"
#define CYPDF_GFX_STATE_MITER_LIMIT_K       "ML"
#define CYPDF_GFX_STATE_DASH_PATTERN_K      "D"

#define CYPDF_GFX_STATE_LINE_WIDTH_I        1
#define CYPDF_GFX_STATE_LINE_CAP_I          2
#define CYPDF_GFX_STATE_LINE_JOIN_I         3
#define CYPDF_GFX_STATE_MITER_LIMIT_I       4
#define CYPDF_GFX_STATE_DASH_PATTERN_I      5


/* External Object Dictionary Keywords */
#define CYPDF_XOBJECT_SUBTYPE_K             "Subtype"

#define CYPDF_XOBJECT_SUBTYPE_I             CYPDF_STREAM_DECODED_LENGTH_I + 1



#endif /* CYPDF_DICT_PARAMETERS_H */
