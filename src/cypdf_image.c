#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cypdf_image.h"
#include "cypdf_color.h"
#include "cypdf_dict.h"
#include "cypdf_dict_parameters.h"
#include "cypdf_integer.h"
#include "cypdf_log.h"
#include "cypdf_memory.h"
#include "cypdf_print.h"
#include "cypdf_utils.h"
#include "cypdf_xobject.h"



static void PNGProcessIHDR(CYPDF_ObjImage* const image, FILE* png);

static void PNGProcessIDAT(CYPDF_Channel* const image_channel, FILE* restrict png, const size_t buff_size, unsigned char buffer[restrict buff_size]);

static void ImagePNG(CYPDF_ObjImage* const image, FILE* png);


CYPDF_ObjImage* CYPDF_NewImage(CYPDF_MemMgr* restrict const memmgr, const char path[restrict static 1]) {
    CYPDF_TRACE;

    CYPDF_ObjImage* image = CYPDF_NewXObject(memmgr, CYPDF_XOBJECT_IMAGE);
    
    FILE* image_file = fopen(path, "rb");
    if (!image_file) {
        fprintf(stderr, "Could not open image file: %s\n", path);
    }

    char* extension = strrchr(path, '.') + 1;
    if (!extension) {
        fprintf(stderr, "Unimplemented image file type: %s\n", extension);
    }

    if (!strcmp(extension, "png")) {
        ImagePNG(image, image_file);
    } else {
        fprintf(stderr, "Unimplemented image file type: %s\n", extension);
    }

    fclose(image_file);

    return image;
}


static void PNGProcessIHDR(CYPDF_ObjImage* const image, FILE* png) {
    CYPDF_TRACE;

    uint32_t chunk_length = 0;
    char chunk_type[5] = { 0 };
    fread(&chunk_length, sizeof(uint32_t), 1, png);
#ifdef CYPDF_LITTLE_ENDIAN
    chunk_length = CYPDF_Bswap32(chunk_length);
#endif /* CYPDF_LITTLE_ENDIAN */
    fread(chunk_type, sizeof(char), 4, png);

    uint32_t width = 0;
    uint32_t height = 0;
    unsigned char bit_depth = 0;
    unsigned char color_type = 0;
    fread(&width, sizeof(uint32_t), 1, png);
    fread(&height, sizeof(uint32_t), 1, png);
#ifdef CYPDF_LITTLE_ENDIAN
    width = CYPDF_Bswap32(width);
    height = CYPDF_Bswap32(height);
#endif /* CYPDF_LITTLE_ENDIAN */
    fread(&bit_depth, sizeof(unsigned char), 1, png);
    fread(&color_type, sizeof(unsigned char), 1, png);
    fread(chunk_type, sizeof(char), 3, png);    /* Consume unused info. */
    CYPDF_DictSetAtIndex(image->dict, CYPDF_IMAGE_WIDTH_I, CYPDF_IMAGE_WIDTH_K, CYPDF_NewInteger(image->dict->memmgr, (int)width));
    CYPDF_DictSetAtIndex(image->dict, CYPDF_IMAGE_HEIGHT_I, CYPDF_IMAGE_HEIGHT_K, CYPDF_NewInteger(image->dict->memmgr, (int)height));
    CYPDF_DictSetAtIndex(image->dict, CYPDF_IMAGE_BITS_PER_COMPONENT_I, CYPDF_IMAGE_BITS_PER_COMPONENT_K, CYPDF_NewInteger(image->dict->memmgr, bit_depth));

    CYPDF_ObjName* color_space = NULL;
    if (color_type & 2) {
        color_space = CYPDF_NewName(image->dict->memmgr, CYPDF_COLOR_SPACE_DEVRGB_K);
    } else {
        color_space = CYPDF_NewName(image->dict->memmgr, CYPDF_COLOR_SPACE_DEVGRAY_K);
    }
    CYPDF_DictSetAtIndex(image->dict, CYPDF_IMAGE_COLOR_SPACE_I, CYPDF_IMAGE_COLOR_SPACE_K, color_space);
    if (color_type & 1 || color_type & 4) {
        fprintf(stderr, "WARNING: Can't process alpha or indexed type png's. Program might crash.\n");
    }
}

static void PNGProcessIDAT(CYPDF_Channel* const image_channel, FILE* restrict png, const size_t buff_size, unsigned char buffer[restrict buff_size]) {
    /* Skip excess information and go to image data. Actual image data is contained by IDAT chunks. */
    uint32_t chunk_length = 0;
    char chunk_type[5] = { 0 };
    while (strcmp("IDAT", chunk_type)) {
        fread(buffer, sizeof(unsigned char), chunk_length + 4, png); /* Consume Chunk Data and CRC. */
        fread(&chunk_length, sizeof(uint32_t), 1, png);
#ifdef CYPDF_LITTLE_ENDIAN
        chunk_length = CYPDF_Bswap32(chunk_length);
#endif /* CYPDF_LITTLE_ENDIAN */
        fread(chunk_type, sizeof(char), 4, png);
    }

    /* IEND marks the end of the image. */
    while (strcmp("IEND", chunk_type)) {
        for (size_t i = 0; i < chunk_length / buff_size; ++i) {
            fread(buffer, sizeof(unsigned char), buff_size, png);
            CYPDF_ChannelWrite(image_channel, buffer, sizeof(unsigned char), buff_size);
        }
        fread(buffer, sizeof(unsigned char), chunk_length % buff_size, png);
        CYPDF_ChannelWrite(image_channel, buffer, sizeof(unsigned char), chunk_length % buff_size);
        fread(buffer, sizeof(unsigned char), 4, png);   /* Consume CRC. */
        fread(&chunk_length, sizeof(uint32_t), 1, png);
#ifdef CYPDF_LITTLE_ENDIAN
        chunk_length = CYPDF_Bswap32(chunk_length);
#endif /* CYPDF_LITTLE_ENDIAN */
        fread(chunk_type, sizeof(char), 4, png);
    }
}

static void ImagePNG(CYPDF_ObjImage* const image, FILE* png) {
    /* PNG Chunk Format:
    
        Length   |   Chunk Type  |    Chunk Data   |   CRC
        ------------------------------------------------------
        4 bytes  |    4 bytes    |   Length bytes  |   4 bytes
    
    */
    CYPDF_TRACE;

    CYPDF_Channel* image_channel = CYPDF_NewChannel(image, CYPDF_CHANNEL_OBJSTREAM);

    const size_t buff_size = 1024;
    unsigned char buffer[buff_size];
    fread(buffer, sizeof(unsigned char), 8, png);   /* Consume png header bytes. */

    /* First chunk is IHDR which contains width, height, bit depth and color type. */
    PNGProcessIHDR(image, png);
    PNGProcessIDAT(image_channel, png, buff_size, buffer);

    free(image_channel);
}
