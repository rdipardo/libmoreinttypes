cmake_minimum_required(VERSION 3.0)

project (moreinttypes VERSION 1.1.0)

file(GLOB LIB_SRC "${PROJECT_SOURCE_DIR}/src/*.c*")
file(GLOB PUBLIC_HEADERS "${PROJECT_SOURCE_DIR}/include/moreinttypes/*.h")
file(GLOB TYPES_API "${PROJECT_SOURCE_DIR}/include/moreinttypes/types/*.h")
file(GLOB UTILS_API "${PROJECT_SOURCE_DIR}/include/moreinttypes/utils/*.h")

add_library(moreinttypes SHARED ${LIB_SRC})
include_directories(moreinttypes "${PROJECT_SOURCE_DIR}/include")

set_target_properties (moreinttypes PROPERTIES
    VERSION ${PROJECT_VERSION}
    COMPILE_DEFINITIONS BUILDING_MOREINTTYPES=1
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build"
    # define these for .dll targets
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build")

if (MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  target_compile_options(moreinttypes PUBLIC /nologo /Ob1 /Ot /Zi /W3 /WX /wd4190)
endif()
# will test TRUE for MinGW -- see next comment
if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
  target_compile_options(moreinttypes PRIVATE
        -Wall
        -Werror
        -pedantic
        -Wno-format
        -Wno-implicit-fallthrough
        -O2
        -g)
  # don't pass -lubsan to the linker when building with MinGW
  if((CMAKE_COMPILER_IS_GNUCC
        AND CMAKE_C_COMPILER_VERSION GREATER 4.8)
      OR (CMAKE_C_COMPILER_ID STREQUAL "Clang"
        AND CMAKE_C_COMPILER_VERSION GREATER 3.7)
      AND NOT WIN32)
    add_compile_options(-fsanitize=null,signed-integer-overflow,bounds)
    link_libraries(-fsanitize=undefined)
  endif()
  # enable the %Lf format specifier in MinGW builds
  if(WIN32)
    target_compile_definitions(moreinttypes PUBLIC -D__USE_MINGW_ANSI_STDIO)
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

add_subdirectory("${PROJECT_SOURCE_DIR}/examples/demo++")
add_subdirectory("${PROJECT_SOURCE_DIR}/examples/demo")

