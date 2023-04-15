cmake_minimum_required(VERSION 3.13) # https://github.com/libcheck/check/issues/325
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR};${CMAKE_MODULE_PATH}")
include(ProjectVersion)

project_version (PROJECT_VERSION "pkgconfig/moreinttypes.pc")
project (moreinttypes VERSION ${PROJECT_VERSION})

file(GLOB LIB_SRC "${PROJECT_SOURCE_DIR}/src/*.c*")
file(GLOB PUBLIC_HEADERS "${PROJECT_SOURCE_DIR}/include/moreinttypes/*.h")
file(GLOB TYPES_API "${PROJECT_SOURCE_DIR}/include/moreinttypes/types/*.h")
file(GLOB UTILS_API "${PROJECT_SOURCE_DIR}/include/moreinttypes/utils/*.h")

add_library(moreinttypes SHARED ${LIB_SRC})
include_directories("${PROJECT_SOURCE_DIR}/include")

if(CMAKE_HOST_WIN32)
  add_subdirectory("${PROJECT_SOURCE_DIR}/src/win32")
endif()

set_target_properties (moreinttypes PROPERTIES
    VERSION ${PROJECT_VERSION}
    COMPILE_DEFINITIONS BUILDING_MOREINTTYPES=1
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
    # define these for .dll targets
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

# ==================================================
# Build options
# ==================================================
option(BUILD_STATIC
  "Build ${CMAKE_PROJECT_NAME} as a static library" OFF)

option(ENABLE_UBSAN
  "GCC,Clang: Enable the Undefined Behavior Sanitizer (ubsan)" ON)

if (BUILD_STATIC)
  add_library(moreinttypes-static STATIC ${LIB_SRC})

  set_target_properties (moreinttypes-static PROPERTIES
      VERSION ${PROJECT_VERSION}
      COMPILE_DEFINITIONS MOREINTTYPES_EXPORTS_BUILT_AS_STATIC=1
      OUTPUT_NAME moreinttypes
      ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/static")

  install (TARGETS moreinttypes-static
           ARCHIVE DESTINATION lib)
endif()

if(CMAKE_BUILD_TYPE MATCHES "Debug")
  add_compile_definitions(_DEBUG)
  set_target_properties(moreinttypes PROPERTIES DEBUG_POSTFIX "d")
  if (BUILD_STATIC)
    set_target_properties(moreinttypes-static PROPERTIES DEBUG_POSTFIX "d")
  endif()
endif()

# ==================================================
# Toolchains
# ==================================================
if (MSVC)
  # https://stackoverflow.com/a/24767451
  set(CMAKE_C_FLAGS "")
  set(CMAKE_CXX_FLAGS "")
  set(CMAKE_C_FLAGS_DEBUG "")
  set(CMAKE_CXX_FLAGS_DEBUG "")
  set(CMAKE_C_FLAGS_RELEASE "")
  set(CMAKE_CXX_FLAGS_RELEASE "")
  set(CMAKE_C_FLAGS_MINSIZEREL "")
  set(CMAKE_CXX_FLAGS_MINSIZEREL "")
  set(CMAKE_C_FLAGS_RELWITHDEBINFO "")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "")

  add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
  target_compile_options(moreinttypes PRIVATE /nologo /Zi /W4 /WX /wd4190)
  if (BUILD_STATIC)
    target_compile_options(moreinttypes-static PRIVATE /nologo /Zi /W4 /WX)
  endif()

  if(CMAKE_BUILD_TYPE MATCHES "Debug")
    target_compile_options(moreinttypes PRIVATE /Od /LDd /DDEBUG)
    target_link_libraries(moreinttypes PRIVATE -OPT:REF -INCREMENTAL:NO -DEBUG)
    if (BUILD_STATIC)
      target_compile_options(moreinttypes-static PRIVATE /Od /MTd /DDEBUG)
    endif()
  else()
    target_compile_options(moreinttypes PUBLIC /Ob1 /Ot /LD /DNDEBUG)
    if (BUILD_STATIC)
      target_compile_options(moreinttypes-static PUBLIC /Ob1 /Ot /MT /DNDEBUG)
    endif()
  endif()
endif()
# will test TRUE for MinGW -- see next comment
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_C_COMPILER_ID MATCHES "Clang")
  list(APPEND POSIX_C_FLAGS
        -Wall
        -Wextra
        -Werror
        -pedantic
        -Werror=incompatible-pointer-types
        -Werror=init-self
        -Werror=uninitialized
        -Wno-format
        -Wno-implicit-fallthrough)

if(NOT CMAKE_C_COMPILER_ID MATCHES "Clang")
  list(APPEND POSIX_C_FLAGS
        -Warray-bounds=2
        -Werror=discarded-array-qualifiers
        -Werror=discarded-qualifiers)
endif()

  # don't pass -lubsan to the linker when building with MinGW
  if(ENABLE_UBSAN AND ((CMAKE_COMPILER_IS_GNUCC
        AND CMAKE_C_COMPILER_VERSION GREATER 4.8)
      OR (CMAKE_C_COMPILER_ID MATCHES "Clang"
        AND CMAKE_C_COMPILER_VERSION GREATER 3.7)
      AND NOT WIN32))
    list(APPEND POSIX_C_FLAGS
        -fsanitize=null,signed-integer-overflow,bounds,undefined)
    target_link_libraries(moreinttypes PUBLIC -fsanitize=undefined)
  endif()
  # enable the %Lf format specifier in MinGW builds
  if(WIN32)
    add_compile_definitions(__USE_MINGW_ANSI_STDIO)
  endif()

  if(CMAKE_BUILD_TYPE MATCHES "Debug")
    list(APPEND POSIX_C_FLAGS -Og)
  endif()

  list (JOIN POSIX_C_FLAGS " " POSIX_C_FLAGS_STRING)
  set (CMAKE_C_FLAGS "${POSIX_C_FLAGS_STRING} ${CMAKE_C_FLAGS}")
endif()

install (TARGETS moreinttypes
         ARCHIVE DESTINATION lib
         LIBRARY DESTINATION lib
         RUNTIME DESTINATION bin)

install(FILES ${PUBLIC_HEADERS} DESTINATION include/moreinttypes)
install(FILES ${TYPES_API} DESTINATION include/moreinttypes/types)
install(FILES ${UTILS_API} DESTINATION include/moreinttypes/utils)
install(FILES "${PROJECT_SOURCE_DIR}/pkgconfig/moreinttypes.pc"
        DESTINATION lib/pkgconfig)

add_subdirectory("${PROJECT_SOURCE_DIR}/test")
add_subdirectory("${PROJECT_SOURCE_DIR}/examples/demo++")
add_subdirectory("${PROJECT_SOURCE_DIR}/examples/demo")

