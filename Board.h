#pragma once

#include "Definitions.h"
#include "Tetromino.h"
#include <string>
class Board {

public:
	Board() { Board::reset(); };
	Board(std::string tileset, int tileSize) : m_tileset(tileset), m_tileSize(tileSize) {};
	void reset();

	bool isSolid(int i, int j);

	bool tryPlace(Tetromino tetromino);
	void place(Tetromino tetromino);
	void remove(Tetromino tetromino);
	int clearLines();
	auto getBoard() { return m_board; }
	void print();
	void clear();

private:
	int m_board[RHEIGHT][WIDTH] = {};
	std::string m_tileset;
	int m_tileSize;
};