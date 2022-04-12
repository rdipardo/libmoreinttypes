/**
 *  @file Int64.h
 *  @defgroup int64_class Int64
 */
#ifndef INT64_H
#define INT64_H 1

#include "Integral.h"

#ifdef __cplusplus
extern "C" {
#endif
/** Encapsulates a 64-bit integer. */
typedef struct Int64 {
    /** The underlying value of this Int64 */
    const int64_t value;
    /** Attempts to set the value of this Int64 by parsing a numeric string. */
    void (*parse)(struct Int64* const restrict, const char*, int);
    /** Returns the factorial of this Int64's value. */
    long double (*n_bang)(struct Int64* const restrict);
    /** Returns the base-2 representation of this Int64's value as a string. */
    const char* (*to_bin)(struct Int64* const restrict);
} Int64;

MOREINTTYPES_EXPORTS Int64 ConstructInt64(const int64_t value);

#ifdef __cplusplus
}
#endif

/**
 *  @defgroup int64_ctor Constructor
 *  @ingroup int64_class
 *  @{
 */
/** Returns an initialized Int64 `struct`. */
#define integer64(x) ConstructInt64(x)
/** @} //int64_ctor */

#endif /* !INT64_H */
