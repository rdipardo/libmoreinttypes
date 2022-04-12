/**
 *  @file Int32.c
 */
#include <moreinttypes/types/Int32.h>
#include <string.h>

/**
 *  @private
 *  @{
 */
/** Persistent storage for the return value of ::to_binary_string() */
static char bin_str_buffer[128] = { 0 };
/** @} */

/**
 *  @defgroup int_protected "Member" Functions
 *  @ingroup int_class
 *  @remark By "member" function we mean: directly callable via function
 *  pointers belonging to every Int32 `struct`.
 *  @{
 */

/** Called by Int32::parse(), a.k.a #from_string() */
static void from_numeric_string(Int32* const restrict self, const char* str,
                                int base);

/** Called by Int32::n_bang(), a.k.a #factorial() */
static long double to_factorial(Int32* const restrict self);

/** Called by Int32::to_bin(), a.k.a #as_binary() */
static const char* to_binary_string(Int32* const restrict self);
/** @} //int_protected */

Int32 ConstructInteger(const int32_t value)
{
#if __STDC_VERSION__ >= 199901L
    Int32 self = { .value = value,
                   .parse = from_numeric_string,
                   .n_bang = to_factorial,
                   .to_bin = to_binary_string };
#else /* !c99 initalizers */
    Int32 self = { value, from_numeric_string, to_factorial, to_binary_string };
#endif

    return self;
}

static void from_numeric_string(Int32* const restrict self, const char* str,
                                int base)
{
    int32_t* value_accessor = 0;
    int32_t new_value = parse_int(str, base);

    if (new_value > 0 || (new_value < 0 && str[0] == '-') ||
        (new_value == 0 && str[0] == '0'))
    {
        *(const int32_t**)&value_accessor = &(self->value);
        *value_accessor = new_value;
    }
}

static long double to_factorial(Int32* const restrict self)
{
    return factorial_of((uint32_t)self->value);
}

static const char* to_binary_string(Int32* const restrict self)
{
    memset(bin_str_buffer, 0, sizeof bin_str_buffer);
    return binary_string(bin_str_buffer, self->value);
}
