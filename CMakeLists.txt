cmake_minimum_required(VERSION 3.0)

project (moreinttypes VERSION 1.0.0 LANGUAGES C)

file(GLOB LIB_SRC "${PROJECT_SOURCE_DIR}/src/*.c")
file(GLOB PUBLIC_HEADERS "${PROJECT_SOURCE_DIR}/include/moreinttypes/*.h")
file(GLOB TYPES_API "${PROJECT_SOURCE_DIR}/include/moreinttypes/types/*.h")
file(GLOB UTILS_API "${PROJECT_SOURCE_DIR}/include/moreinttypes/utils/*.h")

add_library(moreinttypes SHARED ${LIB_SRC})
include_directories(moreinttypes "${PROJECT_SOURCE_DIR}/include")

set_target_properties (moreinttypes PROPERTIES
    COMPILE_DEFINITIONS BUILDING_MOREINTTYPES=1
    C_STANDARD 99
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build"
    # define these for .dll targets
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build")

if (MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  target_compile_options(moreinttypes PRIVATE /nologo /Ob1 /Ot /Zi /W3 /WX)
elseif(GNU)
  target_compile_options(moreinttypes PRIVATE
        -Wall
        -Wextra
        -Werror
        -pedantic
        -Wno-format
        -Wno-implicit-fallthrough
        -O2
        -Og
        -g)
  if(NOT MINGW)
    add_compile_options(-fsanitize=null,signed-integer-overflow,bounds)
    target_link_libraries(moreinttypes ubsan)
  endif()
endif()

install (TARGETS moreinttypes
         ARCHIVE DESTINATION lib
         LIBRARY DESTINATION lib
         RUNTIME DESTINATION bin)

install(FILES ${PUBLIC_HEADERS} DESTINATION include/moreinttypes)
install(FILES ${TYPES_API} DESTINATION include/moreinttypes/types)
install(FILES ${UTILS_API} DESTINATION include/moreinttypes/utils)
install(FILES "${PROJECT_SOURCE_DIR}/pkgconfig/moreinttypes.pc"
        DESTINATION lib/pkgconfig)

# Build and run demo application
set(CMAKE_INSTALL_RPATH lib)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
add_executable(libmoreinttypes-demo "${PROJECT_SOURCE_DIR}/examples/demo.c")
set_target_properties (libmoreinttypes-demo PROPERTIES
    C_STANDARD 90
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build")
target_include_directories(libmoreinttypes-demo PRIVATE "${PROJECT_SOURCE_DIR}/include/moreinttypes")
target_link_libraries(libmoreinttypes-demo PRIVATE moreinttypes)
add_custom_command(TARGET libmoreinttypes-demo
                  POST_BUILD
                  COMMAND "libmoreinttypes-demo"
                  WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/build")