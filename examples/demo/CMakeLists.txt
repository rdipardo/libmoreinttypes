# Build and run demo application
set(CMAKE_INSTALL_RPATH lib)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
add_executable(libmoreinttypes-demo "main.c")
set_target_properties (libmoreinttypes-demo PROPERTIES
    C_STANDARD 90
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build")
target_include_directories(libmoreinttypes-demo PRIVATE
                           "${PROJECT_SOURCE_DIR}/include/moreinttypes")
target_link_libraries(libmoreinttypes-demo PRIVATE moreinttypes)
add_custom_command(TARGET libmoreinttypes-demo
                  POST_BUILD
                  COMMAND "libmoreinttypes-demo"
                  WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/build")
