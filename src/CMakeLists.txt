list(
  APPEND core "${PROJECT_SOURCE_DIR}/include/core/aria.hpp"
  "core/aria.cpp" "${PROJECT_SOURCE_DIR}/include/utils/common.hpp"
)

if(NOT BUILD_STATIC)
  add_library(aria SHARED ${core})
else()
  set(SFML_STATIC_LIBRARIES TRUE)
  add_library(aria STATIC ${core})
endif()

target_link_libraries(aria compile-options sfml-graphics)

target_include_directories(
  aria PUBLIC
  "${PROJECT_SOURCE_DIR}/include/"
  "${PROJECT_SOURCE_DIR}/src"
  "${PROJECT_BINARY_DIR}"
)
