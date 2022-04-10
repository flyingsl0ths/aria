#pragma once

#include <aria/command_line/command.hpp>
#include <aria/window/stage.hpp>

namespace aria::app
{

struct application
{
	virtual void init(std::optional<command_line::command_line_t>& args) = 0;
	virtual void on_start(stage::window& stage)							 = 0;
};

} // namespace aria::app
