#include <iostream>

#include <aria/utils/image.hpp>
#include <aria/stage/stage.hpp>

#include <SFML/Graphics/Image.hpp>

namespace aria::stage
{

void window::icon(const str path) &
{
	auto image_data = utils::img::load_image(path);

	if (!image_data) { return; }

	auto& img = **image_data;

	auto icon_size = img.getSize();
	m_handle.setIcon(icon_size.x, icon_size.y, img.getPixelsPtr());
}

void window::close() &
{
	if (m_show_exit_prompt) { std::cout << "Exiting\n"; }
	if (m_on_close) { (*m_on_close)(); }
	m_handle.close();
}

} // namespace aria::stage
