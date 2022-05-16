# Build and run demo application
set(CMAKE_INSTALL_RPATH lib)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
add_executable(cpp-demo "main.cpp")
set_target_properties (cpp-demo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
if (MSVC)
    target_compile_options(cpp-demo PRIVATE /EHsc)
    if(CMAKE_BUILD_TYPE MATCHES "Debug")
      target_compile_options(cpp-demo PRIVATE /MTd)
    endif()
endif()
target_link_libraries(cpp-demo PRIVATE moreinttypes)
