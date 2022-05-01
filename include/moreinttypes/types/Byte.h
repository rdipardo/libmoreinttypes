/**
 *  @file Byte.h
 *  @defgroup byte_class Byte
 */
#ifndef BYTE_H
#define BYTE_H 1

#include "Integral.h"

#ifdef __cplusplus
extern "C" {
#endif
/** Encapsulates an unsigned 8-bit integer. */
typedef struct Byte {
    /** The underlying value of this Byte */
    const uint8_t value;
    /** Attempts to set the value of this Byte by parsing a numeric string. */
    void (*parse)(struct Byte* const restrict, const char*, int);
    /** Returns the factorial of this Byte's value. */
    long double (*n_bang)(struct Byte* const restrict);
    /** Returns the base-2 representation of this Byte's value as a string. */
    const char* (*to_bin)(struct Byte* const restrict);
} Byte;

MOREINTTYPES_EXPORTS Byte ConstructByte(const uint8_t value);

#ifdef __cplusplus
}
#endif

/**
 *  @defgroup byte_ctor Constructor
 *  @ingroup byte_class
 *  @{
 */
/** Returns an initialized Byte `struct`. */
#define byte(x) ConstructByte(x)
/** @} */

#endif /* !BYTE_H */
