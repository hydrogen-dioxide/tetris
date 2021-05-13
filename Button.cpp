#include "Button.h"

// https://en.sfml-dev.org/forums/index.php?topic=5950.0, modified (too old)

Button::Button(sf::Texture* inactive, sf::Texture* normal, sf::Texture* clicked, sf::Texture* hovered, std::string words, sf::Vector2f location, MouseHandler& mouseHandler, Main& main, std::function<void(Button*, Main*)>& f) : mouseHandler(mouseHandler), m_onClick(f) {
	this->inactive.setTexture(*inactive);
	this->normal.setTexture(*normal);
	this->hovered.setTexture(*hovered);
	this->clicked.setTexture(*clicked);

	this->inactive.setPosition(location);
	this->normal.setPosition(location);
	this->hovered.setPosition(location);
	this->clicked.setPosition(location);

	this->currentSpr = &this->normal;
	current = BUTTON_MODE::NORMAL;
	this->main = &main;
	String.setString(words);
	String.setPosition(location.x + 3, location.y + 3);
}

/* To do: find whether possible to use image path to store it in the button itself.
Button::Button(sf::Texture* inactive, sf::Texture* normal, sf::Texture* clicked, sf::Texture* hovered, std::string words, sf::Vector2f location, MouseHandler mouseHandler) : mouseHandler(mouseHandler) {
	this->inactive.setTexture(*inactive);
	this->normal.setTexture(*normal);
	this->hovered.setTexture(*hovered);
	this->clicked.setTexture(*clicked);

	this->inactive.setPosition(location);
	this->normal.setPosition(location);
	this->hovered.setPosition(location);
	this->clicked.setPosition(location);

	this->currentSpr = &this->normal;
	current = BUTTON_MODE::NORMAL;
	String.setString(words);
	String.setPosition(location.x + 3, location.y + 3);
}
*/

void Button::setState(BUTTON_MODE buttonMode = BUTTON_MODE::NONE) {
	if (buttonMode != BUTTON_MODE::NONE) current = buttonMode;
	if (current == BUTTON_MODE::INACTIVE) currentSpr = &inactive;
	if (current == BUTTON_MODE::NORMAL) currentSpr = &normal;
	if (current == BUTTON_MODE::HOVERED) currentSpr = &hovered;
	if (current == BUTTON_MODE::CLICKED) currentSpr = &clicked;
}

void Button::checkClick() {
	sf::Vector2i mousePos = mouseHandler.getPosition();
	if (current == BUTTON_MODE::INACTIVE) return;
	current = BUTTON_MODE::NORMAL;
	if (mousePos.x > currentSpr->getPosition().x && mousePos.x < (currentSpr->getPosition().x + currentSpr->getTexture()->getSize().x)) {
		if (mousePos.y > currentSpr->getPosition().y && mousePos.y < (currentSpr->getPosition().y + currentSpr->getTexture()->getSize().y)) {
			if (mouseHandler.isPressed(sf::Mouse::Button::Left)) {
				current = BUTTON_MODE::CLICKED;
			} else {
				current = BUTTON_MODE::HOVERED;
			}
		}
	}
	setState();
	if (current == BUTTON_MODE::CLICKED && mouseHandler.isClicked(sf::Mouse::Left)) onClick();
}

void Button::setPosition(sf::Vector2f location) {
	this->inactive.setPosition(location);
	this->normal.setPosition(location);
	this->hovered.setPosition(location);
	this->clicked.setPosition(location);
}

void Button::setText(std::string words) {
	String.setString(words);
}

BUTTON_MODE Button::getVar() {
	return current;
}

std::string Button::getStatus() {
	if (current == BUTTON_MODE::INACTIVE) return "inactive";
	if (current == BUTTON_MODE::NORMAL) return "normal";
	if (current == BUTTON_MODE::HOVERED) return "hovered";
	if (current == BUTTON_MODE::CLICKED) return "clicked";
	return "none";
}

sf::Sprite* Button::getSprite() {
	return currentSpr;
}

sf::Text* Button::getText() {
	return &String;
}

void Button::setActivity(bool active) {
	if (active == true) {
		setState(BUTTON_MODE::NORMAL);
	} else {
		setState(BUTTON_MODE::INACTIVE);
	}
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	// draw the vertex array
	target.draw(*currentSpr, states);
	target.draw(String, states);
}

std::function<void(Button*, Main*)> Button::onClick_default = (const std::function<void(Button*, Main*)>) [](Button* button, Main* main) { return; };