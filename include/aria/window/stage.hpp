#pragma once

#include <functional>
#include <memory>
#include <optional>

#include <SFML/Graphics/Shape.hpp>
#include <aria/utils/colors.hpp>
#include <aria/utils/common.hpp>
#include <aria/utils/types.hpp>
#include "aria/window/cursor.hpp"
#include "aria/window/titlebar_style.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/VertexBuffer.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Cursor.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

namespace aria::stage
{

/// @brief A class representing the application window
/// Any methods undocumented are just wrappers around @see
/// https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1RenderWindow.php
class window final
{
  public:
	using callback = std::function<void()>;

  public:
	window(const u32			width,
		   const u32			height,
		   str const			title,
		   titlebar_style const style = titlebar_style::normal)
		: m_title(title)
		, m_handle(sf::VideoMode(width, height), title.data(), static_cast<u32>(style))

	{
	}

	window(const window&) = delete;

	window(window&&) noexcept(false) = delete;

	~window() = default;

  public:
	window& operator=(const window&) = delete;

	window& operator=(window&&) noexcept(false) = delete;

  public:
	[[nodiscard]] str title() & noexcept { return m_title; }

	/// @brief Gets the window's titlebar style
	/// @return The window's set titlebar style
	[[nodiscard]] titlebar_style style() & noexcept { return m_style; }

	[[nodiscard]] sf::Vector2i position() & { return m_handle.getPosition(); }

	[[nodiscard]] sf::Vector2u size() & { return m_handle.getSize(); }

	/// @brief Checks if the window currently has focus
	[[nodiscard]] bool has_focus() & { return m_handle.hasFocus(); }

	/// @brief Checks if the window's cursor will be visibile
	/// This will be affected by both forms of window::change_cursor
	/// @returns Whether the window will display the cursor
	[[nodiscard]] bool cursor_visible() & noexcept { return m_cursor_visible; }

	[[nodiscard]] bool grabbed_cursor() & noexcept { return m_grabbed_cursor; }

	/// @brief Checks if the window's cursor is a custom image
	[[nodiscard]] bool has_custom_cursor() & noexcept { return m_custom_cursor.has_value(); }

	/// @brief Sets the background color of the window
	//  Primarily used when switching between application themes and window::clear
	/// @bg_color The updated bg color
	void set_bg_color(colors::color_swatch const bg_color) & noexcept { m_bg_color = bg_color; }

	void title(str const new_title) & { m_handle.setTitle(new_title.data()); }

	/// @brief Attempts to set the window's icon
	/// @param icon_path The file path to the window's new icon
	void icon(str icon_path) &;

	void position(sf::Vector2i position) & { m_handle.setPosition(position); }

	void size(sf::Vector2u size) & { m_handle.setSize(size); }

	/// @brief Attempts to gain the window focus
	void focus() & { m_handle.requestFocus(); }

	void visibile(const bool is_visibile) & { m_handle.setVisible(is_visibile); }

	/// @brief Updates the cursor's visibility if possible
	//  (when: stage::change_cursor(window::cursor::cursor_type) is called after a
	//  prior call to window::change_cursor(std::string_view),
	//  stage::change_cursor(window::cursor::cursor) is called,
	//  or when neither are called)
	/// @param is_visibile Whether the cursor will be visibile
	void cursor_visible(const bool is_visibile) &
	{
		if (!m_custom_cursor) { m_handle.setMouseCursorVisible(m_cursor_visible = is_visibile); }
	}

	void grab_cursor(const bool grab_cursor) &
	{
		m_handle.setMouseCursorGrabbed(m_grabbed_cursor = grab_cursor);
	}

	/// @brief Registers the given callback to be called when the window is about to be closed
	//  @param on_close The callback to be called
	void on_close(callback on_close) & { m_on_close = std::move(on_close); };

	/// @brief Displays a prompt when the window is about to be
	/// closed asking the user if they want to exit the application.
	//  This will determine whether any registered callbacks are, well called
	void show_exit_prompt(const bool show_exit_prompt) & noexcept
	{
		m_show_exit_prompt = show_exit_prompt;
	}

	[[nodiscard]] bool is_open() & { return m_handle.isOpen(); }

	[[nodiscard]] bool poll(sf::Event& event) & { return m_handle.pollEvent(event); }

	/// @brief Attempts to draw the cursor set via
	/// window::change_cursor(std::string_view) if any
	/// @param x The x coordinate to draw the the cursor at
	/// @param y The y coordinate to draw the the cursor at
	void draw_cursor(const f32 x, const f32 y)
	{
		if (m_custom_cursor)
		{
			m_custom_cursor->img->setPosition(x, y);
			m_handle.draw(*(m_custom_cursor->img));
		}
	}

	void display() & { m_handle.display(); }

	void clear() & { m_handle.clear(colors::to_color(m_bg_color)); }

	/// @brief Attempts to close the window and call any registered callbacks
	void close() &;

	/// @brief Attempts to draw any instance of sf::Drawable, sf::VertexArray, sf::VertexBuffer,
	/// sf::Vertex*
	/// @param drawable The object to be drawn
	/// @param args Any additional context needed to render the drawable
	/// @see https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1RenderWindow.php
	template <typename T,
			  typename... Ts,
			  bool is_drawable = (std::is_base_of_v<sf::Drawable, utils::types::remove_cvr_t<T>> |
								  std::is_same_v<utils::types::remove_cvr_t<T>, sf::VertexArray> |
								  std::is_same_v<utils::types::remove_cvr_t<T>, sf::VertexBuffer> |
								  std::is_same_v<utils::types::remove_cvr_t<T>, sf::Vertex*>)>
	void draw(T&& drawable, Ts&&... args)
	{
		static_assert(is_drawable,
					  "Type is not an instance of: sf::Drawable | sf::VertexArray | "
					  "sf::VertexBuffer | sf::Vertex*");
		m_handle.draw(std::forward<T>(drawable), std::forward<Ts>(args)...);
	}

	/// @brief Attempts to change the window's cursor using:
	//  @param method A file path to an image (specified as a std::string_view | "string literal")
	/// @brief or
	//  @param method One of window::cursor::cursor_type
	template <typename T,
			  const bool is_valid_method = (std::is_same_v<T, str> |
											std::is_same_v<T, const char*> |
											std::is_same_v<T, cursor::cursor_type>)>
	void change_cursor(T method)
	{
		static_assert(is_valid_method,
					  "Cursor can only be loaded from an image or the operating system");

		if constexpr (std::is_same_v<T, str>)
		{
			auto cursor_sprite = cursor::load_from_image(method);

			if (!cursor_sprite) { return; }
			if (m_window_cursor) { m_window_cursor->reset(nullptr); }
			m_custom_cursor = std::move(*cursor_sprite);
			m_handle.setMouseCursorVisible(m_cursor_visible = false);
		}
		else if constexpr (std::is_same_v<T, const char*>)
		{
			auto cursor_sprite = cursor::load_from_image(str(method));

			if (!cursor_sprite) { return; }
			if (m_window_cursor) { m_window_cursor->reset(nullptr); }
			m_custom_cursor = std::move(*cursor_sprite);
			m_handle.setMouseCursorVisible(m_cursor_visible = false);
		}
		else if constexpr (std::is_same_v<T, cursor::cursor_type>)
		{
			if (m_custom_cursor)
			{
				m_custom_cursor.reset();
				cursor_visible(true);
			}

			if (!m_window_cursor) { m_window_cursor = std::make_unique<sf::Cursor>(); }
			cursor::load_from_system(method, *m_window_cursor, m_handle);
		}
	}

  private:
	bool								 m_show_exit_prompt {};
	bool								 m_cursor_visible {true};
	bool								 m_grabbed_cursor {};
	titlebar_style						 m_style {titlebar_style::normal};
	str									 m_title {};
	colors::color_swatch				 m_bg_color {};
	std::optional<cursor::cursor_sprite> m_custom_cursor {};
	std::optional<cursor::cursor>		 m_window_cursor {};
	std::optional<callback>				 m_on_close {};
	sf::RenderWindow					 m_handle {};
};

} // namespace aria::stage
