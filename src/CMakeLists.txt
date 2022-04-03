list(APPEND command_line
     "${PROJECT_SOURCE_DIR}/include/aria/command_line/command.hpp"
     "aria/command_line/command.cpp")

list(APPEND time "${PROJECT_SOURCE_DIR}/include/aria/utils/time/time.hpp"
     "aria/utils/time/time.cpp")

list(APPEND core "${PROJECT_SOURCE_DIR}/include/aria/aria.hpp" "aria/aria.cpp"
     "${PROJECT_SOURCE_DIR}/include/aria/utils/common.hpp")

list(APPEND sources ${core} ${command_line} ${time})

if(NOT BUILD_STATIC)
  add_library(aria SHARED ${sources})
else()
  set(SFML_STATIC_LIBRARIES TRUE)
  add_library(aria STATIC ${sources})
endif()

target_link_libraries(aria compile-options sfml-graphics)

target_include_directories(
  aria PUBLIC "${PROJECT_SOURCE_DIR}/include/" "${PROJECT_SOURCE_DIR}/src"
              "${PROJECT_BINARY_DIR}")
