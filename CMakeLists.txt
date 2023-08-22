cmake_minimum_required(VERSION 3.13) # https://github.com/libcheck/check/issues/325
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR};${CMAKE_MODULE_PATH}")
include(ProjectVersion)
include(DeprecatedOptions)

project_version (PROJECT_VERSION "pkgconfig/moreinttypes.pc")
project (moreinttypes VERSION ${PROJECT_VERSION})

file(GLOB LIB_SRC "${PROJECT_SOURCE_DIR}/src/*.c*")
file(GLOB PUBLIC_HEADERS "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/*.h")
file(GLOB TYPES_API "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/types/*.h")
file(GLOB UTILS_API "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/utils/*.h")

add_library(${PROJECT_NAME} SHARED ${LIB_SRC})
target_include_directories(${PROJECT_NAME} PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>")

if(CMAKE_HOST_WIN32)
  add_subdirectory("${PROJECT_SOURCE_DIR}/src/win32")
endif()

set_target_properties (${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    COMPILE_DEFINITIONS BUILDING_MOREINTTYPES=1
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
    # define these for .dll targets
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

# ==================================================
# Build options
# ==================================================
option(MOREINTTYPES_BUILD_STATIC
  "Build ${CMAKE_PROJECT_NAME} as a static library" OFF)

option(MOREINTTYPES_ENABLE_UBSAN
  "GCC,Clang: Enable the Undefined Behavior Sanitizer (ubsan)" OFF)

option(MOREINTTYPES_BUILD_TESTS
  "Build and run unit tests" ON)

option(MOREINTTYPES_BUILD_EXAMPLES
  "Build example programs" OFF)

# ==================================================
# Feature tests
# ==================================================
if (BUILD_STATIC)
  deprecate_option(BUILD_STATIC MOREINTTYPES_BUILD_STATIC)
endif()

if (ENABLE_UBSAN)
  deprecate_option(ENABLE_UBSAN MOREINTTYPES_ENABLE_UBSAN)
endif()

if (MOREINTTYPES_BUILD_STATIC)
  get_target_property(BUILD_HEADERS ${PROJECT_NAME} INCLUDE_DIRECTORIES)
  add_library(${PROJECT_NAME}-static STATIC ${LIB_SRC})
  target_include_directories(${PROJECT_NAME}-static PUBLIC ${BUILD_HEADERS})

  set_target_properties (${PROJECT_NAME}-static PROPERTIES
      VERSION ${PROJECT_VERSION}
      COMPILE_DEFINITIONS MOREINTTYPES_EXPORTS_BUILT_AS_STATIC=1
      OUTPUT_NAME ${PROJECT_NAME}
      ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/static")

  install (TARGETS ${PROJECT_NAME}-static
           ARCHIVE DESTINATION lib)
endif()

if(CMAKE_BUILD_TYPE MATCHES "Debug")
  add_compile_definitions(_DEBUG)
  set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")
  if (MOREINTTYPES_BUILD_STATIC)
    set_target_properties(${PROJECT_NAME}-static PROPERTIES DEBUG_POSTFIX "d")
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
  target_compile_options(${PROJECT_NAME} PRIVATE /nologo /Zi /W4 /WX /wd4190)
  if (MOREINTTYPES_BUILD_STATIC)
    target_compile_options(${PROJECT_NAME}-static PRIVATE /nologo /Zi /W4 /WX)
  endif()

  if(CMAKE_BUILD_TYPE MATCHES "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE /Od /LDd /DDEBUG)
    target_link_libraries(${PROJECT_NAME} PRIVATE -OPT:REF -INCREMENTAL:NO -DEBUG)
    if (MOREINTTYPES_BUILD_STATIC)
      target_compile_options(${PROJECT_NAME}-static PRIVATE /Od /MTd /DDEBUG)
    endif()
  else()
    target_compile_options(${PROJECT_NAME} PUBLIC /Ob1 /Ot /LD /DNDEBUG)
    if (MOREINTTYPES_BUILD_STATIC)
      target_compile_options(${PROJECT_NAME}-static PUBLIC /Ob1 /Ot /MT /DNDEBUG)
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
  if(MOREINTTYPES_ENABLE_UBSAN AND ((CMAKE_COMPILER_IS_GNUCC
        AND CMAKE_C_COMPILER_VERSION GREATER 4.8)
      OR (CMAKE_C_COMPILER_ID MATCHES "Clang"
        AND CMAKE_C_COMPILER_VERSION GREATER 3.7)
      AND NOT WIN32))
    list(APPEND POSIX_C_FLAGS
        -fsanitize=null,signed-integer-overflow,bounds,undefined)
    target_link_libraries(${PROJECT_NAME} PUBLIC -fsanitize=undefined)
  endif()
  # enable the %Lf format specifier in MinGW builds
  if(WIN32)
    add_compile_definitions(__USE_MINGW_ANSI_STDIO)
  endif()

  if(CMAKE_BUILD_TYPE MATCHES "Debug")
    list(APPEND POSIX_C_FLAGS -Og)
  endif()

  target_compile_options(${PROJECT_NAME} PRIVATE ${POSIX_C_FLAGS})
endif()

install (TARGETS ${PROJECT_NAME}
         ARCHIVE DESTINATION lib
         LIBRARY DESTINATION lib
         RUNTIME DESTINATION bin)

install(FILES ${PUBLIC_HEADERS} DESTINATION include/${PROJECT_NAME})
install(FILES ${TYPES_API} DESTINATION include/${PROJECT_NAME}/types)
install(FILES ${UTILS_API} DESTINATION include/${PROJECT_NAME}/utils)
install(FILES "${PROJECT_SOURCE_DIR}/pkgconfig/${PROJECT_NAME}.pc"
        DESTINATION lib/pkgconfig)

if(MOREINTTYPES_BUILD_TESTS)
  add_subdirectory("${PROJECT_SOURCE_DIR}/test")
endif()

if(MOREINTTYPES_BUILD_EXAMPLES)
  add_subdirectory("${PROJECT_SOURCE_DIR}/examples/demo++")
  add_subdirectory("${PROJECT_SOURCE_DIR}/examples/demo")
endif()
