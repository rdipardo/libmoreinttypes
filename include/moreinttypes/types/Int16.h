/**
 *  @file Int16.h
 *  @defgroup int16_class Int16
 */
#ifndef INT16_H
#define INT16_H 1

#include "Integral.h"

#ifdef __cplusplus
extern "C" {
#endif
/** Encapsulates a signed 16-bit integer. */
typedef struct Int16 {
    /** The underlying value of this Int16 */
    const int16_t value;
    /** Attempts to set the value of this Int16 by parsing a numeric string. */
    void (*parse)(struct Int16* const restrict, const char*, int);
    /** Returns the factorial of this Int16's value. */
    long double (*n_bang)(struct Int16* const restrict);
    /** Returns the base-2 representation of this Int16's value as a string. */
    const char* (*to_bin)(struct Int16* const restrict);
} Int16;

MOREINTTYPES_EXPORTS Int16 ConstructInt16(const int16_t value);

#ifdef __cplusplus
}
#endif

/**
 *  @defgroup int16_ctor Constructor
 *  @ingroup int16_class
 *  @{
 */
/** Returns an initialized Int16 `struct`. */
#define integer16(x) ConstructInt16(x)
/** @} */

#endif /* !INT16_H */
