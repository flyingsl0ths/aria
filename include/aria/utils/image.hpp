#pragma once

#include <memory>
#include <optional>

#include "common.hpp"

#include <SFML/Graphics/Image.hpp>

namespace utils::img
{

/// @brief Attempts to load the sf::Image specified via the given file path
/// @img_path The image's file path
/// @return The loaded image
std::optional<std::unique_ptr<sf::Image>> load_image(str const img_path);

} // namespace utils::img
