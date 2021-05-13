#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>
#include <functional>
#include <memory>
#include "MouseHandler.h"

enum class BUTTON_MODE {
	NONE,
	INACTIVE,
	NORMAL,
	HOVERED,
	CLICKED
};

class Main;

class Button : public sf::Drawable, public sf::Transformable{
public:
	Button(sf::Texture* inactive, sf::Texture* normal, sf::Texture* clicked, sf::Texture* hovered, std::string, sf::Vector2f location, MouseHandler& mouseHandler, Main & main, std::function<void(Button*, Main*)>& f = onClick_default);
	void checkClick();
	void setState(BUTTON_MODE buttonMode);
	void setText(std::string);
	BUTTON_MODE getVar();
	sf::Sprite* getSprite();
	sf::Text* getText();
	std::string getStatus();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setActivity(bool active);
	void setPosition(sf::Vector2f);
	void onClick() { m_onClick(this, main); };
private:
	sf::Sprite inactive;
	sf::Sprite normal;
	sf::Sprite clicked;
	sf::Sprite hovered;
	sf::Sprite* currentSpr;
	sf::Text String;
	BUTTON_MODE current;
	MouseHandler &mouseHandler;
	Main* main;
	std::function<void(Button*, Main*)> m_onClick;
	static std::function<void(Button*, Main*)> onClick_default;
};