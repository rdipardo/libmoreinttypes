# Build and run demo application
set(CMAKE_INSTALL_RPATH lib)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
add_executable(demo "main.c")
set_target_properties (demo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
target_link_libraries(demo PRIVATE moreinttypes)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_C_COMPILER_ID MATCHES "Clang")
    target_compile_options(demo PRIVATE -ansi -Wall -Werror -pedantic)
elseif(MSVC)
    target_compile_options(demo PRIVATE /nologo /Zi /W3 /WX)
endif()

if(RUN_DEMO)
    add_custom_command(TARGET demo
                      POST_BUILD
                      COMMAND "demo"
                      WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
endif()
