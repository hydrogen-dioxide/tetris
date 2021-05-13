#pragma once
#include "TileMap.h"
#include "Tetromino.h"
#include "Board.h"
#include <chrono>
#include <random>

class Game {

public:
	Game() : m_board("tiles.png", TILESIZE), m_hold_board("small tiles.png", SMALL_TILESIZE), m_next_board("tiles.png", TILESIZE), m_later_board("tiles.png", TILESIZE) { restart(); }
	void newTetromino(Tetromino tetromino);
	
	void moveLeft();
	void moveRight();
	void rotateClockwise();
	void rotateAnticlockwise();
	bool softDrop(int scorePerCell, bool strict = true);
	void hardDrop();

	void predict();
	void hold();

	void clearLines();

	int getHighestScore() { return m_highest_score; } 
	void setHighestScore(int highest_score) { m_highest_score = highest_score; }
	int getScore() { return m_score; };
	void setScore(int score) { m_score = score; }
	int getLevel() { return m_level; };
	void setLevel(int level) { m_level = level; }
	int getClearedLines() { return m_no_of_cleared_lines; }
	void setClearedLines(int no_of_cleared_lines) { m_no_of_cleared_lines = no_of_cleared_lines; }

	bool getHoldMode() { return m_hold_mode; }
	void setHoldMode(bool hold_mode) { m_hold_mode = hold_mode; }
	Board* getBoard() { return &m_board; };

	void gameOver();
	void restart();
	bool lose();

private:

	Board m_board, m_hold_board, m_next_board, m_later_board;
	int m_highest_score = 0, m_score = 0, m_level = 1, m_no_of_cleared_lines = 0;
	Tetromino m_tetromino, m_hold_tetromino = NONE, predicted = NONE;
	bool m_is_losed = false, m_hold_mode = true, m_is_holding = false, m_is_holded = false;
	
};