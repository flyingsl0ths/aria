#pragma once

#include "command_line/command.hpp"
#include "utils/common.hpp"

#include <SFML/Window/WindowStyle.hpp>

namespace aria::app_config
{

/// @brief A struct used to specify the application's theme
enum class theme : u8
{
	LIGHT,
	DARK
};

/// @brief A struct used to configure window parameters
struct window final
{
	u32				   width {500U};
	u32				   height {500U};
	str				   title {"Aria"};
	sf::Style		   style {};
	std::optional<str> icon {};
	bool			   display_prompt_on_exit {};
	bool			   enable_v_sync {};
};

/// @brief A struct used to configure application parameters
struct config final
{
	window										window {};
	theme										app_theme {};
	std::optional<command_line::command_line_t> args {};
};

} // namespace aria::app_config
