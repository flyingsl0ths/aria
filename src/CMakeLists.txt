list(
  APPEND application
  "${PROJECT_SOURCE_DIR}/include/aria/application/config.hpp"
  "${PROJECT_SOURCE_DIR}/include/aria/application/application.hpp"
)

list(
  APPEND window
  "${PROJECT_SOURCE_DIR}/include/aria/stage/stage.hpp" "aria/stage/stage.cpp"
  "${PROJECT_SOURCE_DIR}/include/aria/stage/cursor.hpp" "aria/stage/cursor.cpp"
  "${PROJECT_SOURCE_DIR}/include/aria/stage/titlebar_style.hpp"
)

list(
  APPEND utils "${PROJECT_SOURCE_DIR}/include/aria/utils/time/time.hpp"
  "aria/utils/time/time.cpp"
  "${PROJECT_SOURCE_DIR}/include/aria/utils/common.hpp"
  "${PROJECT_SOURCE_DIR}/include/aria/utils/colors.hpp" "aria/utils/colors.cpp"
  "${PROJECT_SOURCE_DIR}/include/aria/utils/image.hpp" "aria/utils/image.cpp"
  "${PROJECT_SOURCE_DIR}/include/aria/utils/types.hpp"
)

list(
  APPEND command_line
  "${PROJECT_SOURCE_DIR}/include/aria/command_line/command.hpp"
  "aria/command_line/command.cpp"
)

list(APPEND core "${PROJECT_SOURCE_DIR}/include/aria/aria.hpp" "aria/aria.cpp")

list(APPEND sources ${core} ${application} ${window} ${utils} ${command_line})

if(NOT BUILD_STATIC)
  add_library(aria SHARED ${sources})
else()
  set(SFML_STATIC_LIBRARIES TRUE)
  add_library(aria STATIC ${sources})
endif()

target_link_libraries(aria compile-options sfml-graphics)

target_include_directories(
  aria PUBLIC "${PROJECT_SOURCE_DIR}/include/" "${PROJECT_SOURCE_DIR}/src"
  "${PROJECT_BINARY_DIR}"
)
