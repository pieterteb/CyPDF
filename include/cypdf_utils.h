#ifndef CYPDF_UTILS_H
#define CYPDF_UTILS_H


#include "cypdf_types.h"



#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    #define CYPDF_LITTLE_ENDIAN
#elif defined(__BYTE_ORDER__) && __BYTE_ORDER == __ORDER_BIG_ENDIAN__
    #define CYPDF_BIG_ENDIAN
#else
    #error "Unable to determine endianness."
#endif /* defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */


#if defined(__GNUC__) || defined(__clang__)
    #define CYPDF_HAS_BUILTIN_BSWAP16
    #define CYPDF_HAS_BUILTIN_BSWAP32
    #define CYPDF_HAS_BUILTIN_BSWAP64
#endif /* defined(__GNUC__) || defined(__clang__) */

#ifdef CYPDF_HAS_BUILTIN_BSWAP16
    #define CYPDF_Bswap16(x) __builtin_bswap16(x)
    #undef CYPDF_HAS_BUILTIN_BSWAP16
#else /* Not CYPDF_HAS_BUILTIN_BSWAP16 */
    static inline CYPDF_Bswap16(uint16_t x) {
        return x >> 8 | x << 8;
    }
#endif /* CYPDF_HAS_BUILTIN_BSWAP16 */

#ifdef CYPDF_HAS_BUILTIN_BSWAP32
    #define CYPDF_Bswap32(x) __builtin_bswap32(x)
    #undef CYPDF_HAS_BUILTIN_BSWAP32
#else /* Not CYPDF_HAS_BUILTIN_BSWAP32 */
    static inline CYPDF_Bswap32(uint32_t x) {
        return (x & 0x000000FFU) << 24 |
               (x & 0x0000FF00U) << 8  |
               (x & 0x00FF0000U) >> 8  |
               (x & 0xFF000000U) >> 24;
    }
#endif /* CYPDF_HAS_BUILTIN_BSWAP32 */

#ifdef CYPDF_HAS_BUILTIN_BSWAP64
    #define CYPDF_BSwap64(x) __builtin_bswap64(x)
    #undef CYPDF_HAS_BUILTIN_BSWAP64
#else /* Not CYPDF_HAS_BUILTIN_BSWAP64 */
    static inline CYPDF_Bswap64(uint64_t x) {
        return (x & 0x00000000000000FFULL) << 56 |
               (x & 0x000000000000FF00ULL) << 40 |
               (x & 0x0000000000FF0000ULL) << 24 |
               (x & 0x00000000FF000000ULL) << 8  |
               (x & 0x000000FF00000000ULL) >> 8  |
               (x & 0x0000FF0000000000ULL) >> 24 |
               (x & 0x00FF000000000000ULL) >> 40 |
               (x & 0xFF00000000000000ULL) >> 56;
    }
#endif /* CYPDF_HAS_BUILTIN_BSWAP64 */



CYPDF_TransMatrix* CYPDF_TransMatrixTranslate(CYPDF_TransMatrix* const mat, const CYPDF_Point origin);

CYPDF_TransMatrix* CYPDF_TransMatrixScale(CYPDF_TransMatrix* const mat, const float scale_x, const float scale_y);

CYPDF_TransMatrix* CYPDF_TransMatrixRotate(CYPDF_TransMatrix* const mat, const float angle);

CYPDF_TransMatrix* CYPDF_TransMatrixSkew(CYPDF_TransMatrix* const mat, const float skew_x, const float skew_y);



#endif /* CYPDF_UTILS_H */
