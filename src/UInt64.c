/**
 *  @file UInt64.c
 */
#include <moreinttypes/types/UInt64.h>
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
 *  @defgroup uint64_protected "Member" Functions
 *  @ingroup uint64_class
 *  @remark By "member" function we mean: directly callable via function
 *  pointers belonging to every UInt64 `struct`.
 *  @{
 */

/** Called by UInt64::parse(), a.k.a #from_string() */
static void from_numeric_string(UInt64* const restrict self, const char* str,
                                int base);

/** Called by UInt64::n_bang(), a.k.a #factorial() */
static long double to_factorial(UInt64* const restrict self);

/** Called by UInt64::to_bin(), a.k.a #as_binary() */
static const char* to_binary_string(UInt64* const restrict self);
/** @} //uint64_protected */

UInt64 ConstructUInt64(const uint64_t value)
{
    UInt64 self = { value, from_numeric_string, to_factorial,
                    to_binary_string };
    return self;
}

static void from_numeric_string(UInt64* const restrict self, const char* str,
                                int base)
{
    uint64_t* value_accessor = 0;
    uint64_t new_value = parse_uint_64(str, base);

    if (new_value != 0 || str[0] == '0')
    {
        *(const uint64_t**)&value_accessor = &(self->value);
        *value_accessor = new_value;
    }
}

static long double to_factorial(UInt64* const restrict self)
{
    return factorial_of_64(self->value);
}

static const char* to_binary_string(UInt64* const restrict self)
{
    memset(bin_str_buffer, 0, sizeof bin_str_buffer);
    return binary_string_64(bin_str_buffer, self->value);
}
