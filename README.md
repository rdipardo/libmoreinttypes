Description
===========
A minimal library of enhanced integer types for C

Features
--------
- read and write to encapsulated signed/unsigned `const` integers
- parse numeric strings with free functions or by calling through "member" functions
- [polymorphic function macros][]
- use only what you need:

<table border="0">
  <tr>
    <td><code>#include &lt;moreinttypes/core.h&gt;</code></td>
    <td align="right"><em>data types<sup>*</sup>, math and string library</em></td>
  </tr>
  <tr>
    <td><code>#include &lt;moreinttypes/utils.h&gt;</code></td>
    <td align="right"><em>math and string library only</em></td>
  </tr>
  <tr>
    <td colspan="2">
      <small><sup>*</sup> Since version 1.5, the following types are provided:</small>
      <ul style="list-style-type:none">
        <li>Byte</li>
        <li>Int16</li>
        <li>Int32</li>
        <li>Int64</li>
        <li>Sbyte</li>
        <li>UInt16</li>
        <li>UInt32</li>
        <li>UInt64</li>
      </ul>
    </td>
  </tr>
</table>

- compiles on Windows, macOS and Linux
- compatible with code targeting ANSI C ([a GNU compiler][iso-c] supporting `-ansi` is required)

 **Note**
 A compiler supporting the C99 standard is required for building.

- (since version 1.7) compatible with [CPM.cmake]. See [below](#cpm-integration) for a sample configuration.

Examples
--------
**Using function macros (they wrap the "member functions")**
```c
#include <stdio.h>
#include <moreinttypes/core.h> //< Make sure this comes last!

Int32 i = integer(122333333);

// access the underlying value . . .
printf("%d\n", i.value);
// "122333333"

// . . . but no direct assignment allowed!
// i.value = 0;
//
// error: assignment of read-only member ‘value’
//   i.value = 0;
//           ^

// let's set it to the value of a binary string
from_string(i, "10101010", 2);
printf("New value: %d\n", i.value);
// "New value: 170"

// what's that in base-2?
const char* bin_str = as_binary(i);
printf("%s\n", bin_str);
// "1010 1010"

from_string(i, "6", 10);
long double f = factorial(i);
printf("%d! = %.0Lf\n", i.value, f);
// "6! = 720"
```

**Using free functions**
```c
#include <stdio.h>
#include <moreinttypes/utils.h>

int value = parse_int("10101010", 2);
printf("%d\n", value);
// "170"

char buf[16]  = { 0 };
const char* bin_str = binary_string(buf, 170);
printf("%s\n", bin_str);
// "1010 1010"

long double f = factorial_of(6);
printf("6! = %.0Lf\n", f);
// "6! = 720"
```

[CPM][CPM.cmake] integration <a id="cpm-integration" aria-label="CPM Integration"></a>
-----------------
Add the following to your project's `CMakeLists.txt`:

```cmake
cmake_minimum_required (VERSION 3.14)

# Download the 'get_cpm.cmake' module from https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.39.0/get_cpm.cmake
include (get_cpm.cmake)

project (try-libmoreinttypes)

CPMAddPackage ("gh:rdipardo/libmoreinttypes#1.7.0")

add_executable (main "main.c")

add_library (libmoreinttypes INTERFACE IMPORTED)

target_link_libraries (main PUBLIC moreinttypes)

target_include_directories (main
    PUBLIC
    "${libmoreinttypes_SOURCE_DIR}/include"
)

set_target_properties (main moreinttypes
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)
```

Building
--------
- **All environments require [cmake](https://cmake.org)**
- (_optional_) [valgrind], to profile memory usage during unit tests
- (_optional_) [pkg-config](https://packages.debian.org/sid/pkg-config), if available for your system
- (_optional_) [doxygen], if you'd like a local copy of [the documentation][]

**Windows** developers can use the [Visual C++ compiler][], edition 2015 or later.

Compiling with the [MinGW][] toolchain or inside the [MSYS2][] environment will work also.

**Linux** devs can use [gcc][] (version 4.9 and up) or [clang][] (version 3.8 and up).

### Build options
<table border="0">
  <tr>
    <th/>
    <th/>
    <th align="left">Default</th>
  </tr>
  <tr>
    <td><code>-DMOREINTTYPES_BUILD_TESTS=OFF|ON</code></td>
    <td>build and run unit tests</td>
    <td><code>ON</code></td>
  </tr>
  <tr>
    <td><code>-DMOREINTTYPES_BUILD_EXAMPLES=OFF|ON</code></td>
    <td>build sample programs</td>
    <td><code>OFF</code></td>
  </tr>
  <tr>
    <td><code>-DMOREINTTYPES_BUILD_STATIC=OFF|ON</code></td>
    <td>build a static library</td>
    <td><code>OFF</code></td>
  </tr>
  <tr>
    <td><code>-DMOREINTTYPES_ENABLE_UBSAN=OFF|ON</code></td>
    <td>enable the <a href="https://developers.redhat.com/blog/2014/10/16/gcc-undefined-behavior-sanitizer-ubsan" target="_blank">
      Undefined Behavior Sanitizer</a> (GCC,Clang only)</td>
    <td><code>OFF</code></td>
  </tr>
  <tr>
    <td><code>-DMOREINTTYPES_RUN_DEMO</code></td>
    <td>run a sample program immediately after the build (requires <code>MOREINTTYPES_BUILD_EXAMPLES</code>)</td>
    <td><code>OFF</code></td>
  </tr>
  <tr>
    <td><code>-DMOREINTTYPES_CHECK_WITH_VALGRIND=OFF|ON</code></td>
    <td>run a memory leak check with <a href="https://valgrind.org" target="_blank">
      valgrind</a>, if installed </td>
    <td><code>OFF</code></td>
  </tr>
</table>

### Deprecated options (since [1.7.0])
<table border="0">
  <tr>
    <th/>
    <th align="left">Replaced by...</th>
  </tr>
  <tr>
    <td><code>-DBUILD_STATIC=OFF|ON</code></td>
    <td><code>-DMOREINTTYPES_BUILD_STATIC</code></td>
  </tr>
  <tr>
    <td><code>-DENABLE_UBSAN=OFF|ON</code></td>
    <td><code>-DMOREINTTYPES_ENABLE_UBSAN</code></td>
  </tr>
  <tr>
    <td><code>-DRUN_DEMO=OFF|ON</code></td>
    <td><code>-DMOREINTTYPES_RUN_DEMO</code></td>
  </tr>
  <tr>
    <td><code>-DWITH_VALGRIND=OFF|ON</code></td>
    <td><code>-DMOREINTTYPES_CHECK_WITH_VALGRIND</code></td>
  </tr>
</table>

The build steps are the same for all environments, with one exception:

- if you're using the **Visual C++ compiler**, start the [Developer Command Prompt][]; all other users can simply log in to their usual shell
- clone the main branch and enter the root directory at the command line: `cd libmoreinttypes`
- make and enter the build directory: `mkdir cmake-build && cd cmake-build`
- run: `cmake .. `, or (to use a certain [makefile generator][]) `cmake .. -G"<name_of_generator>"`

**Note**
It's better to run `cmake .. -G"NMake Makefiles"` when using the Visual C++ compiler.
This will prevent `cmake` from choosing a [Visual Studio Generator][] by default.

- run:
<div></div>


    make

or, if using [MinGW][]:

    mingw32-make

or, if using [nmake][]:

    nmake


Installing
----------
As the admin user, run:

    make install

or

    mingw32-make install

or

    nmake install


API Documentation
-----------------
To build the [the documentation] and serve it at `localhost:8000`, enter the `doxygen` directory and run:

    ./gendocs

or, on Windows,

    .\gendocs

**Note**
Make sure [doxygen] and [python] are installed and visible to your system's `PATH`.

---
**This project took inspiration from the following sources:**
- the [C Object System](https://github.com/CObjectSystem/COS). Like this library, it strives to be compatible with ANSI/C89 while taking advantage of C99 features at compile time
- Schreiner, A.-T. (1993). [Object-oriented programming
  with ANSI-C](https://www.cs.rit.edu/~ats/books/ooc.pdf). You can read the full text of this obscure classic for free online

License
-------
Copyright (c) 2020 Robert Di Pardo and Contributors. All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


[CPM.cmake]: https://github.com/cpm-cmake/CPM.cmake/#readme
[Visual C++ compiler]: https://docs.microsoft.com/en-us/cpp/build/vscpp-step-0-installation
[Developer Command Prompt]: https://docs.microsoft.com/en-us/dotnet/framework/tools/developer-command-prompt-for-vs
[MSYS2]: https://cmake.org/cmake/help/latest/generator/MSYS%20Makefiles.html#generator:MSYS%20Makefiles
[MinGW]: https://cmake.org/cmake/help/latest/generator/MinGW%20Makefiles.html
[nmake]: https://docs.microsoft.com/en-us/cpp/build/reference/running-nmake?view=msvc-160
[gcc]: https://gcc.gnu.org
[clang]: https://clang.llvm.org
[valgrind]: https://valgrind.org/downloads
[python]: https://www.python.org/downloads
[doxygen]: https://www.doxygen.nl/index.html
[makefile generator]: https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#makefile-generators
[Visual Studio Generator]: https://cmake.org/cmake/help/latest/generator/Visual%20Studio%2014%202015.html
[the documentation]: https://rdipardo.github.io/libmoreinttypes
[polymorphic function macros]: https://rdipardo.github.io/libmoreinttypes/d2/d46/group__int__fn__wrappers.html
[1.7.0]: https://github.com/rdipardo/libmoreinttypes/commit/74e48d0
[iso-c]: https://github.com/rdipardo/libmoreinttypes/blob/5355b132ebaeb939843587191859e10d26cd1080/include/moreinttypes/_compat.h