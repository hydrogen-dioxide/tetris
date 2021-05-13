#include <SFML/Graphics.hpp>
#include "MouseHandler.h"

#include <iostream>
using namespace std;

MouseHandler::MouseHandler(sf::Window& window) : m_window(window) {
	for (int i = 0; i < button_count; i++) {
		m_last_click[i] = m_clock.getElapsedTime();
	}
}

bool MouseHandler::isPressed(sf::Mouse::Button button) {
	return m_holding[button];
}

bool MouseHandler::isClicked(sf::Mouse::Button button) {
	return m_clicked[button];
}

bool MouseHandler::isReleased(sf::Mouse::Button button) {
	return m_released[button];
}

/*
bool MouseHandler::isPeriodReleased(sf::Keyboard::Key key, sf::Time t1, sf::Time t2) {
	if (!m_holding[key] && m_clock.getElapsedTime() - m_last_click[key] >= t1) {
		m_last_click[key] += t2;
		return true;
	}
	return false;
}

bool MouseHandler::isPeriodPressed(sf::Keyboard::Key key, sf::Time t1, sf::Time t2) {
	if (m_holding[key] && m_clock.getElapsedTime() - m_last_click[key] >= t1) {
		m_last_click[key] += t2;
		return true;
	}
	return false;
}
*/

void MouseHandler::update(const sf::Mouse::Button* buttons, const int buttonCount){
	for (int i = 0; i < buttonCount; i++) {
		m_released[buttons[i]] = false;
		if (sf::Mouse::isButtonPressed(buttons[i])) {
			if (!m_holding[buttons[i]]) {
				m_last_click[buttons[i]] = m_clock.getElapsedTime();
				m_holding[buttons[i]] = true;
				m_clicked[buttons[i]] = true;
			}
			else {
				m_clicked[buttons[i]] = false;
			}
		}
		else {
			if (m_holding[buttons[i]]) {
				m_released[buttons[i]] = true;
			}
			m_holding[buttons[i]] = false;
			m_clicked[buttons[i]] = false;
		}
	}
}

void MouseHandler::pause() {
	m_pause_time = m_clock.getElapsedTime();
}

void MouseHandler::resume() {
	sf::Time pause_period = m_clock.getElapsedTime() - m_pause_time;
	for (int button = 0; button < button_count; button++) {
		m_last_click[button] += pause_period;
	}
}

void MouseHandler::reset() {
	m_clock.restart();
	for (int i = 0; i < button_count; i++) {
		m_last_click[i] = m_clock.getElapsedTime();
	}
	m_pause_time = sf::Time::Zero;
}