# Build and run demo application
set(CMAKE_INSTALL_RPATH lib)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
add_executable(demo "main.c")
set_target_properties (demo PROPERTIES
    C_STANDARD 90
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build")
target_link_libraries(demo PRIVATE moreinttypes)
if(RUN_DEMO)
    add_custom_command(TARGET demo
                      POST_BUILD
                      COMMAND "demo"
                      WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/build")
endif()
