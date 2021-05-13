#pragma once

#define idx(x, y) ((x) + ((y) * (WIDTH)))
#define DOWN_SPEED (sf::seconds(0.05f))
#define FONT_SIZE 20
#define SPF (sf::seconds((float) 1 / 60.1))

#define WIDTH 10
#define HEIGHT 20
#define RHEIGHT 22
#define TILESIZE 30
#define SMALL_TILESIZE 20