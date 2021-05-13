#pragma once

#include <SFML/Graphics.hpp>

class KeyboardHandler {
public:
	KeyboardHandler();
	bool isPressed(sf::Keyboard::Key key); // check state of the key
	bool isClicked(sf::Keyboard::Key key); // check if just recently pressed
	bool isReleased(sf::Keyboard::Key key); // check if just recently released
	bool isPeriodReleased(sf::Keyboard::Key key, sf::Time t1, sf::Time t2); // return true if key released for more than t1; add t2 to the last_click[key]
	bool isPeriodPressed(sf::Keyboard::Key key, sf::Time t1, sf::Time t2); // return true if key pressed for more than t1; add t2 to the last_click[key]
	void update(const sf::Keyboard::Key* keys, const int keyCount);

	void pause();
	void resume();
	void reset();

	sf::Time getAutoRepeatSpeed();
	sf::Time getAutoRepeatDelay();
	void setAutoRepeatSpeed(sf::Time);
	void setAutoRepeatDelay(sf::Time);

private:

	sf::Clock m_clock;
	static const int key_count = 255;
	bool m_clicked[key_count] = {};
	bool m_holding[key_count] = {};
	bool m_released[key_count] = {};
	sf::Time m_last_click[key_count] = {};
	sf::Time m_pause_time = sf::Time::Zero;
	sf::Time m_auto_repeat_speed = sf::seconds(0.05f), m_auto_repeat_delay = sf::seconds(0.2f);
};