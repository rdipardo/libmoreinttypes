# Build and run unit tests
include (ExternalProject)
set(CMAKE_INSTALL_RPATH lib)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(LibCheckRootDirectory "${PROJECT_SOURCE_DIR}/test/check")
externalproject_add (
    libcheck
    GIT_REPOSITORY "https://github.com/libcheck/check.git"
    GIT_TAG "0.15.2"
    GIT_SHALLOW 1
    SOURCE_DIR "${LibCheckRootDirectory}"
    BUILD_IN_SOURCE 0
    CMAKE_ARGS "-DCMAKE_BUILD_TYPE=Debug;-DBUILD_TESTING=OFF"
    INSTALL_COMMAND ""
)
externalproject_get_property(libcheck BINARY_DIR)

# link statically on all platforms but Linux:
# https://github.com/libcheck/check/issues/156#issuecomment-402209866
# https://github.com/libcheck/check/issues/48#issuecomment-224461999
set(LIBCOMPAT "libcompat.a")
if(CMAKE_HOST_APPLE OR MINGW)
    set(LIBCHECK "libcheck.a")
else()
    set(LIBCHECK "libcheck.so")
endif()

if (MSVC)
    set(LIBCHECK "check.lib")
    set(LIBCOMPAT "compat.lib")
endif()

file (TO_CMAKE_PATH "${BINARY_DIR}/src/${LIBCHECK}" LIBCHECK_PATH)
file (TO_CMAKE_PATH "${BINARY_DIR}/lib/${LIBCOMPAT}" LIBCOMPAT_PATH)

if(CMAKE_HOST_WIN32)
    string(REGEX REPLACE "/" "\\\\" LIBCHECK "${LIBCHECK_PATH}")
    string(REGEX REPLACE "/" "\\\\" LIBCOMPAT "${LIBCOMPAT_PATH}")
else()
    set(LIBCHECK "${LIBCHECK_PATH}")
    set(LIBCOMPAT "${LIBCOMPAT_PATH}")
endif()

file(GLOB UTEST_SRC "src/*.c")
add_executable(utests ${UTEST_SRC})
add_dependencies (utests libcheck)
target_include_directories(utests PRIVATE "${BINARY_DIR}" "${BINARY_DIR}/src")
list(APPEND UTEST_DEPS "${LIBCHECK}" "${LIBCOMPAT}" moreinttypes)
target_link_libraries(utests PRIVATE ${UTEST_DEPS})
target_compile_definitions(utests PRIVATE -DUSE_64_BITS)

if (MSVC)
    target_compile_options(utests PRIVATE /Od /MDd /DDEBUG)
else()
    target_compile_options(utests PRIVATE
      -Wno-overlength-strings
      -Wno-gnu-zero-variadic-macro-arguments)
endif()

set(CHECKER )
if(WITH_VALGRIND)
  deprecate_option(WITH_VALGRIND MOREINTTYPES_CHECK_WITH_VALGRIND)
endif()

if(MOREINTTYPES_CHECK_WITH_VALGRIND)
    find_program(VALGRIND "valgrind")
    if(VALGRIND)
        list (APPEND MEM_CHECK_ARGS
              --leak-check=full
              --track-origins=yes
              --error-exitcode=1)
        list (APPEND CHECKER "${VALGRIND}" ${MEM_CHECK_ARGS})
        target_compile_definitions(utests PRIVATE -DVALGRIND)
    endif()
endif()

set_target_properties (utests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
add_custom_command(TARGET utests
    POST_BUILD
    COMMAND ${CHECKER} "$<TARGET_FILE:utests>"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
