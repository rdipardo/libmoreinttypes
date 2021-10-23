/**
 *  @file Int64.c
 */
#include <moreinttypes/types/Int64.h>
#include <string.h>

/**
 *  @private
 *  @{
 */
/** Persistent storage for the return value of ::to_binary_string() */
static char bin_str_buffer[128] = { 0 };
/** @} */

/**
 *  @defgroup int64_protected "Member" Functions
 *  @ingroup int64_class
 *  @remark By "member" function we mean: directly callable via function
 *  pointers belonging to every Int64 `struct`.
 *  @{
 */

/** Called by Int64::parse(), a.k.a #from_string() */
static void from_numeric_string(Int64* const restrict self, const char* str,
                                unsigned base);

/** Called by Int64::n_bang(), a.k.a #factorial() */
static long double to_factorial(Int64* const restrict self);

/** Called by Int64::to_bin(), a.k.a #as_binary() */
static const char* to_binary_string(Int64* const restrict self);
/** @} //int64_protected */

Int64 ConstructInt64(const int64_t value)
{
#if __STDC_VERSION__ >= 199901L
    Int64 self = { .value = value,
                   .parse = from_numeric_string,
                   .n_bang = to_factorial,
                   .to_bin = to_binary_string };
#else /* !c99 initalizers */
    Int64 self = { value, from_numeric_string, to_factorial, to_binary_string };
#endif

    return self;
}

static void from_numeric_string(Int64* const restrict self, const char* str,
                                unsigned base)
{
    int64_t* value_accessor = 0;
    int64_t new_value = parse_int_64(str, base);

    if (new_value > 0 || (new_value < 0 && str[0] == '-') ||
        (new_value == 0 && str[0] == '0'))
    {
        *(const int64_t**)&value_accessor = &(self->value);
        *value_accessor = new_value;
    }
}

static long double to_factorial(Int64* const restrict self)
{
    return factorial_of_64((uint64_t)self->value);
}

static const char* to_binary_string(Int64* const restrict self)
{
    memset(bin_str_buffer, 0, sizeof bin_str_buffer);
    return binary_string_64(bin_str_buffer, self->value);
}
