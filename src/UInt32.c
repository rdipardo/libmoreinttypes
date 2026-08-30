/**
 *  @file UInt32.c
 */
#include <moreinttypes/types/UInt32.h>
#include <string.h>
#include "debug.h"

/**
 *  @private
 *  @{
 */
/** The arithmetic operations supported by a UInt32 */
enum OpUInt32 { ADD, SUB, MUL, DIV };
/** Persistent storage for the return value of ::to_binary_string() */
static char bin_str_buffer[128] = { 0 };
static void perform_uint32_op(struct UInt32* const restrict self, uint32_t i,
                              enum OpUInt32 op);
/** @} */

/**
 *  @defgroup uint_protected "Member" Functions
 *  @ingroup uint_class
 *  @remark By "member" function we mean: directly callable via function
 *  pointers belonging to every UInt32 `struct`.
 *  @{
 */

/** Called by UInt32::add() */
static void add_uint32(struct UInt32* const restrict self, uint32_t i);

/** Called by UInt32::sub() */
static void sub_uint32(struct UInt32* const restrict self, uint32_t i);

/** Called by UInt32::mul() */
static void mul_uint32(struct UInt32* const restrict self, uint32_t i);

/** Called by UInt32::div() */
static void div_uint32(struct UInt32* const restrict self, uint32_t i);

/** Called by UInt32::parse(), a.k.a #from_string() */
static void from_numeric_string(UInt32* const restrict self, const char* str,
                                int base);

/** Called by UInt32::n_bang(), a.k.a #factorial() */
static long double to_factorial(UInt32* const restrict self);

/** Called by UInt32::to_bin(), a.k.a #as_binary() */
static const char* to_binary_string(UInt32* const restrict self);
/** @} //uint_protected */

UInt32 ConstructUInt(const uint32_t value)
{
    UInt32 self = { value,        add_uint32,      sub_uint32,
                    mul_uint32,   div_uint32,      from_numeric_string,
                    to_factorial, to_binary_string };
    return self;
}

static void from_numeric_string(UInt32* const restrict self, const char* str,
                                int base)
{
    uint32_t* value_accessor = 0;
    uint32_t new_value = parse_uint(str, base);

    if (parse_succeeded(str, new_value))
    {
        *(const uint32_t**)&value_accessor = &(self->value);
        *value_accessor = new_value;
    }
}

static long double to_factorial(UInt32* const restrict self)
{
    return factorial_of((uint32_t)self->value);
}

static const char* to_binary_string(UInt32* const restrict self)
{
    memset(bin_str_buffer, 0, sizeof bin_str_buffer);
    return binary_string(bin_str_buffer, self->value);
}

static void add_uint32(struct UInt32* const restrict self, uint32_t i)
{
    perform_uint32_op(self, i, ADD);
}

static void sub_uint32(struct UInt32* const restrict self, uint32_t i)
{
    perform_uint32_op(self, i, SUB);
}

static void mul_uint32(struct UInt32* const restrict self, uint32_t i)
{
    perform_uint32_op(self, i, MUL);
}

static void div_uint32(struct UInt32* const restrict self, uint32_t i)
{
    perform_uint32_op(self, i, DIV);
}

static void perform_uint32_op(struct UInt32* const restrict self, uint32_t i,
                              enum OpUInt32 op)
{
    uint32_t* value_accessor = 0;
    *(const uint32_t**)&value_accessor = &(self->value);
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
    if (new_value <= UINT32_MAX)
        *value_accessor = (uint32_t)new_value;
    else
        write_value_error(INT64_PTR_FMT " is greater than %u", new_value,
                          UINT32_MAX);
}
