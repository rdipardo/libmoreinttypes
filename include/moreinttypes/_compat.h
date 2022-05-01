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

#define STRICT_ANSI (__STDC_VERSION__ < 199901L)

#if (__cplusplus || STRICT_ANSI) && !defined(_MSC_VER)
#define restrict __restrict__
#define inline __inline
#endif /* (__cplusplus || C89/90) && !MSVC */

#if defined(_MSC_VER)
#define restrict __restrict

#if !defined(__cplusplus)
#define inline __inline
#endif /* MSVC with `/Tc` compiler switch */
#endif /* MSVC */

#if !STRICT_ANSI || _MSC_VER || __MACH__
/* rely on standard type definitions when they're guaranteed to be available */

#define __STDC_LIMIT_MACROS
#include <inttypes.h> /* <stdint.h> */
#include <limits.h>
#include <stdbool.h>
#else
#ifndef __cplusplus
/* polyfill for <stdbool.h> */

typedef unsigned char uint8_t;
typedef uint8_t bool;
/* clang-format off */
#define false ((uint8_t)0)
/* clang-format on */
#define true !false

#if STRICT_ANSI && (__GNUC__ || __MINGW32__)
/* polyfill for <stdint.h>/<inttypes.h> */

typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long int64_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;
#endif /* !<stdint.h> && !long long */
#endif /* !bool */
#endif /* strict C89/90 */

/***********************************************************
*** Match print format specifiers to expected bit-widths ***
***********************************************************/
#if !STRICT_ANSI
#define BIT_PTR_FMT "%hhu"
#else
#define BIT_PTR_FMT "%hu"
#endif

#define SHRT_PTR_FMT "%h"
#define U_SHRT_PTR_FMT "%hu"

#if (_WIN64 || __LP64__ || _LP64) && (__MACH__ || (__MINGW32__ && !STRICT_ANSI))
/* 64-bit macOS X or C99 compiler targeting a 64-bit MinGW-w64 Environment */

#define SIZE_T_FMT "%llu"
#define INT_PTR_FMT "%lld"
#define INT64_PTR_FMT INT_PTR_FMT

#elif __GNUC__ && (__LP64__ || _LP64)
/* 64-bit GNU Environment */

#define SIZE_T_FMT "%lu"
#define INT_PTR_FMT "%ld"
#define INT64_PTR_FMT INT_PTR_FMT

#elif _MSC_VER
/* Visual C++ Environment */

#define SIZE_T_FMT "%Iu"
#define INT_PTR_FMT "%Id"
#define INT64_PTR_FMT "%I64d"

#else
/* Any 32-bit Environment */

#define SIZE_T_FMT "%u"
#define INT_PTR_FMT "%d"
#define INT64_PTR_FMT "%ld"
#endif

#if __MINGW32__ && !(__USE_MINGW_ANSI_STDIO || __USE_MINGW_ANSI_STDIO == 0)
#define __USE_MINGW_ANSI_STDIO 1
#endif /* __MINGW32__ */

#undef STRICT_ANSI
#endif /* !COMPAT_H */
