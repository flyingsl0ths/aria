#pragma once

#include <memory>
#include <optional>

#include "aria/utils/common.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Cursor.hpp>

namespace aria::stage::cursor
{

/// @brief An enum representing the available O.S cursors
enum class cursor_type : u8
{
	arrow,
	arrow_wait,
	wait,
	text,
	hand,
	size_horizontal,
	size_vertical,
	size_top_left_bottom_right,
	size_bottom_left_top_right,
	size_all,
	cross,
	help,
	not_allowed
};

/// @brief A struct representing the cursor's sprite
struct cursor_sprite final
{
	std::unique_ptr<sf::Texture> texture {};
	std::unique_ptr<sf::Sprite>	 img {};
};

using cursor = std::unique_ptr<sf::Cursor>;

/// @brief  Attempts to set the window's cursor via a user-specified image
//  @param image_path a path to the image containing the cursor's sprite
std::optional<cursor_sprite> load_from_image(str image_path);

/// @brief  Attempts to set the current window's cursor via a system default
/// @param cursor_type One of aria::window::cursor::cursor_type
/// @param cursor The cursor object to be modified
/// @param window The window whose's cursor will be modified
void load_from_system(cursor_type type, cursor& window_cursor, sf::RenderWindow& window);

} // namespace aria::stage::cursor
