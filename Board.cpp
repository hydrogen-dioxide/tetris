#include "Board.h"
#include <iostream>


void Board::reset() {
	for (int i = 0; i < RHEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			m_board[i][j] = 0;
		}
	}
}

inline bool inside(int i, int j) {
	return 0 <= i && i < WIDTH && 0 <= j && j < RHEIGHT;
}

inline bool Board::isSolid(int i, int j) {
	return !inside(i, j) || 1 <= m_board[j][i] && m_board[j][i] <= 7;
}

bool Board::tryPlace(Tetromino tetromino){
	if (tetromino == NONE) return false;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (tetromino.get(i, j)) {
				int x = tetromino.getX() + j, y = tetromino.getY() + i;
				if (isSolid(x, y)) return false;
			}
		}
	}

	return true;
}

void Board::place(Tetromino tetromino) {
//	std::cout << "Real placing block..." << std::endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (tetromino.get(i, j)) {
				int x = tetromino.getX() + j, y = tetromino.getY() + i;
				if (!isSolid(x, y)) {
					m_board[y][x] = tetromino.getColor() + 1;
				}
			}
		}
	}
}

void Board::remove(Tetromino tetromino) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (tetromino.get(i, j)) {
				int x = tetromino.getX() + j, y = tetromino.getY() + i;
				if (inside(x, y) && m_board[y][x] == tetromino.getColor() + 1) {
					m_board[y][x] = 0;
				}
			}
		}
	}
}

void Board::clear() {
	for (int i = 0; i < RHEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			m_board[i][j] = 0;
		}
	}
}

int Board::clearLines() {
	int no_of_cleared_lines = 0;
	bool full[RHEIGHT];
	for (int i = 0; i < RHEIGHT; i++) full[i] = true;
	for (int i = 0; i < RHEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			full[i] &= Board::m_board[i][j] != 0;
		}
	}

	int lineNumber = RHEIGHT - 1, realLineNumber = RHEIGHT - 1;
	while (lineNumber >= 0) {
		if (full[lineNumber]) {
			lineNumber--;
			no_of_cleared_lines++;
			continue;
		}

		for (int i = 0; i < WIDTH; i++) {
			Board::m_board[realLineNumber][i] = Board::m_board[lineNumber][i];
		}
		lineNumber--;
		realLineNumber--;
	}
	while (realLineNumber >= 0) {
		for (int i = 0; i < WIDTH; i++) {
			Board::m_board[realLineNumber][i] = 0;
		}
		realLineNumber--;
	}

	return no_of_cleared_lines;
}

void Board::print() {
/*
	for (int i = 0; i < RHEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			std::cout << '[' << m_board[i][j] << ']';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
*/
}