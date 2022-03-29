#include <chrono>
#include <iostream>

#include <core/aria.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

namespace aria
{

void runner::run()
{

	constexpr u32 WINDOW_WIDTH {1280};
	constexpr u32 WINDOW_HEIGHT {720};
	constexpr f32 FPS {1.0F / 60.F};
	constexpr str WINDOW_NAME {"Breeze"};

	sf::RenderWindow window(
		sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME.data(), sf::Style::Close);

	window.setVerticalSyncEnabled(true);

	constexpr f32 SHAPE_WIDTH {150.F};
	constexpr f32 SHAPE_HEIGHT {150.F};

	auto rect = sf::RectangleShape(sf::Vector2f {SHAPE_WIDTH, SHAPE_HEIGHT});

	rect.setFillColor(sf::Color::Red);

	rect.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0F - SHAPE_WIDTH / 2.0F,
								  WINDOW_HEIGHT / 2.0F - SHAPE_HEIGHT / 2.0F));

	auto then = std::chrono::steady_clock::now();

	while (window.isOpen())
	{
		f32 delta = std::chrono::duration_cast<std::chrono::duration<f32>>(
						std::chrono::steady_clock::now() - then)
						.count();

		sf::Event event;

		if (delta >= FPS)
		{
			then = std::chrono::steady_clock::now();

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::KeyPressed)
				{
					if (bool const closeWindow(event.type == sf::Event::Closed ||
											   event.key.code == sf::Keyboard::Q);
						closeWindow)
					{
						window.close();
					}
				}
			}

			window.draw(rect);

			window.display();
			window.clear();
		}
	}
}

} // namespace aria
