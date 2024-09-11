#ifndef CYPDF_OBJECT_H
#define CYPDF_OBJECT_H


#include <stdbool.h>
#include <stdint.h>

#include "cypdf_types.h"



enum CYPDF_OCLASS {
    CYPDF_OCLASS_NULL = 0,
    CYPDF_OCLASS_BOOL,
    CYPDF_OCLASS_NUMBER,
    CYPDF_OCLASS_REAL,
    CYPDF_OCLASS_STRING,
    CYPDF_OCLASS_NAME,
    CYPDF_OCLASS_ARRAY,
    CYPDF_OCLASS_DICT,
    CYPDF_OCLASS_STREAM,        /* A stream is always an indirect object. */

    CYPDF_OCLASS_INFO,
    CYPDF_OCLASS_CATALOG,
    CYPDF_OCLASS_PAGE,
    CYPDF_OCLASS_PNODE,

    CYPDF_OCLASS_COUNT,

    CYPDF_OCLASS_NONE,
    CYPDF_OCLASS_UNKNOWN,
};


#define CYPDF_DEFAULT_ONUM              0x00000000          /* Used for direct objects. */
#define CYPDF_DEFAULT_OGEN              0x0000


typedef struct CYPDF_ObjHeader {
    bool                indirect;
    enum CYPDF_OCLASS   class;
    uint32_t            onum;
    uint16_t            ogen;
} CYPDF_ObjHeader;


/**
 * @brief Creates a new CYPDF_Object.
 * 
 * @param indirect 
 * @param class
 * @return CYPDF_Object* | Returns NULL if header creation fails.
 */
CYPDF_Object* CYPDF_NewObj(bool indirect, enum CYPDF_OCLASS class);

void CYPDF_ObjSetOnum(CYPDF_Object* obj, uint32_t onum);

/**
 * @brief Checks whether obj is direct or not.
 * 
 * @param obj 
 * @return CYPDF_BOOL | Returns CYPDF_FALSE if obj is NULL.
 */
bool CYPDF_ObjIsDirect(CYPDF_Object* obj);

/**
 * @brief Gets the class of obj.
 * 
 * @param obj 
 * @return enum CYPDF_OCLASS | Returns CYPDF_OCLASS_NONE if obj is NULL.
 */
enum CYPDF_OCLASS CYPDF_ObjGetClass(CYPDF_Object* obj);

/**
 * @brief Gets the ID of obj.
 * 
 * @param obj 
 * @return CYPDF_UINT32 | Returns CYPDF_DEFAULT_OID if obj is NULL.
 */
uint32_t CYPDF_ObjGetOnum(CYPDF_Object* obj);

/**
 * @brief Gets the generation number of obj.
 * 
 * @param obj 
 * @return CYPDF_UINT16 | Returns CYPDF_DEFAULT_OGEN if obj is NULL.
 */
uint16_t CYPDF_ObjGetOgen(CYPDF_Object* obj);

/**
 * @brief Gets the write function belonging to obj.
 * 
 * @param obj 
 * @return CYPDF_Write_Func | Returns NULL if obj is NULL.
 */
CYPDF_PrintFunc CYPDF_ObjGetPrint(CYPDF_Object* obj);

/**
 * @brief Gets the free function belonging to obj.
 * 
 * @param obj 
 * @return CYPDF_Free_Func | Returns NULL if obj is NULL.
 */
CYPDF_FreeFunc CYPDF_ObjGetFree(CYPDF_Object* obj);

/**
 * @brief Writes obj as a direct object. Writes nothing if fp == NULL or obj == NULL.
 * 
 * @param fp Stream to be written to.
 * @param obj 
 */
void CYPDF_PrintObjDirect(FILE* fp, CYPDF_Object* obj);

/**
 * @brief Writes obj as an object definition to fp. Writes nothing if fp == NULL or obj == NULL or if obj is not indirect.
 * 
 * @param fp Stream to be written to.
 * @param obj 
 */
void CYPDF_PrintObjDef(FILE* fp, CYPDF_Object* obj);

/**
 * @brief Writes obj as an object reference to fp. Does nothing if fp == NULL or obj == NULL or if obj is not indirect.
 * 
 * @param fp Stream to be written to.
 * @param obj 
 */
void CYPDF_PrintObjRef(FILE* fp, CYPDF_Object* obj);

/**
 * @brief Frees obj. Does nothing if obj is NULL or if obj is indirect and ifIndirect is false.
 * 
 * @param obj 
 * @param ifIndirect If true, allows for obj to be freed even if it is indirect. Use with caution.
 */
void CYPDF_FreeObj(CYPDF_Object* obj, bool ifIndirect);



#endif /* CYPDF_OBJECT_H */
