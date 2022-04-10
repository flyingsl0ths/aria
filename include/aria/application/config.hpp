#pragma once

#include <aria/command_line/command.hpp>
#include <aria/utils/common.hpp>
#include <aria/window/titlebar_style.hpp>

namespace aria::app
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

} // namespace aria::app
