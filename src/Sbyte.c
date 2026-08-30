/**
 *  @file Sbyte.c
 */
#include <moreinttypes/types/Sbyte.h>
#include <string.h>
#include "debug.h"

/**
 *  @private
 *  @{
 */
/** The arithmetic operations supported by an Sbyte */
enum SbyteOp { ADD, SUB, MUL, DIV };
/** Persistent storage for the return value of ::to_binary_string() */
static char bin_str_buffer[16] = { 0 };
/** Wraps the external parsing function with additional bounds checking */
static int8_t parse_sbyte(const char* str, int base);
/** Dispatches the arithmetic operation indicated by @param op */
static void perform_sbyte_op(struct Sbyte* const restrict self, int8_t b,
                             enum SbyteOp op);
/** @} */

/**
 *  @defgroup sbyte_protected "Member" Functions
 *  @ingroup sbyte_class
 *  @remark By "member" function we mean: directly callable via function
 *  pointers belonging to every Sbyte `struct`.
 *  @{
 */

/** Called by Sbyte::add() */
static void add_sbyte(struct Sbyte* const restrict self, int8_t b);

/** Called by Sbyte::sub() */
static void sub_sbyte(struct Sbyte* const restrict self, int8_t b);

/** Called by Sbyte::mul() */
static void mul_sbyte(struct Sbyte* const restrict self, int8_t b);

/** Called by Sbyte::div() */
static void div_sbyte(struct Sbyte* const restrict self, int8_t b);

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
    Sbyte self = { value,        add_sbyte,       sub_sbyte,
                   mul_sbyte,    div_sbyte,       from_numeric_string,
                   to_factorial, to_binary_string };
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
        write_value_error("'%s' is greater than %d", str, INT8_MAX);
    }

    return 0;
}

static void add_sbyte(struct Sbyte* const restrict self, int8_t b)
{
    perform_sbyte_op(self, b, ADD);
}

static void sub_sbyte(struct Sbyte* const restrict self, int8_t b)
{
    perform_sbyte_op(self, b, SUB);
}

static void mul_sbyte(struct Sbyte* const restrict self, int8_t b)
{
    perform_sbyte_op(self, b, MUL);
}

static void div_sbyte(struct Sbyte* const restrict self, int8_t b)
{
    perform_sbyte_op(self, b, DIV);
}

static void perform_sbyte_op(struct Sbyte* const restrict self, int8_t b,
                             enum SbyteOp op)
{
    int8_t* value_accessor = 0;
    *(const int8_t**)&value_accessor = &(self->value);
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
    if (new_value <= INT8_MAX)
        *value_accessor = (int8_t)new_value;
    else
        write_value_error(INT64_PTR_FMT " is greater than %d", new_value,
                          INT8_MAX);
}
