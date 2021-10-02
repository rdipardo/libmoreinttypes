# Build and run rtrim() demo application
set(CMAKE_INSTALL_RPATH lib)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
add_executable(rtrim-demo "main.cpp")
set_target_properties (rtrim-demo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build")
if (MSVC)
    target_compile_options(rtrim-demo PRIVATE /EHsc)
endif()
target_link_libraries(rtrim-demo PRIVATE moreinttypes)

if(RUN_RTRIM_DEMO)
    find_program(VALGRIND "valgrind")
    if(VALGRIND)
        list (APPEND MEM_CHECK_ARGS --leak-check=full --show-reachable=yes)
        list (APPEND CHECKER "${VALGRIND}" ${MEM_CHECK_ARGS})
    else()
        set(CHECKER )
    endif()

    add_custom_command(TARGET rtrim-demo
                      POST_BUILD
                      COMMAND ${CHECKER} "$<TARGET_FILE:rtrim-demo>"
                      WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/build")
endif()
