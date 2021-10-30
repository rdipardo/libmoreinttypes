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
 *  Appends a binary digit to the given buffer.
 *  @remarks Called internally by ::write_bits
 *  @param dest A string to append to.
 *  @param buffer Scratch memory to which the bit will be written.
 *  @param bit A `0` or a `1`.
 */
static void add_bit(char* dest, char* buffer, uint8_t bit);

/**
 *  Writes an array of binary digits to the given buffer.
 *  @remarks Called internally by ::binary_string and ::binary_string_64
 *  @param bin_str The target buffer (and first argument of ::add_bit)
 *  @param bit_buf The second argument of ::add_bit
 *  @param bits Array of binary digits.
 *  @param bit_width The length of the `bits` array.
 */
static void write_bits(char* bin_str, char* bit_buf, uint8_t* bits,
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
            fprintf(stderr,
                    "\nVALUE ERROR: %" PRIu64 "! is greater than %.2Le.\n", n,
                    LDBL_MAX);
            break;
        }

        ++counter;
    }

    return product;
}

int32_t parse_int(const char* str, unsigned base)
{
    const int64_t result = parse_int_64(str, base);

    if (result <= INT32_MAX)
    {
        return (int32_t)result;
    }
    else
    {
        fprintf(stderr, "\nVALUE ERROR: '%s' is greater than %d.\n", str,
                INT32_MAX);
    }

    return 0;
}

int64_t parse_int_64(const char* str, unsigned base)
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
            fprintf(stderr,
                    "\nVALUE ERROR: '%s' is greater than " INT64_PTR_FMT ".\n",
                    str, INT64_MAX);
        }
        else if (temp > 0 || (temp < 0 && str[0] == '-') /* negative number */
                 || (temp == 0 && str[0] == '0'))        /* number was '0' */
        {
            result = temp;
        }
        else
        {
            fprintf(stderr, "\nARGUMENT ERROR: Can't parse value of '%s'.\n",
                    str);
        }
    }
    else
    {
        fprintf(stderr, "\nARGUMENT ERROR: Invalid string.\n");
    }

    return result;
}

const char* binary_string(char* bin_str, int32_t n)
{
    if ((int64_t)n <= INT32_MAX)
    {
        return binary_string_64(bin_str, (int64_t)n);
    }
    else
    {
        fprintf(stderr,
                "\nVALUE ERROR: " INT64_PTR_FMT " is greater than %d.\n",
                (int64_t)n, INT32_MAX);
    }

    return bin_str;
}

const char* binary_string_64(char* bin_str, int64_t n)
{
    if (n <= INT64_MAX)
    {
        char bit_buf[BIT_BUFFER_SIZE] = { 0 };
        uint8_t bits[64] = { 0 };
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
        fprintf(stderr,
                "\n VALUE ERROR: " INT64_PTR_FMT
                " is greater than " INT64_PTR_FMT ".\n",
                n, INT64_MAX);
    }

    return bin_str;
}

static inline void write_bits(char* bin_str, char* bit_buf, uint8_t* bits,
                              uint8_t bit_width)
{
    uint8_t z = 0;

    switch (bit_width)
    {
        case 64:
        case 63:
        case 62:
        case 61:
            for (z = 64 - bit_width; z > 0; z--)
            {
                add_bit(bin_str, bit_buf, ASCII_ZERO);
            }

            while (bit_width > 60)
            {
                add_bit(bin_str, bit_buf, bits[bit_width]);
                bit_width--;
            }

            add_bit(bin_str, bit_buf, ASCII_GAP);
        case 60:
        case 59:
        case 58:
        case 57:
            for (z = 60 - bit_width; z > 0; z--)
            {
                add_bit(bin_str, bit_buf, ASCII_ZERO);
            }

            while (bit_width > 56)
            {
                add_bit(bin_str, bit_buf, bits[bit_width]);
                bit_width--;
            }

            add_bit(bin_str, bit_buf, ASCII_GAP);
        case 56:
        case 55:
        case 54:
        case 53:
            for (z = 56 - bit_width; z > 0; z--)
            {
                add_bit(bin_str, bit_buf, ASCII_ZERO);
            }

            while (bit_width > 52)
            {
                add_bit(bin_str, bit_buf, bits[bit_width]);
                bit_width--;
            }

            add_bit(bin_str, bit_buf, ASCII_GAP);
        case 52:
        case 51:
        case 50:
        case 49:
            for (z = 52 - bit_width; z > 0; z--)
            {
                add_bit(bin_str, bit_buf, ASCII_ZERO);
            }

            while (bit_width > 48)
            {
                add_bit(bin_str, bit_buf, bits[bit_width]);
                bit_width--;
            }

            add_bit(bin_str, bit_buf, ASCII_GAP);
        case 48:
        case 47:
        case 46:
        case 45:
            for (z = 48 - bit_width; z > 0; z--)
            {
                add_bit(bin_str, bit_buf, ASCII_ZERO);
            }

            while (bit_width > 44)
            {
                add_bit(bin_str, bit_buf, bits[bit_width]);
                bit_width--;
            }

            add_bit(bin_str, bit_buf, ASCII_GAP);
        case 44:
        case 43:
        case 42:
        case 41:
            for (z = 44 - bit_width; z > 0; z--)
            {
                add_bit(bin_str, bit_buf, ASCII_ZERO);
            }

            while (bit_width > 40)
            {
                add_bit(bin_str, bit_buf, bits[bit_width]);
                bit_width--;
            }

            add_bit(bin_str, bit_buf, ASCII_GAP);
        case 40:
        case 39:
        case 38:
        case 37:
            for (z = 40 - bit_width; z > 0; z--)
            {
                add_bit(bin_str, bit_buf, ASCII_ZERO);
            }

            while (bit_width > 36)
            {
                add_bit(bin_str, bit_buf, bits[bit_width]);
                bit_width--;
            }

            add_bit(bin_str, bit_buf, ASCII_GAP);
        case 36:
        case 35:
        case 34:
        case 33:
            for (z = 36 - bit_width; z > 0; z--)
            {
                add_bit(bin_str, bit_buf, ASCII_ZERO);
            }

            while (bit_width > 32)
            {
                add_bit(bin_str, bit_buf, bits[bit_width]);
                bit_width--;
            }

            add_bit(bin_str, bit_buf, ASCII_GAP);
        case 32:
        case 31:
        case 30:
        case 29:
            for (z = 32 - bit_width; z > 0; z--)
            {
                add_bit(bin_str, bit_buf, ASCII_ZERO);
            }

            while (bit_width > 28)
            {
                add_bit(bin_str, bit_buf, bits[bit_width]);
                bit_width--;
            }

            add_bit(bin_str, bit_buf, ASCII_GAP);
        case 28:
        case 27:
        case 26:
        case 25:
            for (z = 28 - bit_width; z > 0; z--)
            {
                add_bit(bin_str, bit_buf, ASCII_ZERO);
            }

            while (bit_width > 24)
            {
                add_bit(bin_str, bit_buf, bits[bit_width]);
                bit_width--;
            }

            add_bit(bin_str, bit_buf, ASCII_GAP);
        case 24:
        case 23:
        case 22:
        case 21:
            for (z = 24 - bit_width; z > 0; z--)
            {
                add_bit(bin_str, bit_buf, ASCII_ZERO);
            }

            while (bit_width > 20)
            {
                add_bit(bin_str, bit_buf, bits[bit_width]);
                bit_width--;
            }

            add_bit(bin_str, bit_buf, ASCII_GAP);
        case 20:
        case 19:
        case 18:
        case 17:
            for (z = 20 - bit_width; z > 0; z--)
            {
                add_bit(bin_str, bit_buf, ASCII_ZERO);
            }

            while (bit_width > 16)
            {
                add_bit(bin_str, bit_buf, bits[bit_width]);
                bit_width--;
            }

            add_bit(bin_str, bit_buf, ASCII_GAP);
        case 16:
        case 15:
        case 14:
        case 13:
            for (z = 16 - bit_width; z > 0; z--)
            {
                add_bit(bin_str, bit_buf, ASCII_ZERO);
            }

            while (bit_width > 12)
            {
                add_bit(bin_str, bit_buf, bits[bit_width]);
                bit_width--;
            }

            add_bit(bin_str, bit_buf, ASCII_GAP);
        case 12:
        case 11:
        case 10:
        case 9:
            for (z = 12 - bit_width; z > 0; z--)
            {
                add_bit(bin_str, bit_buf, ASCII_ZERO);
            }

            while (bit_width > 8)
            {
                add_bit(bin_str, bit_buf, bits[bit_width]);
                bit_width--;
            }

            add_bit(bin_str, bit_buf, ASCII_GAP);
        case 8:
        case 7:
        case 6:
        case 5:
            for (z = 8 - bit_width; z > 0; z--)
            {
                add_bit(bin_str, bit_buf, ASCII_ZERO);
            }

            while (bit_width > 4)
            {
                add_bit(bin_str, bit_buf, bits[bit_width]);
                bit_width--;
            }

            add_bit(bin_str, bit_buf, ASCII_GAP);
        case 4:
        case 3:
        case 2:
        case 1:
            for (z = 4 - bit_width; z > 0; z--)
            {
                add_bit(bin_str, bit_buf, ASCII_ZERO);
            }

            while (bit_width > 0)
            {
                add_bit(bin_str, bit_buf, bits[bit_width]);
                bit_width--;
            }
            break;
        case 0:
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
