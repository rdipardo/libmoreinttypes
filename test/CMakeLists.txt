# Build and run unit tests
include (ExternalProject)
set(CMAKE_INSTALL_RPATH lib)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CppUTestRootDirectory "${PROJECT_SOURCE_DIR}/test/cpputest")
externalproject_add (
    cpputest-build
    GIT_REPOSITORY "https://github.com/cpputest/cpputest.git"
    GIT_TAG latest-passing-build
    PREFIX "${CppUTestRootDirectory}"
    SOURCE_DIR "${CppUTestRootDirectory}/git"
    BINARY_DIR "${CppUTestRootDirectory}/git/cpputest_build"
    CMAKE_ARGS "-DCMAKE_BUILD_TYPE=Debug;-DEXTENSIONS=OFF;-DTESTS=OFF;-DTESTS_BUILD_DISCOVER=OFF"
    INSTALL_COMMAND ""
)
externalproject_get_property(cpputest-build BINARY_DIR)
set(CPPUTEST_STATIC "libCppUTest.a")

if (MSVC)
    set(CPPUTEST_STATIC "CppUTest.lib")
endif()

list(APPEND UTEST_DEPS
    "${BINARY_DIR}/src/CppUTest/${CPPUTEST_STATIC}"
    moreinttypes)
file(GLOB UTEST_SRC "src/*.c*")

add_subdirectory ("include")
add_executable(utests ${UTEST_SRC} $<TARGET_OBJECTS:utesthelpers>)
add_dependencies (utests cpputest-build)
target_include_directories(utests PRIVATE "include" "${CppUTestRootDirectory}/git/include")
target_link_libraries(utests PRIVATE ${UTEST_DEPS})
target_compile_definitions(utests PRIVATE -DUSE_64_BITS)

if (MSVC)
    target_compile_options(utests PRIVATE /Od /MDd /EHsc /DDEBUG)
    target_link_libraries (utests PRIVATE winmm.lib)
endif()

set(CHECKER )
if(WITH_VALGRIND)
    find_program(VALGRIND "valgrind")
    if(VALGRIND)
        list (APPEND MEM_CHECK_ARGS
              --leak-check=full
              --track-origins=yes
              --suppressions="${PROJECT_SOURCE_DIR}/test/valgrind.supp"
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
