/**
 *  @file debug.c
 */
#include <stdio.h>
#include <stdarg.h>
#include "debug.h"

typedef enum ErrorType { VALUE = -1, ARGUMENT } Error;

#ifndef _DEBUG
static void write_error(Error nop, ...)
{
    (void)(nop);
}
#else
static void write_error(Error error, const char* msg, va_list vargs)
{
    switch (error)
    {
        case VALUE:
            fprintf(stderr, "\nVALUE ERROR: ");
            break;
        case ARGUMENT:
            fprintf(stderr, "\nARGUMENT ERROR: ");
            break;
        default:
            fprintf(stderr, "\nERROR: ");
            break;
    }
    vfprintf(stderr, msg, vargs);
    fprintf(stderr, ".\n");
}
#endif

void write_argument_error(const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    write_error(ARGUMENT, msg, args);
    va_end(args);
}

void write_value_error(const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    write_error(VALUE, msg, args);
    va_end(args);
}
