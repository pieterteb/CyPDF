#ifndef CYPDF_INFO_H
#define CYPDF_INFO_H


#include "cypdf_dict.h"
#include "cypdf_memory.h"



#define CYPDF_INFO_MAX_SIZE                 128


typedef CYPDF_ObjDict CYPDF_ObjInfo;


CYPDF_ObjInfo* CYPDF_NewInfo(CYPDF_MemMgr* const restrict memmgr, char title[static 1], char author[static 1], char subject[static 1], char creator[static 1], char producer[static 1], char creation_date[restrict static 1]);



#endif /* CYPDF_INFO_H */
