#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "TileMap.h"
#include "Game.h"
#include "KeyboardHandler.h"
#include "Button.h"
FILE *stream;

const int frame_per_cell[51] = { 0, 48, 43, 38, 33, 28, 23, 18, 13, 8, 6,
								5, 5, 5, 4, 4, 4, 3, 3, 3, 2,
								2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
								1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
								1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

sf::Font font, debug_font;

void set(sf::Text& text, double x, double y) {
	text.setPosition(x, y);
	text.setFont(font);
	text.setCharacterSize(FONT_SIZE);
}

std::string to_string(const void* address) {
	std::ostringstream os;
	os << (void const *)address;
	std::string name = os.str();
	return name;
}

class Main {
public:
	Main() : window(sf::VideoMode(980, 660), "Tetris"), mouseHandler(window){
		// pre-computation
//		freopen_s(&stream, "C:/Users/User/source/repos/Tetris/Tetris/log.txt", "w", stdout);
		
	}
	~Main() {};
	int main(){

		/* Items to be load on screen */
		font.loadFromFile("C:/Users/User/source/repos/Project1/Project1/Debug/arial.ttf");
		debug_font.loadFromFile("C:/Users/User/source/repos/Project1/Project1/Debug/MinecraftRegular-Bmg3.otf");

		sf::RectangleShape shadow(sf::Vector2f(WIDTH * TILESIZE, RHEIGHT * TILESIZE));
		shadow.setFillColor(sf::Color(30, 30, 30, 200));

		sf::Text highestScore, highestScoreInt, score, scoreInt, level, levelInt, clearedLines, clearedLinesInt, debug;
		std::string debug_message;
		highestScore.setString("Highest score");
		score.setString("Score");
		level.setString("Level");
		clearedLines.setString("Cleared Lines");
		set(debug, 5, 5);
		debug.setFont(debug_font);
		set(highestScore, 345, 60);
		set(highestScoreInt, 345, 120);
		set(score, 345, 180);
		set(scoreInt, 345, 240);
		set(level, 345, 300);
		set(levelInt, 345, 360);
		set(clearedLines, 345, 420);
		set(clearedLinesInt, 345, 480);

		sf::Texture inactive, normal, clicked, hovered;
		normal.loadFromFile("gem.png");
		clicked.loadFromFile("cancel.png");
		hovered.loadFromFile("gem.png");
		inactive.loadFromFile("inactivated_gem.png");
		std::function<void(Button*, Main*)> f = (std::function<void(Button*, Main*)>) [](Button* button, Main* main) {button->setPosition(sf::Vector2f(std::rand() % 470, std::rand() % 630)); main->game.setScore(main->game.getScore() + 10000); };
		Button button1(&inactive, &normal, &clicked, &hovered, "Button Test", sf::Vector2f(200, 200), mouseHandler, *this, f);
		Button button2(&inactive, &normal, &clicked, &hovered, "Button Test", sf::Vector2f(200, 230), mouseHandler, *this, f);
		while (window.isOpen())
		{
			from = timer.getElapsedTime();
			// handle events
			sf::Event event;
			while (window.pollEvent(event))
			{

				if (event.type == sf::Event::Resized) {
					int height = event.size.height;
					int width = event.size.width;
					// Not very important?
				}
				if (event.type == sf::Event::Closed) {
					//				saveState();
					window.close();
				}
			}

			paused |= game.lose();

			mouseHandler.update(buttons, 1);

			if (game.lose()) {
				keyboardHandler.update(keys, 1);
			}
			else if (paused) {
				keyboardHandler.update(keys, 2);
			}
			else {
				keyboardHandler.update(keys, keyCount);
			}

			if (keyboardHandler.isClicked(sf::Keyboard::Escape)) {
				if (!paused) {
					keyboardHandler.pause();
					paused = !paused;
				}
				else {
					keyboardHandler.resume();
					paused = !paused;
				}
				continue;
			}

			if (keyboardHandler.isClicked(sf::Keyboard::R)) {
				keyboardHandler.reset();
				game.restart();
				paused = false;
				continue;
			}

			if (!paused) {
				if (keyboardHandler.isClicked(sf::Keyboard::Left) || keyboardHandler.isPeriodPressed(sf::Keyboard::Left, keyboardHandler.getAutoRepeatDelay(), keyboardHandler.getAutoRepeatSpeed())) {
					game.moveLeft();
				}

				if (keyboardHandler.isClicked(sf::Keyboard::Right) || keyboardHandler.isPeriodPressed(sf::Keyboard::Right, keyboardHandler.getAutoRepeatDelay(), keyboardHandler.getAutoRepeatSpeed())) {
					game.moveRight();
				}

				if (keyboardHandler.isClicked(sf::Keyboard::Up)) {
					game.rotateClockwise();
				}

				if (keyboardHandler.isClicked(sf::Keyboard::Z)) {
					game.rotateAnticlockwise();
				}

				if (keyboardHandler.isClicked(sf::Keyboard::Down) || keyboardHandler.isPeriodPressed(sf::Keyboard::Down, DOWN_SPEED, DOWN_SPEED)) {
					game.softDrop(1);
				}
				else {
					if (keyboardHandler.isPeriodReleased(sf::Keyboard::Down, SPF * (float)frame_per_cell[game.getLevel()], SPF * (float)frame_per_cell[game.getLevel()])) {
						game.softDrop(0);
					}
				}

				if (keyboardHandler.isClicked(sf::Keyboard::Space)) {
					game.hardDrop();
				}

				if (keyboardHandler.isClicked(sf::Keyboard::H)) {
					game.hold();
				}
			}

			// consider rename this thing? name not match
			main_field.load("tiles.png", sf::Vector2u(TILESIZE, TILESIZE), game.getBoard()->getBoard(), WIDTH, RHEIGHT); // + 2 * WIDTH
			// game.getBoard()->print();
			// std::cout << std::endl;
			window.clear();
			window.draw(main_field);
			if (paused) {
				window.draw(shadow);
			}
			to = timer.getElapsedTime();

			highestScoreInt.setString(std::to_string(game.getHighestScore()));
			scoreInt.setString(std::to_string(game.getScore()));
			levelInt.setString(std::to_string(game.getLevel()));
			clearedLinesInt.setString(std::to_string(game.getClearedLines()));
			debug_message = "CPS: " + std::to_string(1 / (to - from).asSeconds()) + "\n";

			/*		sf::RectangleShape blank(sf::Vector2f(WIDTH * TILESIZE, RHEIGHT * TILESIZE));
					sf::Texture bl;
					bl.loadFromFile("blank.png");
					blank.setTexture(&bl);
					window.draw(blank); */
			button1.checkClick();
			button2.checkClick();
			debug_message += "Button 1 status: " + button1.getStatus() + "\n";
			window.draw(button1);
			debug_message += "Button 2 status: " + button2.getStatus() + "\n";
			window.draw(button2);
			window.draw(score);
			window.draw(scoreInt);
			window.draw(highestScore);
			window.draw(highestScoreInt);
			window.draw(level);
			window.draw(levelInt);
			window.draw(clearedLines);
			window.draw(clearedLinesInt);
			debug.setString(debug_message);
			window.draw(debug);
			window.display();
		}

		return 0;
	}

	// create the window
	sf::RenderWindow window;

	/* Background computation */
	TileMap main_field, hold_field, next_field, later_field;
	KeyboardHandler keyboardHandler;
	MouseHandler mouseHandler;
	Game game;

	const sf::Keyboard::Key keys[10] = { sf::Keyboard::R, sf::Keyboard::Escape, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::H, sf::Keyboard::Z, sf::Keyboard::C, sf::Keyboard::Space };
	const int keyCount = 10;

	const sf::Mouse::Button buttons[1] = { sf::Mouse::Button::Left };
	const int buttonCount = 1;

	bool paused = false;
	sf::Clock timer;
	sf::Time from, to;
};

void onExit() {
	
}

int32_t main() {
	Main main;
	main.main();
	atexit(onExit);
}
