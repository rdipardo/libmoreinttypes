macro(project_version OUTPUT_VAR FILENAME)
    file (TO_CMAKE_PATH "${FILENAME}" VERSION_SRC)

    if(CMAKE_HOST_WIN32)
      string(REGEX REPLACE "/" "\\\\" VERSION_SRC_DOS "${VERSION_SRC}")
      set (CMD "cmd.exe")
      set (ARGS "/c type ${VERSION_SRC_DOS}")
    else()
      set (CMD "cat")
      set (ARGS "${VERSION_SRC}")
    endif()

    execute_process (WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
                     COMMAND ${CMD} ${ARGS}
                     OUTPUT_VARIABLE VERSION_STR
                     OUTPUT_STRIP_TRAILING_WHITESPACE)

    if(NOT "${VERSION_STR}" STREQUAL "")
        set (SEMVER_STR "")
        string (REGEX MATCHALL "[0-9][\\.0-9]*" X_Y_Z ${VERSION_STR})
        string (CONCAT SEMVER ${X_Y_Z})
        string (REGEX REPLACE "\\.$" "" SEMVER_STR ${SEMVER})
    endif()

    if ("${SEMVER_STR}" STREQUAL "")
      message (SEND_ERROR
               "No version number in x[.]y[.]z[.a] format found in "
               ${FILENAME})
    else()
      set (${OUTPUT_VAR} ${SEMVER_STR})
      message (STATUS "Setting project version to " ${SEMVER_STR})
    endif()
endmacro()