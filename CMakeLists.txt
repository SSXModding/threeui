cmake_minimum_required(VERSION 3.10..4.69)


# Prohibit in-source tree builds.
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "In-source builds are strictly prohibited.")
endif()

project(threeui
        VERSION 0.1.0
        LANGUAGES C CXX
        )

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(Policies)
include(tuiProjectFuncs)

# requirements
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# FIXME //third_party/mcolib
add_subdirectory(third_party)

# components
add_subdirectory(src/threeui)

