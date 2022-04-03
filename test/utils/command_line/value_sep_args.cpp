#include <aria/command_line/command.hpp>
#include <aria/utils/common.hpp>
#include <test_common.hpp>

s32 main(s32 argc, const char* argv[])
{
	using namespace aria;

	const auto flags = command_line::parse(argc, argv);

	if (!flags) { return EXIT_FAILURE; }

	const auto& parsed_flags = *flags;

	constexpr szt expected_flag_no {2UL};
	if (parsed_flags.size() != expected_flag_no)
	{
		std::cerr << "Failed to parse flags\n";
		return EXIT_FAILURE;
	}

	auto const passed_test = [](const command_line::command_line_t& cmd_flags)
	{
		bool have_values {true};

		for (const auto& cmd : cmd_flags)
		{
			if (!cmd.value.has_value())
			{
				std::cerr << "Failed to parse values";
				have_values = false;
				break;
			}
		}

		const auto& first  = cmd_flags[0UL];
		const auto& second = cmd_flags[1UL];

		return have_values && (first.name == "--log-level" && first.value.value() == "warn") &&
			   (second.name == "--animation-speed" && second.value.value() == "'fast'");
	};

	return (passed_test(parsed_flags) ? EXIT_SUCCESS
									  : (std::cerr << "Incorrectly parsed flag\n", EXIT_FAILURE));
}
