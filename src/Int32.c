/**
 *  @file Int32.c
 */
#include <moreinttypes/types/Int32.h>
#include <string.h>
#include "debug.h"

/**
 *  @private
 *  @{
 */
/** The arithmetic operations supported by an Int32 */
enum Int32Op { ADD, SUB, MUL, DIV };
/** Persistent storage for the return value of ::to_binary_string() */
static char bin_str_buffer[128] = { 0 };
/** Dispatches the arithmetic operation indicated by @param op */
static void perform_int32_op(struct Int32* const restrict self, int32_t i,
                             enum Int32Op op);
/** @} */

/**
 *  @defgroup int_protected "Member" Functions
 *  @ingroup int_class
 *  @remark By "member" function we mean: directly callable via function
 *  pointers belonging to every Int32 `struct`.
 *  @{
 */

/** Called by Int32::add() */
static void add_int32(struct Int32* const restrict self, int32_t i);

/** Called by Int32::sub() */
static void sub_int32(struct Int32* const restrict self, int32_t i);

/** Called by Int32::mul() */
static void mul_int32(struct Int32* const restrict self, int32_t i);

/** Called by Int32::div() */
static void div_int32(struct Int32* const restrict self, int32_t i);

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
                   .add = add_int32,
                   .sub = sub_int32,
                   .mul = mul_int32,
                   .div = div_int32,
                   .parse = from_numeric_string,
                   .n_bang = to_factorial,
                   .to_bin = to_binary_string };
#else /* !c99 initalizers */
    Int32 self = { value,        add_int32,       sub_int32,
                   mul_int32,    div_int32,       from_numeric_string,
                   to_factorial, to_binary_string };
#endif

    return self;
}

static void from_numeric_string(Int32* const restrict self, const char* str,
                                int base)
{
    int32_t* value_accessor = 0;
    int32_t new_value = parse_int(str, base);

    if (parse_succeeded(str, new_value))
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

static void add_int32(struct Int32* const restrict self, int32_t i)
{
    perform_int32_op(self, i, ADD);
}

static void sub_int32(struct Int32* const restrict self, int32_t i)
{
    perform_int32_op(self, i, SUB);
}

static void mul_int32(struct Int32* const restrict self, int32_t i)
{
    perform_int32_op(self, i, MUL);
}

static void div_int32(struct Int32* const restrict self, int32_t i)
{
    perform_int32_op(self, i, DIV);
}

static void perform_int32_op(struct Int32* const restrict self, int32_t b,
                             enum Int32Op op)
{
    int32_t* value_accessor = 0;
    *(const int32_t**)&value_accessor = &(self->value);
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
    if (new_value <= INT32_MAX)
        *value_accessor = (int32_t)new_value;
    else
        write_value_error(INT64_PTR_FMT " is greater than %d", new_value,
                          INT32_MAX);
}
