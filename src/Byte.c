/**
 *  @file Byte.c
 */
#include <moreinttypes/types/Byte.h>
#include <string.h>
#include "debug.h"

/**
 *  @private
 *  @{
 */
/** The arithmetic operations supported by a Byte */
enum ByteOp { ADD, SUB, MUL, DIV };
/** Persistent storage for the return value of ::to_binary_string() */
static char bin_str_buffer[16] = { 0 };
/** Wraps the external parsing function with additional bounds checking */
static uint8_t parse_byte(const char* str, int base);
/** Dispatches the arithmetic operation indicated by @param op */
static void perform_byte_op(struct Byte* const restrict self, uint8_t b,
                            enum ByteOp op);
/** @} */

/**
 *  @defgroup byte_protected "Member" Functions
 *  @ingroup byte_class
 *  @remark By "member" function we mean: directly callable via function
 *  pointers belonging to every Byte `struct`.
 *  @{
 */

/** Called by Byte::add() */
static void add_byte(struct Byte* const restrict self, uint8_t b);

/** Called by Byte::sub() */
static void sub_byte(struct Byte* const restrict self, uint8_t b);

/** Called by Byte::mul() */
static void mul_byte(struct Byte* const restrict self, uint8_t b);

/** Called by Byte::div() */
static void div_byte(struct Byte* const restrict self, uint8_t b);

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
    Byte self = { value,        add_byte,        sub_byte,
                  mul_byte,     div_byte,        from_numeric_string,
                  to_factorial, to_binary_string };
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
        write_argument_error("Expected unsigned value but got '%s'", str);
    }
    else if (result <= UINT8_MAX)
    {
        return (uint8_t)result;
    }
    else
    {
        write_value_error("'%s' is greater than %d", str, UINT8_MAX);
    }

    return 0;
}

static void add_byte(struct Byte* const restrict self, uint8_t b)
{
    perform_byte_op(self, b, ADD);
}

static void sub_byte(struct Byte* const restrict self, uint8_t b)
{
    perform_byte_op(self, b, SUB);
}

static void mul_byte(struct Byte* const restrict self, uint8_t b)
{
    perform_byte_op(self, b, MUL);
}

static void div_byte(struct Byte* const restrict self, uint8_t b)
{
    perform_byte_op(self, b, DIV);
}

static void perform_byte_op(struct Byte* const restrict self, uint8_t b,
                            enum ByteOp op)
{
    uint8_t* value_accessor = 0;
    *(const uint8_t**)&value_accessor = &(self->value);
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
    if (new_value <= UINT8_MAX)
        *value_accessor = (uint8_t)new_value;
    else
        write_value_error(INT64_PTR_FMT " is greater than %u", new_value,
                          UINT8_MAX);
}
