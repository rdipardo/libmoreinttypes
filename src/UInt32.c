/**
 *  @file UInt32.c
 */
#include <moreinttypes/types/UInt32.h>
#include <stdio.h>
#include <string.h>

/**
 *  @private
 *  @{
 */
/** Persistent storage for the return value of ::to_binary_string() */
static char bin_str_buffer[128] = { 0 };
/** @} */

/**
 *  @defgroup uint_protected "Member" Functions
 *  @ingroup uint_class
 *  @remark By "member" function we mean: directly callable via function
 *  pointers belonging to every UInt32 `struct`.
 *  @{
 */

/** Called by UInt32::parse(), a.k.a #from_string() */
static void from_numeric_string(UInt32* const restrict self, const char* str,
                                int base);

/** Called by UInt32::n_bang(), a.k.a #factorial() */
static long double to_factorial(UInt32* const restrict self);

/** Called by UInt32::to_bin(), a.k.a #as_binary() */
static const char* to_binary_string(UInt32* const restrict self);
/** @} //uint_protected */

UInt32 ConstructUInt(const uint32_t value)
{
    UInt32 self = { value, from_numeric_string, to_factorial,
                    to_binary_string };
    return self;
}

static void from_numeric_string(UInt32* const restrict self, const char* str,
                                int base)
{
    uint32_t* value_accessor = 0;
    uint32_t new_value = parse_uint(str, base);

    if (parse_succeeded(str, new_value))
    {
        *(const uint32_t**)&value_accessor = &(self->value);
        *value_accessor = new_value;
    }
}

static long double to_factorial(UInt32* const restrict self)
{
    return factorial_of((uint32_t)self->value);
}

static const char* to_binary_string(UInt32* const restrict self)
{
    memset(bin_str_buffer, 0, sizeof bin_str_buffer);
    return binary_string(bin_str_buffer, self->value);
}
