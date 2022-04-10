#include <aria/utils/image.hpp>

namespace utils::img
{

std::optional<std::unique_ptr<sf::Image>> load_image(str const path)
{
	if (path.empty()) { return {}; }

	auto img = std::make_unique<sf::Image>();

	if (!img->loadFromFile(path.data())) { return {}; }

	return {std::move(img)};
}

} // namespace utils::img
