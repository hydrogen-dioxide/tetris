#pragma once
#include <SFML/Graphics.hpp>

class MouseHandler {
public:
	MouseHandler(sf::Window& window);
	bool isPressed(sf::Mouse::Button button); // check state of the button
	bool isReleased(sf::Mouse::Button button); // check if the button is just recently released
	bool isClicked(sf::Mouse::Button button); // check if the button is just recently pressed
	void update(const sf::Mouse::Button* buttons, const int buttonCount);
	sf::Vector2i getPosition() { return sf::Mouse::getPosition(m_window); }
	void pause();
	void resume();
	void reset();

private:

	sf::Clock m_clock;
	sf::Window &m_window;
	static const int button_count = 20;
	bool m_clicked[button_count] = {};
	bool m_holding[button_count] = {};
	bool m_released[button_count] = {};
	sf::Time m_last_click[button_count] = {};
	sf::Time m_pause_time = sf::Time::Zero;
};