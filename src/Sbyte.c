/**
 *  @file Sbyte.c
 */
#include <moreinttypes/types/Sbyte.h>
#include <stdio.h>
#include <string.h>

/**
 *  @private
 *  @{
 */
/** Persistent storage for the return value of ::to_binary_string() */
static char bin_str_buffer[16] = { 0 };
/** Wraps the external parsing function with additional bounds checking */
static int8_t parse_sbyte(const char* str, int base);
/** @} */

/**
 *  @defgroup sbyte_protected "Member" Functions
 *  @ingroup sbyte_class
 *  @remark By "member" function we mean: directly callable via function
 *  pointers belonging to every Sbyte `struct`.
 *  @{
 */

/** Called by Sbyte::parse(), a.k.a #from_string() */
static void from_numeric_string(Sbyte* const restrict self, const char* str,
                                int base);

/** Called by Sbyte::n_bang(), a.k.a #factorial() */
static long double to_factorial(Sbyte* const restrict self);

/** Called by Sbyte::to_bin(), a.k.a #as_binary() */
static const char* to_binary_string(Sbyte* const restrict self);
/** @} //sbyte_protected */

Sbyte ConstructSbyte(const int8_t value)
{
    Sbyte self = { value, from_numeric_string, to_factorial, to_binary_string };
    return self;
}

static void from_numeric_string(Sbyte* const restrict self, const char* str,
                                int base)
{
    int8_t* value_accessor = 0;
    int8_t new_value = parse_sbyte(str, base);

    if (parse_succeeded(str, new_value))
    {
        *(const int8_t**)&value_accessor = &(self->value);
        *value_accessor = new_value;
    }
}

static long double to_factorial(Sbyte* const restrict self)
{
    return factorial_of((uint32_t)self->value);
}

static const char* to_binary_string(Sbyte* const restrict self)
{
    memset(bin_str_buffer, 0, sizeof bin_str_buffer);
    return binary_string(bin_str_buffer, self->value);
}

static int8_t parse_sbyte(const char* str, int base)
{
    const int64_t result = parse_int_64(str, base);

    if (result <= INT8_MAX)
    {
        return (int8_t)result;
    }
    else
    {
        fprintf(stderr, "\nVALUE ERROR: '%s' is greater than %d.\n", str,
                INT8_MAX);
    }

    return 0;
}
