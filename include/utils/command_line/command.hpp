#pragma once

#include <optional>
#include <vector>

#include <utils/common.hpp>

namespace command_line
{

struct command final
{
	str				   name {};
	std::optional<str> value {};
};

using command_line_t = std::vector<command>;

} // namespace command_line
