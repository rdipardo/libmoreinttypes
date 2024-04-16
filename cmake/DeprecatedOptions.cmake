macro(deprecate_option OLD_OPTION NEW_OPTION)
  message(AUTHOR_WARNING
    "${OLD_OPTION} is deprecated! Use ${NEW_OPTION} instead.")
  set(${NEW_OPTION} "ON" CACHE BOOL
    "Replaces the deprecated ${OLD_OPTION} option" FORCE)
endmacro()

option(BUILD_STATIC "Build ${CMAKE_PROJECT_NAME} as a static library" OFF)
option(ENABLE_UBSAN "GCC,Clang: Enable the Undefined Behavior Sanitizer (ubsan)" OFF)
