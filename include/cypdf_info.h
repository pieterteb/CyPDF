#ifndef CYPDF_INFO_H
#define CYPDF_INFO_H


#include <stdbool.h>

#include "cypdf_dict.h"
#include "cypdf_object.h"



#define CYPDF_PRINT_INFO                    CYPDF_PrintInfo
#define CYPDF_FREE_INFO                     CYPDF_FreeInfo


#define CYPDF_INFO_MAX_SIZE                 128


typedef struct CYPDF_ObjInfo {
    CYPDF_ObjHeader header;

    char            title[CYPDF_INFO_MAX_SIZE];             /* The document’s title. */
    char            author[CYPDF_INFO_MAX_SIZE];            /* The name of the person who created the document. */
    char            subject[CYPDF_INFO_MAX_SIZE];           /* The subject of the document. */

    char            creator[CYPDF_INFO_MAX_SIZE];           /* If the document was converted to PDF from another format, the name of the application (for example, VSCode) that created the original document from which it was converted. */
    char            producer[CYPDF_INFO_MAX_SIZE];          /* If the document was converted to PDF from another format, the name of the application (for example, CyProducer) that converted it to PDF. */
    char            creation_date[CYPDF_INFO_MAX_SIZE];     /* The date and time the document was created, in human-readable form. */

    CYPDF_ObjDict*  dict;
} CYPDF_ObjInfo;


/**
 * @brief Creates new CYPDF_ObjInfo.
 * 
 * @param indirect
 * @param title The document’s title.
 * @param author The name of the person who created the document.
 * @param subject The subject of the document.
 * @param creator If the document was converted to PDF from another format, the name of the application (for example, CyPress Editor) that created the original document from which it was converted.
 * @param producer If the document was converted to PDF from another format, the name of the application (for example, CyProducer) that converted it to PDF.
 * @param creation_date The date and time the document was created, in human-readable form.
 * @return CYPDF_Obj_Info* 
 */
CYPDF_ObjInfo* CYPDF_NewInfo(bool indirect, const char* title, const char* author, const char* subject, const char* creator, const char* producer, const char* creation_date);

/**
 * @brief Writes obj to fp.
 * 
 * @param fp 
 * @param obj 
 */
void CYPDF_PrintInfo(FILE* fp, CYPDF_Object* obj);

/**
 * @brief Frees obj.
 * 
 * @param obj 
 */
void CYPDF_FreeInfo(CYPDF_Object* obj);



#endif /* CYPDF_INFO_H */
