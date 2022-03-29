add_executable(foo foo.cpp "${PROJECT_SOURCE_DIR}/include/utils/common.hpp")

target_include_directories(foo PRIVATE "${PROJECT_SOURCE_DIR}/include")

target_link_libraries(foo PRIVATE compile-options)

add_test(NAME FOO_TEST COMMAND foo)
