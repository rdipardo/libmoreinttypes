/**
 *  @file text.c
 */
#if defined(__GNUC__) && !defined(__MINGW32__)
#include <moreinttypes/utils.h>
/* use POSIX implementation of `alloca.h` when available */
#include <alloca.h>
#else
#include <malloc.h>
#include <moreinttypes/utils.h>
#endif

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/** Called internally by ::ltrim_s() when the second argument is `NULL`
 *  @param pstr Pointer to a writable `char` array.
 */
static void ltrim_rw(char(*pstr));

/** Called internally by ::rtrim_s() when the second argument is `NULL`
 *  @param pstr Pointer to a writable `char` array.
 */
static void rtrim_rw(char(*pstr));

/** Called internally by ::trim_s() when the second argument is `NULL`
 *  @param pstr Pointer to a writable `char` array.
 */
static void trim_rw(char(*pstr));

/** Called internally by ::ltrim_s() when the second argument is not `NULL`,
 *  but a read-only string
 *  @param dest Pointer to a writable `char` array.
 *  @param src Pointer to a read-only `char` array
 */
static void ltrim_ro(char(*dest), const char(*src));

/** Called internally by ::rtrim_s() when the second argument is not `NULL`,
 *  but a read-only string
 *  @param dest Pointer to a writable `char` array.
 *  @param src Pointer to a read-only `char` array
 */
static void rtrim_ro(char(*dest), const char(*src));

/** Called internally by ::trim_s() when the second argument is not `NULL`,
 *  but a read-only string
 *  @param dest Pointer to a writable `char` array.
 *  @param src Pointer to a read-only `char` array
 */
static void trim_ro(char(*dest), const char(*src));

void append_string(char* dest, const char* src, size_t lim)
{
    char* buf = NULL;
    size_t growth = strlen(src) + 1;
    size_t offset = strlen(dest) + 1;
    size_t new_length = offset + growth;

    if (new_length < MAX_LEN && new_length < lim)
    {
        size_t end;
        buf = (char*)alloca(new_length);
        memset(buf, 0, new_length);
        snprintf(buf, offset, "%s", dest);

        offset -= 1;
        end = offset;
        int succ = snprintf(buf + offset, growth, "%s", src);

        if (succ > 0 && (size_t)succ < MAX_LEN)
        {
            snprintf(dest + offset, growth, "%s", src);

            if (!*(dest + end))
            {
                *(dest + end) = '\0';
            }
        }
    }
}

void chomp(char(*pstr))
{
    if (pstr)
    {
        size_t i = 0, len = strlen(pstr) + 1;

        /* skip ahead to string content, if any */
        while (isspace(*(pstr + i))) i++;

        if (i >= len - 1)
        {
            /* string was empty except for whitespace */
            *(pstr) = '\0';
        }

        for (; i < len; i++)
        {
            if (i < len - 1 && (*(pstr + i) == '\r' || *(pstr + i) == '\n'))
            {
                *(pstr + i) = '\0';
                break;
            }
        }
    }
}

void ltrim_s(char(*dest), const char(*src))
{
    if (src)
    {
        ltrim_ro(dest, src);
    }
    else
    {
        ltrim_rw(dest);
    }
}

void rtrim_s(char(*dest), const char(*src))
{
    if (src)
    {
        rtrim_ro(dest, src);
    }
    else
    {
        rtrim_rw(dest);
    }
}

void trim_s(char(*dest), const char(*src))
{
    if (src)
    {
        trim_ro(dest, src);
    }
    else
    {
        trim_rw(dest);
    }
}

static void ltrim_rw(char(*pstr))
{
    int i = 0, j = 0;

    while (isspace(pstr[i]))
    {
        ++i;
    }

    while (pstr[i])
    {
        pstr[j++] = pstr[i++];
    }

    pstr[j] = '\0';
}

static void rtrim_rw(char(*pstr))
{
    char* end = pstr + strlen(pstr) - 1;
    while (end >= pstr && isspace(*end)) --end;
    *(end + 1) = '\0';
}

static void trim_rw(char(*pstr))
{
    rtrim_rw(pstr);
    ltrim_rw(pstr);
}

static void ltrim_ro(char(*dest), const char(*src))
{
    /* copy a segment of `src` into `dest` */
    size_t i = 0;
    while (isspace(src[i])) ++i;

    size_t j = 0;
    while (src[i]) dest[j++] = src[i++];

    dest[j] = '\0';
}

static void rtrim_ro(char(*dest), const char(*src))
{
    long long i = (long long)strlen(src) - 1;
    while (i >= 0 && isspace(src[i])) --i;
    if (i >= 0)
    {
        /* We use memmove instead of `memcpy`,
         because `dest` and `src` might overlap */
        size_t n = (size_t)i + 1;
        memmove(dest, src, n);
    }

    dest[i + 1] = '\0';
}

static void trim_ro(char(*dest), const char(*src))
{
    rtrim_ro(dest, src);
    ltrim_ro(dest, dest);
}
