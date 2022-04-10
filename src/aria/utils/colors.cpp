#include <aria/utils/colors.hpp>

namespace aria::colors
{

sf::Color to_color(color_swatch const shade)
{
	switch (shade)
	{
		case color_swatch::white: return sf::Color(225, 225, 225);
		case color_swatch::gray_1: return sf::Color(98, 98, 98); break;
		case color_swatch::blue_gray_10: return sf::Color(14, 19, 22); break;
		case color_swatch::red_10: return sf::Color(141, 11, 11);
	}
}

} // namespace aria::colors
