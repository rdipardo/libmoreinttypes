/**
 *  @file UInt16.h
 *  @defgroup uint16_class UInt16
 */
#ifndef UINT16_H
#define UINT16_H 1

#include "Integral.h"

#ifdef __cplusplus
extern "C" {
#endif
/** Encapsulates an unsigned 16-bit integer. */
typedef struct UInt16 {
    /** The underlying value of this UInt16 */
    const uint16_t value;
    /** Attempts to set the value of this UInt16 by parsing a numeric string. */
    void (*parse)(struct UInt16* const restrict, const char*, int);
    /** Returns the factorial of this UInt16's value. */
    long double (*n_bang)(struct UInt16* const restrict);
    /** Returns the base-2 representation of this UInt16's value as a string. */
    const char* (*to_bin)(struct UInt16* const restrict);
} UInt16;

MOREINTTYPES_EXPORTS UInt16 ConstructUInt16(const uint16_t value);

#ifdef __cplusplus
}
#endif

/**
 *  @defgroup uint16_ctor Constructor
 *  @ingroup uint16_class
 *  @{
 */
/** Returns an initialized UInt16 `struct`. */
#define uinteger16(x) ConstructUInt16(x)
/** @} */

#endif /* !UINT16_H */
