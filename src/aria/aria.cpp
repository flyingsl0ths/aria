#include <aria/aria.hpp>
#include <aria/utils/time/time.hpp>
#include <aria/stage/stage.hpp>
#include "aria/utils/colors.hpp"
#include "aria/stage/cursor.hpp"
#include "aria/stage/titlebar_style.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

namespace aria
{

void runner::run()
{
	using namespace utils;

	constexpr u32		   WINDOW_WIDTH {1280};
	constexpr u32		   WINDOW_HEIGHT {720};
	constexpr time::time_t FPS {1.0F / 60.F};
	str constexpr WINDOW_NAME {"Aria"};

	stage::window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);

	constexpr f32 SHAPE_WIDTH {150.F};
	constexpr f32 SHAPE_HEIGHT {150.F};

	auto rect = sf::RectangleShape({SHAPE_WIDTH, SHAPE_HEIGHT});

	rect.setFillColor(colors::to_color(colors::color_swatch::red_10));

	rect.setPosition(
		{WINDOW_WIDTH / 2.0F - SHAPE_WIDTH / 2.0F, WINDOW_HEIGHT / 2.0F - SHAPE_HEIGHT / 2.0F});

	auto then = time::timer_t::now();

	std::array<f32, 2UL> mousePos {};
	while (window.is_open())
	{
		time::time_t delta = time::deltaTime(then);

		sf::Event event;

		if (delta >= FPS)
		{
			then = std::chrono::steady_clock::now();

			while (window.poll(event))
			{
				if (event.type == sf::Event::Closed) { window.close(); }
				if (event.type == sf::Event::MouseMoved)
				{
					mousePos[0UL] = event.mouseMove.x;
					mousePos[1UL] = event.mouseMove.y;
				}
			}

			window.draw(rect);

			window.draw_cursor(mousePos[0UL], mousePos[1UL]);
			window.display();
			window.clear();
		}
	}
}

} // namespace aria
