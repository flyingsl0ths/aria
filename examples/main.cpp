#include <iostream>

#include <aria/aria.hpp>
#include <aria/command_line/command.hpp>
#include <config.hpp>

s32 main(s32 argc, const char* argv[])
{

	auto parsed_flags = aria::command_line::parse(argc, argv);
	if (parsed_flags)
	{
		for (const auto& flag : *parsed_flags) { std::cout << flag << '\n'; }
	}

	std::cout << "Aria v" << ARIA_VERSION_MAJOR << '.' << ARIA_VERSION_MINOR << '.'
			  << ARIA_VERSION_PATCH << '\n';

	auto runner = aria::runner {};

	runner.run();

	return 0;
}
