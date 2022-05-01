/**
 *  @file Sbyte.h
 *  @defgroup sbyte_class Sbyte
 */
#ifndef SBYTE_H
#define SBYTE_H 1

#include "Integral.h"

#ifdef __cplusplus
extern "C" {
#endif
/** Encapsulates a signed 8-bit integer. */
typedef struct Sbyte {
    /** The underlying value of this Sbyte */
    const int8_t value;
    /** Attempts to set the value of this Sbyte by parsing a numeric string. */
    void (*parse)(struct Sbyte* const restrict, const char*, int);
    /** Returns the factorial of this Sbyte's value. */
    long double (*n_bang)(struct Sbyte* const restrict);
    /** Returns the base-2 representation of this Sbyte's value as a string. */
    const char* (*to_bin)(struct Sbyte* const restrict);
} Sbyte;

MOREINTTYPES_EXPORTS Sbyte ConstructSbyte(const int8_t value);

#ifdef __cplusplus
}
#endif

/**
 *  @defgroup sbyte_ctor Constructor
 *  @ingroup sbyte_class
 *  @{
 */
/** Returns an initialized Sbyte `struct`. */
#define sbyte(x) ConstructSbyte(x)
/** @} */

#endif /* !SBYTE_H */
