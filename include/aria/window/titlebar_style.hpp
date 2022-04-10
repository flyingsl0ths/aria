#pragma once

#include <aria/utils/common.hpp>

namespace aria::stage
{

/// @brief An enum representing the available window titlebar styles
enum class titlebar_style : u32
{
	none	   = 0U,
	titlebar   = 1U << 0U,
	resize	   = 1U << 1U,
	close	   = 1U << 2U,
	fullscreen = 1U << 3U,
	normal	   = titlebar | resize | close
};

/// @brief A "to string" function for titlebar_style variants
/// @style The titlebar_style variant
/// @return The variant's name as a string without the namespacing
constexpr str to_str(titlebar_style const style) noexcept
{
	switch (style)
	{
		case titlebar_style::none: return "None";
		case titlebar_style::titlebar: return "Titlebar";
		case titlebar_style::resize: return "Resize";
		case titlebar_style::close: return "Close";
		case titlebar_style::fullscreen: return "Fullscreen";
		case titlebar_style::normal: return "Default";
		default: return "???";
	}
}

} // namespace aria::stage
