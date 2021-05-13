#pragma once

#include <SFML/Graphics.hpp>

#include "Definitions.h"

class TileMap : public sf::Drawable, public sf::Transformable
{
public:

	bool load(const std::string& tileset, sf::Vector2u tileSize, int tiles[][WIDTH], unsigned int width, unsigned int height);
private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	
	sf::Texture m_tileset;
	unsigned int m_each_width, m_each_height;
};