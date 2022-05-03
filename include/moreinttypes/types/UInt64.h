/**
 *  @file UInt64.h
 *  @defgroup uint64_class UInt64
 */
#ifndef UINT64_H
#define UINT64_H 1

#include "Integral.h"

#ifdef __cplusplus
extern "C" {
#endif
/** Encapsulates an unsigned 64-bit integer. */
typedef struct UInt64 {
    /** The underlying value of this UInt64 */
    const uint64_t value;
    /** Attempts to set the value of this UInt64 by parsing a numeric string. */
    void (*parse)(struct UInt64* const restrict, const char*, int);
    /** Returns the factorial of this UInt64's value. */
    long double (*n_bang)(struct UInt64* const restrict);
    /** Returns the base-2 representation of this UInt64's value as a string. */
    const char* (*to_bin)(struct UInt64* const restrict);
} UInt64;

MOREINTTYPES_EXPORTS UInt64 ConstructUInt64(const uint64_t value);

#ifdef __cplusplus
}
#endif

/**
 *  @defgroup uint64_ctor Constructor
 *  @ingroup uint64_class
 *  @{
 */
/** Returns an initialized UInt64 `struct`. */
#define uinteger64(x) ConstructUInt64(x)
/** @} */

#endif /* !UINT64_H */
