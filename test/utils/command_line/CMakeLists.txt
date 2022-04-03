add_library(command-parser-test INTERFACE)
target_sources(
  command-parser-test
  INTERFACE "${PROJECT_SOURCE_DIR}/include/aria/command_line/command.hpp"
            "${PROJECT_SOURCE_DIR}/src/aria/command_line/command.cpp")
target_link_libraries(command-parser-test INTERFACE test-case)

add_executable(single_arg "single_arg.cpp")
target_link_libraries(single_arg PRIVATE compile-options command-parser-test)
add_test(NAME CMD_LINE_SINGLE_ARG_TEST COMMAND single_arg "--enable-logging")

add_executable(mixed_args "mixed_args.cpp")
target_link_libraries(mixed_args PRIVATE compile-options command-parser-test)
add_test(NAME CMD_LINE_MIXED_ARG_TEST
         COMMAND mixed_args "--enable-logging" "--no-animations" "-r" "-c"
                 "-ll" "warn" "-f" "bar")

add_executable(value_sep_args "value_sep_args.cpp")
target_link_libraries(value_sep_args PRIVATE compile-options
                                             command-parser-test)
add_test(NAME CMD_LINE_VALUE_SEPARATED_ARG_TEST
         COMMAND value_sep_args "--log-level=warn" "--animation-speed='fast'")
