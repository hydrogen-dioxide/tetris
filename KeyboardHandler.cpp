#include <SFML/Graphics.hpp>
#include "KeyboardHandler.h"

#include <iostream>
using namespace std;

KeyboardHandler::KeyboardHandler() {
	for (int i = 0; i < key_count; i++) {
		m_last_click[i] = m_clock.getElapsedTime();
	}
}

bool KeyboardHandler::isPressed(sf::Keyboard::Key key) {
	return m_holding[key];
}

bool KeyboardHandler::isClicked(sf::Keyboard::Key key) {
	return m_clicked[key];
}

bool KeyboardHandler::isReleased(sf::Keyboard::Key key) {
	return m_released[key];
}

bool KeyboardHandler::isPeriodReleased(sf::Keyboard::Key key, sf::Time t1, sf::Time t2) {
	if (!m_holding[key] && m_clock.getElapsedTime() - m_last_click[key] >= t1) {
		m_last_click[key] += t2;
		return true;
	}
	return false;
}

bool KeyboardHandler::isPeriodPressed(sf::Keyboard::Key key, sf::Time t1, sf::Time t2) {
	if (m_holding[key] && m_clock.getElapsedTime() - m_last_click[key] >= t1) {
		m_last_click[key] += t2;
		return true;
	}
	return false;
}

void KeyboardHandler::update(const sf::Keyboard::Key* keys, const int keyCount) {
	for (int i = 0; i < keyCount; i++) {
		m_released[keys[i]] = false;
		if (sf::Keyboard::isKeyPressed(keys[i])) {
			if (!m_holding[keys[i]]) {
				m_last_click[keys[i]] = m_clock.getElapsedTime();
				m_holding[keys[i]] = true;
				m_clicked[keys[i]] = true;
			}
			else {
				m_clicked[keys[i]] = false;
			}
		}
		else {
			if (m_holding[keys[i]]) {
				m_released[keys[i]] = true;
			}
			m_holding[keys[i]] = false;
			m_clicked[keys[i]] = false;
		}
	}
}

void KeyboardHandler::pause() {
	m_pause_time = m_clock.getElapsedTime();
}

void KeyboardHandler::resume() {
	sf::Time pause_period = m_clock.getElapsedTime() - m_pause_time;
	for (int key = 0; key < key_count; key++) {
		m_last_click[key] += pause_period;
	}
}

void KeyboardHandler::reset() {
	m_clock.restart();
	for (int i = 0; i < key_count; i++) {
		m_last_click[i] = m_clock.getElapsedTime();
	}
	m_pause_time = sf::Time::Zero;
}

sf::Time KeyboardHandler::getAutoRepeatDelay() {
	return m_auto_repeat_delay;
}

sf::Time KeyboardHandler::getAutoRepeatSpeed() {
	return m_auto_repeat_speed;
}

void KeyboardHandler::setAutoRepeatDelay(sf::Time autoRepeatDelay) {
	m_auto_repeat_delay = autoRepeatDelay;
};

void KeyboardHandler::setAutoRepeatSpeed(sf::Time autoRepeatSpeed) {
	m_auto_repeat_speed = autoRepeatSpeed;
};