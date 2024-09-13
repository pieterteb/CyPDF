#ifndef CYPDF_INFO_H
#define CYPDF_INFO_H


#include <stdbool.h>
#include <stdio.h>

#include "cypdf_dict.h"
#include "cypdf_mmgr.h"
#include "cypdf_string.h"
#include "cypdf_object.h"



#define CYPDF_PRINT_INFO                    CYPDF_PrintInfo
#define CYPDF_FREE_INFO                     CYPDF_FreeInfo


#define CYPDF_INFO_MAX_SIZE                 128


typedef struct CYPDF_ObjInfo {
    CYPDF_ObjHeader     header;

    CYPDF_ObjString*    title;             /* The document’s title. */
    CYPDF_ObjString*    author;            /* The name of the person who created the document. */
    CYPDF_ObjString*    subject;           /* The subject of the document. */

    CYPDF_ObjString*    creator;           /* If the document was converted to PDF from another format, the name of the application (for example, VSCode) that created the original document from which it was converted. */
    CYPDF_ObjString*    producer;          /* If the document was converted to PDF from another format, the name of the application (for example, CyProducer) that converted it to PDF. */
    CYPDF_ObjString*    creation_date;     /* The date and time the document was created, in human-readable form. */

    CYPDF_ObjDict*      dict;
} CYPDF_ObjInfo;


CYPDF_ObjInfo* CYPDF_NewInfo(CYPDF_MMgr* const mmgr, char title[static 1], char author[static 1], char subject[static 1], char creator[static 1], char producer[static 1], char creation_date[restrict static 1]);

void CYPDF_PrintInfo(FILE* restrict fp, const CYPDF_Object* const obj);

void CYPDF_FreeInfo(CYPDF_Object* obj);



#endif /* CYPDF_INFO_H */
