/**
 *  @file numeric.h
 *  @defgroup numeric Math Lib
 *  @brief Functions for integral math
 */
#ifndef NUMERIC_H
#define NUMERIC_H 1

/* https://github.com/doxygen/doxygen/issues/6856#issuecomment-467020583 */
#ifdef __DOXYGEN__
#define USE_64_BITS 1
#endif
/**
 * @ingroup numeric
 * @def USE_64_BITS
 * When defined, exposes 64-bit versions of this library's functions.
 * @remarks Must be defined before including `moreinttypes/core.h` or
 * `moreinttypes/utils.h`
 *
 * @def MATCH_ARCH
 * Returns the appropriate function name based on the expected integer type.
 * Names will be appended with "_64" if #USE_64_BITS has been set.
 */

/**
 * @ingroup numeric
 * @{
 */
#ifndef USE_64_BITS
#define MATCH_ARCH(func_name) func_name
#else
#define MATCH_ARCH(func_name) func_name##_64
#endif
/** @} */

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @ingroup numeric
 * @{
 */
/** Returns the factorial of an unsigned integer.
 *  @param n An unsigned integer.
 *  @returns The factorial of `n`, if computable, otherwise `0`.
 *  @details The range of representable return values will depend on the bit
 *  width of the host system's `long double` type.
 *  A rough estimate:
 * <table>
 *  <tr>
 *   <th>Size (bytes)</th>
 *   <th>Computable input values</th>
 *  </tr>
 *  <tr>
 *   <th colspan="2">32-bit</th>
 *  </tr>
 *  <tr>
 *    <td>`8`</td>
 *    <td>`<= 170`</td>
 *  </tr>
 *  <tr>
 *     <td>`12`</td>
 *     <td>`<= 1754`</td>
 *  </tr>
 *  <tr>
 *   <th colspan="2">64-bit</th>
 *  </tr>
 *  <tr>
 *    <td>`16`</td>
 *    <td>`<= 1754`</td>
 *  </tr>
 * </table>
 *  @remarks Signed arguments will be cast to their unsigned equivalents.
 *  Integer overflows are signalled by an error message and a `0` return value.
 */
MOREINTTYPES_EXPORTS long double factorial_of(uint32_t n);
/** @copydoc ::factorial_of */
MOREINTTYPES_EXPORTS long double factorial_of_64(uint64_t n);

/** Returns the integral value represented by the given numeric string.
 *  @param str  A string representation of an integral value.
 *  @param base The radix to use when parsing `str`.
 *  @return The integral value of `str`, otherwise `0`.
 */
MOREINTTYPES_EXPORTS int32_t parse_int(const char* str, int base);
/** @copydoc ::parse_int */
MOREINTTYPES_EXPORTS uint32_t parse_uint(const char* str, int base);
/** @copydoc ::parse_int */
MOREINTTYPES_EXPORTS int64_t parse_int_64(const char* str, int base);
/** @copydoc ::parse_int
 *  @remarks Negative values will be cast to their 2's complement by implicit
 * type conversion.
 */
MOREINTTYPES_EXPORTS uint64_t parse_uint_64(const char* str, int base);

/** Returns true if and only if the given string represents the given value.
 *  @param str  A string representation of an integral value.
 *  @param val The value returned after parsing @p str.
 *  @return True if @p val really is the value represented by @p str.
 */
MOREINTTYPES_EXPORTS bool parse_succeeded(const char* str, const int64_t val);

/** Converts an integer to a string representation of its binary equivalent,
 *  formatted in space-separated nibbles.
 *  @param buffer A string buffer to use as scratch memory.
 *  @param n      An integer.
 *  @return A formatted string representation of `n` in base-2 notation.
 *  @remarks Negative values will be cast to their 2's complement by implicit
 * type conversion.
 */
MOREINTTYPES_EXPORTS const char* binary_string(char* buffer, uint32_t n);
/** @copydoc ::binary_string */
MOREINTTYPES_EXPORTS const char* binary_string_64(char* buffer, uint64_t n);
/** @} */
#ifdef __cplusplus
}
#endif

#endif /* !NUMERIC_H */
