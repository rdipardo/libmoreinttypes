/**
 *  @file text.h
 *  @defgroup text String Lib
 *  @brief String manipulation functions
 */
#ifndef STRING_UTILS_H
#define STRING_UTILS_H 1

#include <stddef.h>

/**
 * @ingroup text
 * @def MAX_LEN
 * Maximum allowed length of a string, when appending to it.
 */
#define MAX_LEN 4096U

#if __STDC_VERSION__ < 199901L && !_MSC_VER && !__MINGW32__
#    define strncasecmp strncmp
#endif /* c89/90 GNU compiler */

#ifdef _MSC_VER
#    define strncasecmp _strnicmp
#    define strcasecmp _stricmp
#endif /* _MSC_VER */

#ifdef __cplusplus
extern "C" {
#endif
/** @ingroup text
 *  @{
 */
/** Appends text to a string.
 * @param dest Target buffer &mdash; <em>make sure it's been initialized!</em>
 * @param src Text to append.
 * @param lim Total size of target buffer.
 */
MOREINTTYPES_EXPORTS void
    append_string(char* dest, const char* src, size_t lim);

/** Removes the newline from the end of a string.
 *  @param pstr Pointer to a string.
 */
MOREINTTYPES_EXPORTS void chomp(char(*pstr));

/** Removes leading whitespace chars from a string.
 *  @param pstr Pointer to a string.
 */
MOREINTTYPES_EXPORTS void ltrim(char(*pstr));

/** Removes trailing whitespace chars from a string.
 *  @param pstr Pointer to a string.
 */
MOREINTTYPES_EXPORTS void rtrim(char(*pstr));

/** Removes all surrounding whitespace chars from a string.
 *  @param pstr Pointer to a string.
 */
MOREINTTYPES_EXPORTS void trim(char(*pstr));
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* !STRING_UTILS_H */
