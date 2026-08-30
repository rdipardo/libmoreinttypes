# Build the gray16 application
set(CMAKE_INSTALL_RPATH lib)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
add_executable(gray16 "main.c")
set_target_properties (gray16 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
target_link_libraries(gray16 PRIVATE moreinttypes)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_C_COMPILER_ID MATCHES "Clang")
    target_compile_options(gray16 PRIVATE -Wall -Werror -pedantic)
elseif(MSVC)
    target_compile_options(gray16 PRIVATE /nologo /Zi /W4 /WX /wd4189)
endif()
