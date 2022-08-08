/**
 *  @file numeric.c
 */
#include <moreinttypes/utils.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include "debug.h"

#define ASCII_GAP 32
#define ASCII_ZERO 48
#define BIT_BUFFER_SIZE 512U

#ifndef INT32_MAX
#define INT32_MAX 0x7FFFFFFF
#endif /* !INT32_MAX */

#ifndef INT64_MAX
#define INT64_MAX 0x7FFFFFFFFFFFFFFF
#endif /* !INT64_MAX */

/**
 *  Writes a zero-padded span of bits into the destination buffer.
 *  @remarks Called internally by ::write_bits
 *  @param dest A string to append to.
 *  @param buffer Scratch memory to which the bit will be written.
 *  @param[in, out] bit_width Pointer to the array length of @p bits; it will be
 *      reduced by the number of bits written.
 *  @param bits Array of binary digits.
 *  @param max A multiple of 4 that is >= the value of @p bit_width.
 */
static void fill_bits(char* dest, char* buffer, uint8_t* bit_width,
                      const uint8_t* bits, const uint8_t max);

/**
 *  Writes an array of binary digits to the given buffer.
 *  @remarks Called internally by ::binary_string and ::binary_string_64
 *  @param bin_str The target buffer (and first argument of ::fill_bits)
 *  @param bit_buf The second argument of ::fill_bits
 *  @param bits Array of binary digits.
 *  @param bit_width The length of the `bits` array.
 */
static void write_bits(char* bin_str, char* bit_buf, const uint8_t* bits,
                       uint8_t bit_width);

long double factorial_of(uint32_t n)
{
    return factorial_of_64((uint64_t)n);
}

long double factorial_of_64(uint64_t n)
{
    uint64_t counter = 1;
    long double product = 1.0L;

    while (counter <= n)
    {
        product *= counter;

        if (isinf(product))
        {
            product = 0.0L;
            write_value_error("%" PRIu64 "! is greater than %.2Le", n,
                              LDBL_MAX);
            break;
        }

        ++counter;
    }

    return product;
}

int32_t parse_int(const char* str, int base)
{
    const int64_t result = parse_int_64(str, base);

    if (result <= INT32_MAX)
    {
        return (int32_t)result;
    }
    else
    {
        write_value_error("'%s' is greater than %d", str, INT32_MAX);
    }

    return 0;
}

uint32_t parse_uint(const char* str, int base)
{
    const int64_t result = parse_int_64(str, base);

    if (result < 0)
    {
        write_argument_error("Expected unsigned value but got '%s'", str);
    }
    else if (result <= UINT32_MAX)
    {
        return (uint32_t)result;
    }
    else
    {
        write_value_error("'%s' is greater than %u", str, UINT32_MAX);
    }

    return 0;
}

int64_t parse_int_64(const char* str, int base)
{
    int64_t result = 0;

    char buffer[128] = { 0 };
    char temp_buffer[2] = { 0 };
    char* end = { 0 };
    int (*parse_func)(int);

    memset(buffer, '*', (sizeof buffer));
    buffer[sizeof buffer - 1] = '\0';
    parse_func = (base == 16) ? isxdigit : isdigit;
    errno = 0;

    if (str && strlen(str) > 0 && strlen(str) <= sizeof buffer)
    {
        int64_t temp = 0;
        size_t i = 0, j = 0;

        for (i = 0; i < strlen(str); i++)
        {
            if (parse_func(str[i]))
            {
                temp_buffer[0] = str[i];
                temp_buffer[1] = '\0';
                temp = (int64_t)strtol(temp_buffer, &end, base);
                end = "";

                if (errno == 0)
                {
                    if (temp != 0 || temp_buffer[0] == '0')
                    {
                        for (j = 0; j < strlen(buffer); j++)
                        {
                            if (buffer[j] == '*')
                            {
                                buffer[j] = temp_buffer[0];
                                break;
                            }
                        }
                    }
                    else
                        buffer[i] = '*';
                }
                else
                    errno = 0;
            }
            else if (i == 0 && (str[0] == '-' || str[0] == '+'))
            {
                buffer[i] = str[i];
            }
            else if (i > 0 && str[i] == '.')
            {
                buffer[i - 1] = '*';
                break;
            }
        }

        buffer[i] = '\0';

        for (i = 0; i < strlen(buffer); i++)
        {
            if (buffer[i] == '*')
                buffer[i] = '\0';
        }

        temp = (int64_t)strtoll(buffer, &end, base);

        if (errno == ERANGE || (temp < 0 && str[0] != '-')) /* overflow */
        {
            errno = 0;
            write_value_error("'%s' is greater than " INT64_PTR_FMT, str,
                              INT64_MAX);
        }
        else if (parse_succeeded(str, temp))
        {
            result = temp;
        }
        else
        {
            write_argument_error("Can't parse value of '%s'", str);
        }
    }
    else
    {
        write_argument_error("Invalid string '%s'", str);
    }

    return result;
}

uint64_t parse_uint_64(const char* str, int base)
{
    uint64_t result = 0;
    char buffer[128] = { 0 };
    char temp_buffer[2] = { 0 };
    char* end = { 0 };
    int (*parse_func)(int);

    memset(buffer, '*', (sizeof buffer));
    buffer[sizeof buffer - 1] = '\0';
    parse_func = (base == 16) ? isxdigit : isdigit;
    errno = 0;

    if (strlen(str) >= 2 && str[0] == '-' && parse_func(str[1]))
    {
        write_argument_error("Expected unsigned value but got '%s'", str);
    }
    else if (str && strlen(str) > 0 && strlen(str) <= sizeof buffer)
    {
        uint64_t temp = 0;
        size_t i = 0, j = 0;

        for (i = 0; i < strlen(str); i++)
        {
            if (parse_func(str[i]))
            {
                temp_buffer[0] = str[i];
                temp_buffer[1] = '\0';
                temp = (int64_t)strtol(temp_buffer, &end, base);
                end = "";

                if (errno == 0)
                {
                    if (temp != 0 || temp_buffer[0] == '0')
                    {
                        for (j = 0; j < strlen(buffer); j++)
                        {
                            if (buffer[j] == '*')
                            {
                                buffer[j] = temp_buffer[0];
                                break;
                            }
                        }
                    }
                    else
                        buffer[i] = '*';
                }
                else
                    errno = 0;
            }
            else if (i == 0 && (str[0] == '-' || str[0] == '+'))
            {
                buffer[i] = str[i];
            }
            else if (i > 0 && str[i] == '.')
            {
                buffer[i - 1] = '*';
                break;
            }
        }

        buffer[i] = '\0';

        for (i = 0; i < strlen(buffer); i++)
        {
            if (buffer[i] == '*')
                buffer[i] = '\0';
        }

        temp = (uint64_t)strtoull(buffer, &end, base);

        if (errno == ERANGE) /* overflow */
        {
            errno = 0;
            write_value_error("'%s' is greater than " SIZE_T_FMT, str,
                              UINT64_MAX);
        }
        else if (temp < INT64_MAX && ((int64_t)temp) < 0)
        {
            write_argument_error("Expected unsigned value but got '%s'", str);
        }
        else if (temp != 0 || str[0] == '0')
        {
            result = temp;
        }
        else
        {
            write_argument_error("Can't parse value of '%s'", str);
        }
    }
    else
    {
        write_argument_error("Invalid string '%s'", str);
    }

    return result;
}

const char* binary_string(char* bin_str, uint32_t n)
{
    if (n <= UINT32_MAX)
    {
        return binary_string_64(bin_str, (int64_t)n);
    }
    else
    {
        write_value_error("%u is greater than %u", n, UINT32_MAX);
    }

    return bin_str;
}

const char* binary_string_64(char* bin_str, uint64_t n)
{
    if (n <= UINT64_MAX)
    {
        char bit_buf[BIT_BUFFER_SIZE] = { 0 };
        uint8_t bits[65] = { 0 };
        uint8_t bit_width = 0;

        while (n > 0)
        {
            bit_width++;
            bits[bit_width] = n % 2;
            n >>= 1;
        }
        write_bits(bin_str, bit_buf, bits, bit_width);
    }
    else
    {
        write_value_error(INT64_PTR_FMT " is greater than " SIZE_T_FMT, n,
                          UINT64_MAX);
    }

    return bin_str;
}

bool parse_succeeded(const char* str, const int64_t val)
{
    return (val > 0 || (val < 0 && str[0] == '-') /* negative number */
            || (val == 0 && str[0] == '0'));      /* number was '0' */
}

static inline void write_bits(char* bin_str, char* bit_buf, const uint8_t* bits,
                              uint8_t bit_width)
{
    switch (bit_width)
    {
        case 64:
        case 63:
        case 62:
        case 61:
            fill_bits(bin_str, bit_buf, &bit_width, bits, 64);
        case 60:
        case 59:
        case 58:
        case 57:
            fill_bits(bin_str, bit_buf, &bit_width, bits, 60);
        case 56:
        case 55:
        case 54:
        case 53:
            fill_bits(bin_str, bit_buf, &bit_width, bits, 56);
        case 52:
        case 51:
        case 50:
        case 49:
            fill_bits(bin_str, bit_buf, &bit_width, bits, 52);
        case 48:
        case 47:
        case 46:
        case 45:
            fill_bits(bin_str, bit_buf, &bit_width, bits, 48);
        case 44:
        case 43:
        case 42:
        case 41:
            fill_bits(bin_str, bit_buf, &bit_width, bits, 44);
        case 40:
        case 39:
        case 38:
        case 37:
            fill_bits(bin_str, bit_buf, &bit_width, bits, 40);
        case 36:
        case 35:
        case 34:
        case 33:
            fill_bits(bin_str, bit_buf, &bit_width, bits, 36);
        case 32:
        case 31:
        case 30:
        case 29:
            fill_bits(bin_str, bit_buf, &bit_width, bits, 32);
        case 28:
        case 27:
        case 26:
        case 25:
            fill_bits(bin_str, bit_buf, &bit_width, bits, 28);
        case 24:
        case 23:
        case 22:
        case 21:
            fill_bits(bin_str, bit_buf, &bit_width, bits, 24);
        case 20:
        case 19:
        case 18:
        case 17:
            fill_bits(bin_str, bit_buf, &bit_width, bits, 20);
        case 16:
        case 15:
        case 14:
        case 13:
            fill_bits(bin_str, bit_buf, &bit_width, bits, 16);
        case 12:
        case 11:
        case 10:
        case 9:
            fill_bits(bin_str, bit_buf, &bit_width, bits, 12);
        case 8:
        case 7:
        case 6:
        case 5:
            fill_bits(bin_str, bit_buf, &bit_width, bits, 8);
        case 4:
        case 3:
        case 2:
        case 1:
            fill_bits(bin_str, bit_buf, &bit_width, bits, 4);
            break;
        default:
            memcpy((void*)bin_str, "0000", 5);
            break;
    }
}

static inline void add_bit(char* dest, char* buffer, uint8_t bit)
{
    int succ = 0;

    if (bit == ASCII_ZERO)
    {
        (sprintf(buffer, "%c", ASCII_ZERO));
    }
    else if (bit == ASCII_GAP)
    {
        (sprintf(buffer, "%c", ASCII_GAP));
    }
    else
    {
        (sprintf(buffer, BIT_PTR_FMT, bit));
    }

    succ = snprintf(NULL, 0, "%s", buffer);

    if (succ > 0)
    {
        append_string(dest, buffer, BIT_BUFFER_SIZE);
    }
}

static inline void fill_bits(char* dest, char* buffer, uint8_t* bit_width,
                             const uint8_t* bits, const uint8_t max)
{
    for (uint8_t i = max - *bit_width; i > 0; i--)
        add_bit(dest, buffer, ASCII_ZERO);

    while (*bit_width > (max - 4)) add_bit(dest, buffer, bits[(*bit_width)--]);

    if (max > 4)
        add_bit(dest, buffer, ASCII_GAP);
}
