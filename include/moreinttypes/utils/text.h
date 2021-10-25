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
#define strncasecmp strncmp
#endif /* c89/90 GNU compiler */

#ifdef _MSC_VER
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#endif /* _MSC_VER */

#ifndef NULL
/* clang-format off */
#define NULL ((void*)0)
/* clang-format on */
#endif

#ifdef __cplusplus
extern "C" {
#endif
/** @ingroup text
 *  @{
 */
/** Appends text to a string.
 * @param[out] dest Target buffer &mdash; <em>make sure it's initialized!</em>
 * @param[in] src Text to append.
 * @param[in] lim Total size of target buffer.
 */
MOREINTTYPES_EXPORTS void append_string(char* dest, const char* src,
                                        size_t lim);

/** Removes all ASCII newline chars from the end of a string.
 *  @param pstr Pointer to a string.
 */
MOREINTTYPES_EXPORTS void chomp(char(*pstr));

/** Writes a copy of @p src to @p dest with leading whitespace removed.
 *  @param[out] dest Target buffer.
 *  @param[in] src Pointer to a read-only string.
 */
MOREINTTYPES_EXPORTS void ltrim_s(char(*dest), const char(*src));

/** Writes a copy of @p src to @p dest with trailing whitespace removed.
 *  @param[out] dest Target buffer.
 *  @param[in] src Pointer to a read-only string.
 */
MOREINTTYPES_EXPORTS void rtrim_s(char(*dest), const char(*src));

/** Writes a copy of @p src to @p dest with all surrounding whitespace removed.
 *  @param[out] dest Target buffer.
 *  @param[in] src Pointer to a read-only string.
 */
MOREINTTYPES_EXPORTS void trim_s(char(*dest), const char(*src));
/** @} */
#ifdef __cplusplus
}
#endif

/** @ingroup text
 *  @{
 */
/** Removes leading whitespace chars from a string.
 *  @param pstr Pointer to a string.
 */
#define ltrim(pstr) ltrim_s(pstr, NULL);

/** Removes trailing whitespace chars from a string.
 *  @param pstr Pointer to a string.
 */
#define rtrim(pstr) rtrim_s(pstr, NULL);

/** Removes all surrounding whitespace chars from a string.
 *  @param pstr Pointer to a string.
 */
#define trim(pstr) trim_s(pstr, NULL);
/** @} */

#endif /* !STRING_UTILS_H */
