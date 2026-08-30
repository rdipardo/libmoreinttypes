/**
 *  @file UInt64.c
 */
#include <moreinttypes/types/UInt64.h>
#include <string.h>
#include "debug.h"

/**
 *  @private
 *  @{
 */
/** The arithmetic operations supported by a UInt64 */
enum OpUInt64 { ADD, SUB, MUL, DIV };
/** Persistent storage for the return value of ::to_binary_string() */
static char bin_str_buffer[128] = { 0 };
/** Dispatches the arithmetic operation indicated by @param op */
static void perform_uint64_op(struct UInt64* const restrict self, uint64_t i,
                              enum OpUInt64 op);
/** @} */

/**
 *  @defgroup uint64_protected "Member" Functions
 *  @ingroup uint64_class
 *  @remark By "member" function we mean: directly callable via function
 *  pointers belonging to every UInt64 `struct`.
 *  @{
 */

/** Called by UInt64::add() */
static void add_uint64(struct UInt64* const restrict self, uint64_t i);

/** Called by UInt64::sub() */
static void sub_uint64(struct UInt64* const restrict self, uint64_t i);

/** Called by UInt64::mul() */
static void mul_uint64(struct UInt64* const restrict self, uint64_t i);

/** Called by UInt64::div() */
static void div_uint64(struct UInt64* const restrict self, uint64_t i);

/** Called by UInt64::parse(), a.k.a #from_string() */
static void from_numeric_string(UInt64* const restrict self, const char* str,
                                int base);

/** Called by UInt64::n_bang(), a.k.a #factorial() */
static long double to_factorial(UInt64* const restrict self);

/** Called by UInt64::to_bin(), a.k.a #as_binary() */
static const char* to_binary_string(UInt64* const restrict self);
/** @} //uint64_protected */

UInt64 ConstructUInt64(const uint64_t value)
{
    UInt64 self = { value,        add_uint64,      sub_uint64,
                    mul_uint64,   div_uint64,      from_numeric_string,
                    to_factorial, to_binary_string };
    return self;
}

static void from_numeric_string(UInt64* const restrict self, const char* str,
                                int base)
{
    uint64_t* value_accessor = 0;
    uint64_t new_value = parse_uint_64(str, base);

    if (new_value != 0 || str[0] == '0')
    {
        *(const uint64_t**)&value_accessor = &(self->value);
        *value_accessor = new_value;
    }
}

static long double to_factorial(UInt64* const restrict self)
{
    return factorial_of_64(self->value);
}

static const char* to_binary_string(UInt64* const restrict self)
{
    memset(bin_str_buffer, 0, sizeof bin_str_buffer);
    return binary_string_64(bin_str_buffer, self->value);
}

static void add_uint64(struct UInt64* const restrict self, uint64_t i)
{
    perform_uint64_op(self, i, ADD);
}

static void sub_uint64(struct UInt64* const restrict self, uint64_t i)
{
    perform_uint64_op(self, i, SUB);
}

static void mul_uint64(struct UInt64* const restrict self, uint64_t i)
{
    perform_uint64_op(self, i, MUL);
}

static void div_uint64(struct UInt64* const restrict self, uint64_t i)
{
    perform_uint64_op(self, i, DIV);
}

static void perform_uint64_op(struct UInt64* const restrict self, uint64_t b,
                              enum OpUInt64 op)
{
    uint64_t* value_accessor = 0;
    *(const uint64_t**)&value_accessor = &(self->value);
    uint64_t new_value = *value_accessor;
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
    if (new_value <= UINT64_MAX)
        *value_accessor = new_value;
    else
        write_value_error(SIZE_T_FMT " is greater than " SIZE_T_FMT, new_value,
                          UINT64_MAX);
}
