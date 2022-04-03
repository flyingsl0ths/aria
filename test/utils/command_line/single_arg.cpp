#include <aria/command_line/command.hpp>
#include <aria/utils/common.hpp>
#include <test_common.hpp>

s32 main(s32 argc, const char* argv[])
{
	using namespace aria;

	const auto flags = command_line::parse(argc, argv);

	if (!flags)
	{
		std::cerr << "No flags parsed\n";
		return EXIT_FAILURE;
	}

	const auto& cmd_flags = *flags;

	constexpr szt expected_flag_no {1UL};
	if (cmd_flags.size() != expected_flag_no)
	{
		std::cerr << "Failed to parse single flag given\n";
		return EXIT_FAILURE;
	}

	auto const passed_test = [&cmd_flags]()
	{
		const auto& head = cmd_flags[0UL];
		return (head.name == "--enable-logging" && !(head.value.has_value()) ? EXIT_SUCCESS
																			 : EXIT_FAILURE);
	};

	return passed_test();
}
