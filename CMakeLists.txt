# ----------------------------------
# -- Force Out of source building --
# ----------------------------------
if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
  message( FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt and CMakeFiles directory." )
endif()


# ---------------------------- #
# -- Basic Project Settings -- #
# ---------------------------- #
cmake_minimum_required(VERSION 3.3.0 FATAL_ERROR)
project("openml"
  CXX
  )
set(CMAKE_BUILD_TYPE Release)

# Target properties
#set_target_properties(
#  )

# Project version
set(${CMAKE_PROJECT_NAME}_VERSION_MAJOR 0)
set(${CMAKE_PROJECT_NAME}_VERSION_MINOR 1)

# Cmake module/package search scripts
Set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  ${CMAKE_SOURCE_DIR}/cmake_modules
  )

# --------------- #
# -- Optionals -- #
# --------------- #
option(skipSFML
  "Do NOT use SFML for visualizations"
  OFF)



# -------------------------------------- #
# -- External Packages / Dependencies -- #
# -------------------------------------- #
# OpenCL
if (APPLE)
  find_library(OPENCL_LIBRARIES OpenCL)
  if (OPENCL_LIBRARIES)
    message(STATUS "OpenCL Found: ${OPENCL_LIBRARIES}")
    set(OPENCL_INCLUDE_DIR "${OPENCL_LIBRARIES}/Headers")
    set(OPENCL_FOUND true)
  endif(OPENCL_LIBRARIES)
endif (APPLE)

if (NOT OPENCL_FOUND)
  find_package(OpenCL REQUIRED)
endif(NOT OPENCL_FOUND)

# Boost
find_package(Boost 1.59 REQUIRED
  COMPONENTS
  unit_test_framework
  )


# SFML
if (NOT skipSFML)
  find_package(SFML 2.3
    COMPONENTS
    graphics
    system
    window
    )
endif(NOT skipSFML)

# ---------------------------------- #
# -- Compilation/linking Settings -- #
# ---------------------------------- #
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(warnings "-Wall -Wextra -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  set(warnings "/W4 /WX /EHsc")
endif()

set (modernCompile "-std=c++14")


if (NOT CONFIGURED_ONCE)
  set(CMAKE_CXX_FLAGS
    "${modernCompile} ${warnings}"
    CACHE STRING "Flags used by the compiler during all build types." FORCE
    )
endif()

#Bring the headers into the project
include_directories(
  /usr/local/include
  include
  ${OPENCL_INCLUDE_DIR}
  )

# Specify library paths
link_directories(
  /usr/local/lib
  ${CMAKE_BINARY_DIR}/src
  )



# --- Unit Testing Settings --- #
enable_testing()


# --- Source directories --- #
add_subdirectory(src)
add_subdirectory(tests)


set(CONFIGURED_ONCE TRUE CACHE INTERNAL
  "A flag showing that CMake has configured at least once.")
