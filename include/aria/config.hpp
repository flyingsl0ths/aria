#pragma once

#include "aria/window/titlebar_style.hpp"
#include "command_line/command.hpp"
#include "utils/common.hpp"

namespace aria::app_config
{

/// @brief A struct used to specify the application's theme
enum class theme : u8
{
	LIGHT,
	DARK
};

/// @brief A struct used to configure application parameters
struct config final
{
	theme										app_theme {};
	std::optional<command_line::command_line_t> args {};
};

} // namespace aria::app_config
