cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

if("${CMAKE_BUILD_TYPE}" STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
  message(STATUS "Exporting compile commands")
endif()

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(BUILD_SHARED_LIBS OFF)

option(BUILD_EXAMPLES "Build examples" ON)

option(BUILD_STATIC "Builds Aria as a static library" ON)

option(RUN_TESTS "Runs tests" ON)

set(NAME ARIA)
set(DESCRIPTION "A GUI toolkit inspired by Google's material design")

project(
  ${NAME}
  VERSION 0.0.1
  DESCRIPTION ${DESCRIPTION}
  LANGUAGES CXX)

configure_file("${PROJECT_SOURCE_DIR}/config.hpp.in"
               "${PROJECT_BINARY_DIR}/config.hpp")

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "In Source Builds Not Allowed")
endif()

set(SFML_VERSION 2.5.1)

# Check if external project already located SFML
if(NOT SFML_FOUND)
  find_package(SFML ${SFML_VERSION} QUIET COMPONENTS graphics)
endif()

# Default to submodule if prior find_package call failed
if(NOT SFML_FOUND)
  include(cmake/git.cmake)

  find_package(Git QUIET)

  if(GIT_FOUND)
    option(BREEZE_SUBMODULES_UPDATE
           "Init/Update the submodules used by project" TRUE)

    if(BREEZE_SUBMODULES_UPDATE)
      git_update_submodules(FATAL_ERROR)
      add_subdirectory(ext/SFML)
    endif()
  endif()
endif()

add_library(compile-options INTERFACE)

target_compile_features(compile-options INTERFACE cxx_std_17)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL
                                             "GNU")
  target_compile_options(
    compile-options
    INTERFACE "-Wextra;-Wall;-Wsign-conversion;-Werror;-Wunused-local-typedefs")
endif()

add_subdirectory(src)

if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

if(RUN_TESTS)
  enable_testing()
  add_subdirectory("test/")
endif()
