#include <aria/stage/cursor.hpp>
#include <aria/stage/stage.hpp>
#include "aria/utils/image.hpp"

namespace aria::stage::cursor
{

std::optional<cursor_sprite> load_from_image(str const image_path)
{
	auto cursor_texture = std::make_unique<sf::Texture>();
	if (!cursor_texture->loadFromFile(image_path.data())) { return {}; }
	auto cursor_img = std::make_unique<sf::Sprite>();
	cursor_img->setTexture(*cursor_texture);

	return cursor_sprite {std::move(cursor_texture), std::move(cursor_img)};
}

void load_from_system(cursor_type const type, cursor& window_cursor, sf::RenderWindow& window)
{
	if (window_cursor->loadFromSystem(static_cast<sf::Cursor::Type>(type)))
	{
		window.setMouseCursor(*window_cursor);
	}
}

} // namespace aria::stage::cursor
