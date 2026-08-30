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
/** The arithmetic operations supported by an Int16 */
enum OpInt16 { ADD, SUB, MUL, DIV };
/** Persistent storage for the return value of ::to_binary_string() */
static char bin_str_buffer[32] = { 0 };
/** Wraps the external parsing function with additional bounds checking */
static int16_t parse_short(const char* str, int base);
/** Dispatches the arithmetic operation indicated by @param op */
static void perform_int16_op(struct Int16* const restrict self, int16_t i,
                             enum OpInt16 op);
/** @} */

/**
 *  @defgroup int16_protected "Member" Functions
 *  @ingroup int16_class
 *  @remark By "member" function we mean: directly callable via function
 *  pointers belonging to every Int16 `struct`.
 *  @{
 */

/** Called by Int16::add() */
static void add_int16(struct Int16* const restrict self, int16_t i);

/** Called by Int16::sub() */
static void sub_int16(struct Int16* const restrict self, int16_t i);

/** Called by Int16::mul() */
static void mul_int16(struct Int16* const restrict self, int16_t i);

/** Called by Int16::div() */
static void div_int16(struct Int16* const restrict self, int16_t i);

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
    Int16 self = { value,        add_int16,       sub_int16,
                   mul_int16,    div_int16,       from_numeric_string,
                   to_factorial, to_binary_string };
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

static void add_int16(struct Int16* const restrict self, int16_t i)
{
    perform_int16_op(self, i, ADD);
}

static void sub_int16(struct Int16* const restrict self, int16_t i)
{
    perform_int16_op(self, i, SUB);
}

static void mul_int16(struct Int16* const restrict self, int16_t i)
{
    perform_int16_op(self, i, MUL);
}

static void div_int16(struct Int16* const restrict self, int16_t i)
{
    perform_int16_op(self, i, DIV);
}

static void perform_int16_op(struct Int16* const restrict self, int16_t i,
                             enum OpInt16 op)
{
    int16_t* value_accessor = 0;
    *(const int16_t**)&value_accessor = &(self->value);
    int64_t new_value = *value_accessor;
    switch (op)
    {
        case ADD:
            new_value += i;
            break;
        case SUB:
            new_value -= i;
            break;
        case MUL:
            new_value *= i;
            break;
        case DIV:
            if (i > 0)
                new_value /= i;
            else
                write_argument_error("Division by 0 attempted");
            break;
        default:
            break;
    }
    if (new_value <= INT16_MAX)
        *value_accessor = (int16_t)new_value;
    else
        write_value_error(INT64_PTR_FMT " is greater than %d", new_value,
                          INT16_MAX);
}
