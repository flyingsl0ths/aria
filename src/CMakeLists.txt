list(
  APPEND aria_CORE "${PROJECT_SOURCE_DIR}/include/core/aria.hpp"
  "core/aria.cpp" "${PROJECT_SOURCE_DIR}/include/utils/common.hpp"
)

if(MSVC AND NOT BUILD_STATIC)
  add_library(aria-core SHARED ${aria_CORE})
else()
  set(SFML_STATIC_LIBRARIES TRUE)
  add_library(aria-core STATIC ${aria_CORE})
endif()

target_link_libraries(aria-core compile-options sfml-graphics)

target_include_directories(
  aria-core PUBLIC
  "${PROJECT_SOURCE_DIR}/include/"
  "${PROJECT_SOURCE_DIR}/src"
  "${PROJECT_BINARY_DIR}"
)
