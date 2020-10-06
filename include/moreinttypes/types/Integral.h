/**
 *  @file Integral.h
 *  @defgroup int_interface Integral
 */
#ifndef INTEGRAL_H
#define INTEGRAL_H 1

#include <moreinttypes/utils.h>

/**
 *  @defgroup int_fn_wrappers Interface
 *  @ingroup int_interface
 *  @brief Simplifies manipulation of integer types
 *  @details These function macros accept any integral type, i.e., any `struct`
 *  representing an integer.
 *  @{
 */

/** Returns the factorial of the given integer type.
 *  @param i An integer type.
 *  @returns The factorial of `i`, if computable, otherwise `0`.
 */
#define factorial(i) (i.n_bang(&i))

/** Tries to set the value of the given integer type by parsing a numeric
 *  string.
 *  @param i    An integer type.
 *  @param str  A string representation of an integral value.
 *  @param b    The radix to use when parsing `str`.
 */
#define from_string(i, str, b) (i.parse(&i, str, b))

/** Returns the binary equivalent of the given integer type as a string.
 *  @param i An integer type.
 *  @return A string representation of `i` in base-2 notation.
 */
#define as_binary(i) (i.to_bin(&i))
/** @} */
#endif /* !INTEGRAL_H */
