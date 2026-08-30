/**
 *  @file Int64.c
 */
#include <moreinttypes/types/Int64.h>
#include <string.h>
#include "debug.h"

/**
 *  @private
 *  @{
 */
/** The arithmetic operations supported by an Int64 */
enum OpInt64 { ADD, SUB, MUL, DIV };
/** Persistent storage for the return value of ::to_binary_string() */
static char bin_str_buffer[128] = { 0 };
/** Dispatches the arithmetic operation indicated by @param op */
static void perform_int64_op(struct Int64* const restrict self, int64_t i,
                             enum OpInt64 op);
/** @} */

/**
 *  @defgroup int64_protected "Member" Functions
 *  @ingroup int64_class
 *  @remark By "member" function we mean: directly callable via function
 *  pointers belonging to every Int64 `struct`.
 *  @{
 */

/** Called by Int64::add() */
static void add_int64(struct Int64* const restrict self, int64_t i);

/** Called by Int64::sub() */
static void sub_int64(struct Int64* const restrict self, int64_t i);

/** Called by Int64::mul() */
static void mul_int64(struct Int64* const restrict self, int64_t i);

/** Called by Int64::div() */
static void div_int64(struct Int64* const restrict self, int64_t i);

/** Called by Int64::parse(), a.k.a #from_string() */
static void from_numeric_string(Int64* const restrict self, const char* str,
                                int base);

/** Called by Int64::n_bang(), a.k.a #factorial() */
static long double to_factorial(Int64* const restrict self);

/** Called by Int64::to_bin(), a.k.a #as_binary() */
static const char* to_binary_string(Int64* const restrict self);
/** @} //int64_protected */

Int64 ConstructInt64(const int64_t value)
{
#if __STDC_VERSION__ >= 199901L
    Int64 self = { .value = value,
                   .add = add_int64,
                   .sub = sub_int64,
                   .mul = mul_int64,
                   .div = div_int64,
                   .parse = from_numeric_string,
                   .n_bang = to_factorial,
                   .to_bin = to_binary_string };
#else /* !c99 initalizers */
    Int64 self = { value,        add_int64,       sub_int64,
                   mul_int64,    div_int64,       from_numeric_string,
                   to_factorial, to_binary_string };
#endif

    return self;
}

static void from_numeric_string(Int64* const restrict self, const char* str,
                                int base)
{
    int64_t* value_accessor = 0;
    int64_t new_value = parse_int_64(str, base);

    if (parse_succeeded(str, new_value))
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

static void add_int64(struct Int64* const restrict self, int64_t i)
{
    perform_int64_op(self, i, ADD);
}

static void sub_int64(struct Int64* const restrict self, int64_t i)
{
    perform_int64_op(self, i, SUB);
}

static void mul_int64(struct Int64* const restrict self, int64_t i)
{
    perform_int64_op(self, i, MUL);
}

static void div_int64(struct Int64* const restrict self, int64_t i)
{
    perform_int64_op(self, i, DIV);
}

static void perform_int64_op(struct Int64* const restrict self, int64_t b,
                             enum OpInt64 op)
{
    int64_t* value_accessor = 0;
    *(const int64_t**)&value_accessor = &(self->value);
    int64_t new_value = *value_accessor;
    switch (op)
    {
        case ADD:
            new_value += b;
            break;
        case SUB:
            new_value -= b;
            break;
        case MUL:
            new_value *= b;
            break;
        case DIV:
            if (b > 0)
                new_value /= b;
            else
                write_argument_error("Division by 0 attempted");
            break;
        default:
            break;
    }
    if (new_value <= INT64_MAX)
        *value_accessor = new_value;
    else
        write_value_error(INT64_PTR_FMT " is greater than " INT64_PTR_FMT,
                          new_value, INT64_MAX);
}
