/**
 *  @file Int16.c
 */
#include <moreinttypes/types/Int16.h>
#include <string.h>
#include "debug.h"

/**
 *  @private
 *  @{
 */
/** Persistent storage for the return value of ::to_binary_string() */
static char bin_str_buffer[32] = { 0 };
/** Wraps the external parsing function with additional bounds checking */
static int16_t parse_short(const char* str, int base);
/** @} */

/**
 *  @defgroup int16_protected "Member" Functions
 *  @ingroup int16_class
 *  @remark By "member" function we mean: directly callable via function
 *  pointers belonging to every Int16 `struct`.
 *  @{
 */

/** Called by Int16::parse(), a.k.a #from_string() */
static void from_numeric_string(Int16* const restrict self, const char* str,
                                int base);

/** Called by Int16::n_bang(), a.k.a #factorial() */
static long double to_factorial(Int16* const restrict self);

/** Called by Int16::to_bin(), a.k.a #as_binary() */
static const char* to_binary_string(Int16* const restrict self);
/** @} */

Int16 ConstructInt16(const int16_t value)
{
    Int16 self = { value, from_numeric_string, to_factorial, to_binary_string };
    return self;
}

static void from_numeric_string(Int16* const restrict self, const char* str,
                                int base)
{
    int16_t* value_accessor = 0;
    int16_t new_value = parse_short(str, base);

    if (parse_succeeded(str, new_value))
    {
        *(const int16_t**)&value_accessor = &(self->value);
        *value_accessor = new_value;
    }
}

static long double to_factorial(Int16* const restrict self)
{
    return factorial_of((uint32_t)self->value);
}

static const char* to_binary_string(Int16* const restrict self)
{
    memset(bin_str_buffer, 0, sizeof bin_str_buffer);
    return binary_string(bin_str_buffer, self->value);
}

static int16_t parse_short(const char* str, int base)
{
    const int64_t result = parse_int_64(str, base);

    if (result <= INT16_MAX)
    {
        return (int16_t)result;
    }
    else
    {
        write_value_error("'%s' is greater than %d", str, INT16_MAX);
    }

    return 0;
}
