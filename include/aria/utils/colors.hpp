#pragma once

#include <aria/utils/common.hpp>

#include <SFML/Graphics/Color.hpp>

namespace aria::colors
{

/// @brief An enum representing variations of the material design color palette
/// @see https://material.io/design/color/the-color-system.html#tools-for-picking-colors
/// under "2014 Material Design color palettes"
enum class color_swatch : u32
{
	white,
	gray_1,
	blue_gray_10,
	red_10,
};

/// @brief Converts the color_swatch variant to an sf::Color instance
/// Note: The resulting sf::Color may vary from what is show on the website referenced
/// @param shade The color to convert
/// @return The shade as an sf::Color instance
sf::Color to_color(color_swatch const shade);

} // namespace aria::colors
