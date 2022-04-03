add_library(test-case INTERFACE)
target_include_directories(test-case INTERFACE "${PROJECT_SOURCE_DIR}/include"
                                               "${PROJECT_SOURCE_DIR}/test")
target_sources(
  test-case INTERFACE "${PROJECT_SOURCE_DIR}/include/aria/utils/common.hpp"
                      "test_common.hpp")

add_subdirectory(utils/command_line)
