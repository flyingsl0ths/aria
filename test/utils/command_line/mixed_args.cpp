#include <aria/command_line/command.hpp>
#include <aria/utils/common.hpp>
#include <test_common.hpp>

s32 main(s32 argc, const char* argv[])
{
	using namespace aria;

	const auto flags = command_line::parse(argc, argv);

	if (!flags) { return EXIT_FAILURE; }

	const auto& parsed_flags = *flags;

	constexpr szt expected_flag_no {6UL};
	if (parsed_flags.size() != expected_flag_no)
	{
		std::cerr << "Failed to parse flags\n";
		return EXIT_FAILURE;
	}

	auto const passed_test = [](const command_line::command_line_t& cmd_flags)
	{
		const auto& first_val_flag	= cmd_flags[4UL];
		const auto& second_val_flag = cmd_flags[5UL];

		const bool val_flags_have_values =
			first_val_flag.value.has_value() && second_val_flag.value.has_value();

		return val_flags_have_values && (cmd_flags[0UL].name == "--enable-logging") &&
			   (cmd_flags[1UL].name == "--no-animations") && (cmd_flags[2UL].name == "-r") &&
			   (cmd_flags[3UL].name == "-c") &&
			   (first_val_flag.name == "-ll" && first_val_flag.value.value() == "warn") &&
			   (second_val_flag.name == "-f" && second_val_flag.value.value() == "bar");
	};

	return (passed_test(parsed_flags) ? EXIT_SUCCESS
									  : (std::cerr << "Incorrectly parsed flag\n", EXIT_FAILURE));
}
