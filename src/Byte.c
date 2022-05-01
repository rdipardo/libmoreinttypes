/**
 *  @file Byte.c
 */
#include <moreinttypes/types/Byte.h>
#include <stdio.h>
#include <string.h>

/**
 *  @private
 *  @{
 */
/** Persistent storage for the return value of ::to_binary_string() */
static char bin_str_buffer[16] = { 0 };
/** Wraps the external parsing function with additional bounds checking */
static uint8_t parse_byte(const char* str, int base);
/** @} */

/**
 *  @defgroup byte_protected "Member" Functions
 *  @ingroup byte_class
 *  @remark By "member" function we mean: directly callable via function
 *  pointers belonging to every Byte `struct`.
 *  @{
 */

/** Called by Byte::parse(), a.k.a #from_string() */
static void from_numeric_string(Byte* const restrict self, const char* str,
                                int base);

/** Called by Byte::n_bang(), a.k.a #factorial() */
static long double to_factorial(Byte* const restrict self);

/** Called by Byte::to_bin(), a.k.a #as_binary() */
static const char* to_binary_string(Byte* const restrict self);
/** @} //byte_protected */

Byte ConstructByte(const uint8_t value)
{
    Byte self = { value, from_numeric_string, to_factorial, to_binary_string };
    return self;
}

static void from_numeric_string(Byte* const restrict self, const char* str,
                                int base)
{
    uint8_t* value_accessor = 0;
    uint8_t new_value = parse_byte(str, base);

    if (parse_succeeded(str, new_value))
    {
        *(const uint8_t**)&value_accessor = &(self->value);
        *value_accessor = new_value;
    }
}

static long double to_factorial(Byte* const restrict self)
{
    return factorial_of((uint32_t)self->value);
}

static const char* to_binary_string(Byte* const restrict self)
{
    memset(bin_str_buffer, 0, sizeof bin_str_buffer);
    return binary_string(bin_str_buffer, self->value);
}

static uint8_t parse_byte(const char* str, int base)
{
    const int64_t result = parse_int_64(str, base);

    if (result < 0)
    {
        fprintf(stderr,
                "\nVALUE ERROR: needed an unsigned value but got '%s'.\n", str);
    }
    else if (result <= UINT8_MAX)
    {
        return (uint8_t)result;
    }
    else
    {
        fprintf(stderr, "\nVALUE ERROR: '%s' is greater than %d.\n", str,
                UINT8_MAX);
    }

    return 0;
}
