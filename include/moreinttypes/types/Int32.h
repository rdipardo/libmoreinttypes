/**
 *  @file Int32.h
 *  @defgroup int_class Int32
 */
#ifndef INT32_H
#define INT32_H 1

#include "Integral.h"

#ifdef __cplusplus
extern "C" {
#endif
/** Encapsulates a 32-bit integer. */
typedef struct Int32 {
    /** The underlying value of this Int32 */
    const int32_t value;
    /** Attempts to set the value of this Int32 by parsing a numeric string. */
    void (*parse)(struct Int32* const restrict, const char*, unsigned);
    /** Returns the factorial of this Int32's value. */
    long double (*n_bang)(struct Int32* const restrict);
    /** Returns the base-2 representation of this Int32's value as a string. */
    const char* (*to_bin)(struct Int32* const restrict);
} Int32;

MOREINTTYPES_EXPORTS Int32 ConstructInteger(const int32_t value);

#ifdef __cplusplus
}
#endif

/**
 *  @defgroup int_ctor Constructor
 *  @ingroup int_class
 *  @{
 */
/** Returns an initialized Int32 `struct`. */
#define integer(x) ConstructInteger(x)
/** @} //int_ctor */

#endif /* !INT32_H */
