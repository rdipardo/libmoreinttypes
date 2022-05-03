/**
 *  @file UInt32.h
 *  @defgroup uint_class UInt32
 */
#ifndef UINT32_H
#define UINT32_H 1

#include "Integral.h"

#ifdef __cplusplus
extern "C" {
#endif
/** Encapsulates an unsigned 32-bit integer. */
typedef struct UInt32 {
    /** The underlying value of this UInt32 */
    const uint32_t value;
    /** Attempts to set the value of this UInt32 by parsing a numeric string. */
    void (*parse)(struct UInt32* const restrict, const char*, int);
    /** Returns the factorial of this UInt32's value. */
    long double (*n_bang)(struct UInt32* const restrict);
    /** Returns the base-2 representation of this UInt32's value as a string. */
    const char* (*to_bin)(struct UInt32* const restrict);
} UInt32;

MOREINTTYPES_EXPORTS UInt32 ConstructUInt(const uint32_t value);

#ifdef __cplusplus
}
#endif

/**
 *  @defgroup uint_ctor Constructor
 *  @ingroup uint_class
 *  @{
 */
/** Returns an initialized UInt32 `struct`. */
#define uinteger(x) ConstructUInt(x)
/** @} */

#endif /* !UINT32_H */
