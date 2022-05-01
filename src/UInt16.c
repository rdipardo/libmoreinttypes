/**
 *  @file UInt16.c
 */
#include <moreinttypes/types/UInt16.h>
#include <stdio.h>
#include <string.h>

/**
 *  @private
 *  @{
 */
/** Persistent storage for the return value of ::to_binary_string() */
static char bin_str_buffer[32] = { 0 };
/** Wraps the external parsing function with additional bounds checking */
static uint16_t parse_ushort(const char* str, int base);
/** @} */

/**
 *  @defgroup uint16_protected "Member" Functions
 *  @ingroup uint16_class
 *  @remark By "member" function we mean: directly callable via function
 *  pointers belonging to every UInt16 `struct`.
 *  @{
 */

/** Called by UInt16::parse(), a.k.a #from_string() */
static void from_numeric_string(UInt16* const restrict self, const char* str,
                                int base);

/** Called by UInt16::n_bang(), a.k.a #factorial() */
static long double to_factorial(UInt16* const restrict self);

/** Called by UInt16::to_bin(), a.k.a #as_binary() */
static const char* to_binary_string(UInt16* const restrict self);
/** @} */

UInt16 ConstructUInt16(const uint16_t value)
{
    UInt16 self = { value, from_numeric_string, to_factorial,
                    to_binary_string };
    return self;
}

static void from_numeric_string(UInt16* const restrict self, const char* str,
                                int base)
{
    uint16_t* value_accessor = 0;
    uint16_t new_value = parse_ushort(str, base);

    if (parse_succeeded(str, new_value))
    {
        *(const uint16_t**)&value_accessor = &(self->value);
        *value_accessor = new_value;
    }
}

static long double to_factorial(UInt16* const restrict self)
{
    return factorial_of((uint32_t)self->value);
}

static const char* to_binary_string(UInt16* const restrict self)
{
    memset(bin_str_buffer, 0, sizeof bin_str_buffer);
    return binary_string(bin_str_buffer, self->value);
}

static uint16_t parse_ushort(const char* str, int base)
{
    const int64_t result = parse_int_64(str, base);

    if (result < 0)
    {
        fprintf(stderr,
                "\nVALUE ERROR: needed an unsigned value but got '%s'.\n", str);
    }
    else if (result <= UINT16_MAX)
    {
        return (uint16_t)result;
    }
    else
    {
        fprintf(stderr, "\nVALUE ERROR: '%s' is greater than %d.\n", str,
                UINT16_MAX);
    }

    return 0;
}
