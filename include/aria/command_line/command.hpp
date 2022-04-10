#pragma once

#include <optional>
#include <ostream>
#include <vector>

#include <aria/utils/common.hpp>

namespace aria::command_line
{

/// @brief A struct used to represent a parsed commmand line flag
struct command final
{
	str				   name {};
	std::optional<str> value {};

	friend std::ostream& operator<<(std::ostream& out, const command& cmd)
	{
		out << cmd.name;
		if (cmd.value) { out << ":\t" << *(cmd.value); }
		return out;
	}
};

using command_line_t = std::vector<command>;

/// @brief Parses arguments passed to the application via the main function
/// @param argc The number of arguments received
/// @param argv The arguments themselves
/// @return parsed command line flags if any
std::optional<command_line_t> parse(s32 argc, const char* const argv[]);

} // namespace aria::command_line
