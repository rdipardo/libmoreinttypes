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

void append_string(char* dest, const char* src, size_t lim)
{
    char* buf = NULL;
    int succ = 0;
    size_t growth = strlen(src) + 1;
    size_t end, offset = strlen(dest) + 1;
    size_t new_length = offset + growth;

    if (new_length < MAX_LEN && new_length < lim)
    {
        buf = (char*)alloca(new_length);
        memset(buf, 0, new_length);
        snprintf(buf, offset, "%s", dest);

        offset -= 1;
        end = offset;
        succ = snprintf(buf + offset, growth, "%s", src);

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
    size_t i, len = strlen(pstr) + 1;

    if (pstr)
    {
        for (i = 0; i < len; i++)
        {
            if (i >= 0 && i < len - 1 &&
                (*(pstr + i) == '\r' || *(pstr + i) == '\n'))
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
        /** @todo Finish implementing ::ltrim_s */
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
        /** @todo Finish implementing ::rtrim_s */
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
        /** @todo Finish implementing ::trim_s */
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
    /** @todo Implement ::trim_rw */
}
