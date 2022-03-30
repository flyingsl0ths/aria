#pragma once

#include <utils/command_line/command.hpp>
#include <utils/common.hpp>

#include <SFML/Window/WindowStyle.hpp>

namespace aria::app_config
{

enum class theme : u8
{
	LIGHT,
	DARK
};

struct window_config final
{
	u32				   width {500U};
	u32				   height {500U};
	str				   title {"Aria"};
	sf::Style		   style {};
	std::optional<str> icon {};
	bool			   display_prompt_on_exit {};
};

struct config final
{
	window_config				 window {};
	theme						 app_theme {};
	command_line::command_line_t args {};
};

} // namespace aria::app_config
