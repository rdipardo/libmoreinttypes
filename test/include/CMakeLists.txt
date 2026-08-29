# Build test helper library
add_library(utesthelpers OBJECT "TestHelpers.cpp")
target_include_directories(utesthelpers PRIVATE "${PROJECT_SOURCE_DIR}/include")
target_compile_definitions(utesthelpers PRIVATE -DUSE_64_BITS)
if (MSVC)
    target_compile_options(utesthelpers PRIVATE /EHsc /wd4190)
endif()
