/**
 *  @file _compat.h
 *  Feature tests for standards conformance and (some) cross-platform
 *  compatibility.
 *
 *  @warning Client code should `#include` this before any standard libraries,
 *  with the single exception of `malloc.h` (applies to MSVC only).
 */
#ifndef COMPAT_H
#define COMPAT_H 1

#if (__cplusplus || __STDC_VERSION__ < 199901L) && !defined(_MSC_VER)
#    define restrict __restrict__
#    define inline __inline
#endif /* (__cplusplus || C89/90) && !MSVC */

#if defined(_MSC_VER)
#    define restrict __restrict

#    if !defined(__cplusplus)
#        define inline __inline
#    endif /* MSVC with `/Tc` compiler switch */
#endif     /* MSVC */

#define __STDC_LIMIT_MACROS
#include <inttypes.h> /* <stdint.h> */
#include <limits.h>

#if __STDC_VERSION__ >= 199901L
#    include <stdbool.h>
#else
typedef unsigned char uint8_t;
#    ifndef __cplusplus
typedef uint8_t bool;
#        define false ((uint8_t)0)
#        define true !false
#    endif /* !bool */
#endif     /* C89/90 */

/***********************************************************
*** Match print format specifiers to expected bit-widths ***
***********************************************************/
#if __STDC_VERSION__ >= 199901L
#    define BIT_PTR_FMT "%hhu"
#else
#    define BIT_PTR_FMT "%hu"
#endif

#define SHRT_PTR_FMT "%h"
#define U_SHRT_PTR_FMT "%hu"

#if (_WIN64 || __LP64__ || _LP64) && __MINGW32__
/* 64-bit MinGW-w64 Environment */

#    define SIZE_T_FMT "%llu"
#    define INT_PTR_FMT "%lld"
#    define INT64_PTR_FMT INT_PTR_FMT

#elif __GNUC__ && (__LP64__ || _LP64)
/* 64-bit GNU Environment */

#    define SIZE_T_FMT "%lu"
#    define INT_PTR_FMT "%ld"
#    define INT64_PTR_FMT INT_PTR_FMT

#elif _MSC_VER
/* Visual C++ Environment */

#    define SIZE_T_FMT "%Iu"
#    define INT_PTR_FMT "%Id"
#    define INT64_PTR_FMT "%I64d"

#else
/* Any 32-bit Environment */

#    define SIZE_T_FMT "%u"
#    define INT_PTR_FMT "%d"
#    define INT64_PTR_FMT "%lld"
#endif

#if __MINGW32__ && !__USE_MINGW_ANSI_STDIO
#    define __USE_MINGW_ANSI_STDIO 1
#endif /* __MINGW32__ */

#endif /* !COMPAT_H */
