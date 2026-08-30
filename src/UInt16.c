/**
 *  @file UInt16.c
 */
#include <moreinttypes/types/UInt16.h>
#include <string.h>
#include "debug.h"

/**
 *  @private
 *  @{
 */
/** The arithmetic operations supported by a UInt16 */
enum OpUInt16 { ADD, SUB, MUL, DIV };
/** Persistent storage for the return value of ::to_binary_string() */
static char bin_str_buffer[32] = { 0 };
/** Wraps the external parsing function with additional bounds checking */
static uint16_t parse_ushort(const char* str, int base);
static void perform_uint16_op(struct UInt16* const restrict self, uint16_t i,
                              enum OpUInt16 op);
/** @} */

/**
 *  @defgroup uint16_protected "Member" Functions
 *  @ingroup uint16_class
 *  @remark By "member" function we mean: directly callable via function
 *  pointers belonging to every UInt16 `struct`.
 *  @{
 */

/** Called by UInt16::add() */
static void add_uint16(struct UInt16* const restrict self, uint16_t i);

/** Called by UInt16::sub() */
static void sub_uint16(struct UInt16* const restrict self, uint16_t i);

/** Called by UInt16::mul() */
static void mul_uint16(struct UInt16* const restrict self, uint16_t i);

/** Called by UInt16::div() */
static void div_uint16(struct UInt16* const restrict self, uint16_t i);

/** Called by UInt16::parse(), a.k.a #from_string() */
static void from_numeric_string(UInt16* const restrict self, const char* str,
                                int base);

/** Called by UInt16::n_bang(), a.k.a #factorial() */
static long double to_factorial(UInt16* const restrict self);

/** Called by UInt16::to_bin(), a.k.a #as_binary() */
static const char* to_binary_string(UInt16* const restrict self);
/** @} */

UInt16 ConstructUInt16(const uint16_t value)
{
    UInt16 self = { value,        add_uint16,      sub_uint16,
                    mul_uint16,   div_uint16,      from_numeric_string,
                    to_factorial, to_binary_string };
    return self;
}

static void from_numeric_string(UInt16* const restrict self, const char* str,
                                int base)
{
    uint16_t* value_accessor = 0;
    uint16_t new_value = parse_ushort(str, base);

    if (parse_succeeded(str, new_value))
    {
        *(const uint16_t**)&value_accessor = &(self->value);
        *value_accessor = new_value;
    }
}

static long double to_factorial(UInt16* const restrict self)
{
    return factorial_of((uint32_t)self->value);
}

static const char* to_binary_string(UInt16* const restrict self)
{
    memset(bin_str_buffer, 0, sizeof bin_str_buffer);
    return binary_string(bin_str_buffer, self->value);
}

static uint16_t parse_ushort(const char* str, int base)
{
    const int64_t result = parse_int_64(str, base);

    if (result < 0)
    {
        write_argument_error("Expected unsigned value but got '%s'", str);
    }
    else if (result <= UINT16_MAX)
    {
        return (uint16_t)result;
    }
    else
    {
        write_value_error("'%s' is greater than %d", str, UINT16_MAX);
    }

    return 0;
}

static void add_uint16(struct UInt16* const restrict self, uint16_t i)
{
    perform_uint16_op(self, i, ADD);
}

static void sub_uint16(struct UInt16* const restrict self, uint16_t i)
{
    perform_uint16_op(self, i, SUB);
}

static void mul_uint16(struct UInt16* const restrict self, uint16_t i)
{
    perform_uint16_op(self, i, MUL);
}

static void div_uint16(struct UInt16* const restrict self, uint16_t i)
{
    perform_uint16_op(self, i, DIV);
}

static void perform_uint16_op(struct UInt16* const restrict self, uint16_t i,
                              enum OpUInt16 op)
{
    uint16_t* value_accessor = 0;
    *(const uint16_t**)&value_accessor = &(self->value);
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
    if (new_value <= UINT16_MAX)
        *value_accessor = (uint16_t)new_value;
    else
        write_value_error(INT64_PTR_FMT " is greater than %u", new_value,
                          UINT16_MAX);
}
