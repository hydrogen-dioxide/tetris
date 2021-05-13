#include "Game.h"
#include "TileMap.h"
#include "Tetromino.h"
#include "Board.h"
#include <iostream>

void Game::newTetromino(Tetromino tetromino = NONE) {
//	std::cout << "New Tetromino" << std::endl;
	m_is_holded = false;
	Game::clearLines();
	if (tetromino == NONE) {
		m_tetromino = Tetromino();
	} else {
		m_tetromino = tetromino;
	}
	m_board.print();
	bool lose = !m_board.tryPlace(m_tetromino);
	if (lose) {
		Game::gameOver();
		return;
	}
//	std::cout << "Placing block..." << std::endl;
	predict();
	m_board.place(m_tetromino);

	if (m_tetromino.getId() == 0) {
		softDrop(0);
	} else {
		softDrop(0);
		softDrop(0);
	}
	return;
}

void Game::moveLeft() {
	m_board.remove(m_tetromino);

	bool failed = !m_board.tryPlace(m_tetromino.addX(-1));

	if (!failed) {
		m_tetromino = m_tetromino.addX(-1);
	}

//	std::cout << "Move Left" << std::endl;
	predict();
	m_board.place(m_tetromino);
	return;
}

void Game::moveRight() {
	m_board.remove(m_tetromino);

	bool failed = !m_board.tryPlace(m_tetromino.addX(1));

	if (!failed) {
		m_tetromino = m_tetromino.addX(1);
	}

//	std::cout << "Move Right" << std::endl;
	predict();
	m_board.place(m_tetromino);
	return;
}

// https://tetris.wiki/Super_Rotation_System Wall kick

static int dx[7][4][2][5] = {
	{
		{
			{0, -2, 1, -2, 1},
			{0, -1, 2, -1, 2}
		},
		{
			{0, -1, 2, -1, 2},
			{0, 2, -1, 2, -1}
		},
		{
			{0, 2, -1, 2, -1},
			{0, 1, -2, 1, -2}
		},
		{
			{0, 1, -2, 1, -2},
			{0, -2, 1, -2, 1}
		}
	},
	{
		{
			{0, -1, -1, 0, -1},
			{0, 1, 1, 0, 1}
		},
		{
			{0, 1, 1, 0, 1},
			{0, 1, 1, 0, 1}
		},
		{
			{0, 1, 1, 0, 1},
			{0, -1, -1, 0, -1}
		},
		{
			{0, -1, -1, 0, -1},
			{0, -1, -1, 0, -1}
		}
	},
	{
		{
			{0, -1, -1, 0, -1},
			{0, 1, 1, 0, 1}
		},
		{
			{0, 1, 1, 0, 1},
			{0, 1, 1, 0, 1}
		},
		{
			{0, 1, 1, 0, 1},
			{0, -1, -1, 0, -1}
		},
		{
			{0, -1, -1, 0, -1},
			{0, -1, -1, 0, -1}
		}
	},
	{
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0}
		}
	},
	{
		{
			{0, -1, -1, 0, -1},
			{0, 1, 1, 0, 1}
		},
		{
			{0, 1, 1, 0, 1},
			{0, 1, 1, 0, 1}
		},
		{
			{0, 1, 1, 0, 1},
			{0, -1, -1, 0, -1}
		},
		{
			{0, -1, -1, 0, -1},
			{0, -1, -1, 0, -1}
		}
	},
	{
		{
			{0, -1, -1, 0, -1},
			{0, 1, 1, 0, 1}
		},
		{
			{0, 1, 1, 0, 1},
			{0, 1, 1, 0, 1}
		},
		{
			{0, 1, 1, 0, 1},
			{0, -1, -1, 0, -1}
		},
		{
			{0, -1, -1, 0, -1},
			{0, -1, -1, 0, -1}
		}
	},
	{
		{
			{0, -1, -1, 0, -1},
			{0, 1, 1, 0, 1}
		},
		{
			{0, 1, 1, 0, 1},
			{0, 1, 1, 0, 1}
		},
		{
			{0, 1, 1, 0, 1},
			{0, -1, -1, 0, -1}
		},
		{
			{0, -1, -1, 0, -1},
			{0, -1, -1, 0, -1}
		}
	}
};
static int dy[7][4][2][5] = {
	{
		{
			{0, 0, 0, -1, 2},
			{0, 0, 0, 2, -1}
		},
		{
			{0, 0, 0, 2, -1},
			{0, 0, 0, 1, -2}
		},
		{
			{0, 0, 0, 1, -2},
			{0, 0, 0, -2, 1}
		},
		{
			{0, 0, 0, -2, 1},
			{0, 0, 0, -1, 2}
		},
	},
	{
		{
			{0, 0, 1, -2, -2},
			{0, 0, 1, -2, -2}
		},
		{
			{0, 0, -1, 2, 2},
			{0, 0, -1, 2, 2}
		},
		{
			{0, 0, 1, -2, -2},
			{0, 0, 1, -2, -2}
		},
		{
			{0, 0, -1, 2, 2},
			{0, 0, -1, 2, 2}
		},
	},
	{
		{
			{0, 0, 1, -2, -2},
			{0, 0, 1, -2, -2}
		},
		{
			{0, 0, -1, 2, 2},
			{0, 0, -1, 2, 2}
		},
		{
			{0, 0, 1, -2, -2},
			{0, 0, 1, -2, -2}
		},
		{
			{0, 0, -1, 2, 2},
			{0, 0, -1, 2, 2}
		},
	},
	{
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0}
		}
	},
	{
		{
			{0, 0, 1, -2, -2},
			{0, 0, 1, -2, -2}
		},
		{
			{0, 0, -1, 2, 2},
			{0, 0, -1, 2, 2}
		},
		{
			{0, 0, 1, -2, -2},
			{0, 0, 1, -2, -2}
		},
		{
			{0, 0, -1, 2, 2},
			{0, 0, -1, 2, 2}
		},
	},
	{
		{
			{0, 0, 1, -2, -2},
			{0, 0, 1, -2, -2}
		},
		{
			{0, 0, -1, 2, 2},
			{0, 0, -1, 2, 2}
		},
		{
			{0, 0, 1, -2, -2},
			{0, 0, 1, -2, -2}
		},
		{
			{0, 0, -1, 2, 2},
			{0, 0, -1, 2, 2}
		},
	},
	{
		{
			{0, 0, 1, -2, -2},
			{0, 0, 1, -2, -2}
		},
		{
			{0, 0, -1, 2, 2},
			{0, 0, -1, 2, 2}
		},
		{
			{0, 0, 1, -2, -2},
			{0, 0, 1, -2, -2}
		},
		{
			{0, 0, -1, 2, 2},
			{0, 0, -1, 2, 2}
		},
	}
};

void Game::rotateClockwise() {
	m_board.remove(m_tetromino);

	for (int test = 0; test < 5; test++) {
		Tetromino attempt = Tetromino(m_tetromino.getX() + dx[m_tetromino.getId()][m_tetromino.getRotation()][0][test], m_tetromino.getY() + dy[m_tetromino.getId()][m_tetromino.getRotation()][0][test], m_tetromino.getId(), (m_tetromino.getRotation() + 1) % 4);
		if (m_board.tryPlace(attempt)) {
			m_tetromino = attempt;
			break;
		}
	}

//	std::cout << "Rotate Clockwise" << std::endl;
	predict();
	m_board.place(m_tetromino);
	return;
}

void Game::rotateAnticlockwise() {
	m_board.remove(m_tetromino);

	bool failed = !m_board.tryPlace(m_tetromino.addRotation(-1));

	if (!failed) {
		m_tetromino = m_tetromino.addRotation(-1);
	}

//	std::cout << "Rotate Anitclockwise" << std::endl;
	predict();
	m_board.place(m_tetromino);
	return;
}

bool Game::softDrop(int scorePerCell, bool strict) {
	if (m_is_losed) return false;
	m_board.remove(m_tetromino);

	bool failed = !m_board.tryPlace(m_tetromino.addY(1));

	if (!failed) {
		m_tetromino = m_tetromino.addY(1);
	}

//	std::cout << "Soft Drop" << std::endl;
	m_board.place(m_tetromino);
	
	if (failed) {
		if (strict) {
			Game::newTetromino();
		}
		return false;
	}

	m_score += scorePerCell * m_level;
	m_highest_score = std::max(m_highest_score, m_score);
	return true;
}

void Game::hardDrop() {

	while (Game::softDrop(2));
}

void Game::predict() {
	m_board.print();
	if (predicted.getId() != -1) {
		m_board.remove(predicted);
	}
	Tetromino original = m_tetromino;
	while (Game::softDrop(0, false));
	predicted = m_tetromino;
	m_board.remove(m_tetromino);
	predicted.setColor(predicted.getColor() + 8);
	m_board.place(predicted);
	m_tetromino = original;
	m_board.place(m_tetromino);
}

void Game::hold() {
	if (!m_hold_mode || m_is_holded) return;
	if (m_is_holding) {
		m_board.remove(m_tetromino);
		m_hold_board.remove(m_hold_tetromino);
		std::swap(m_hold_tetromino, m_tetromino);
		m_tetromino.toMainBoard();
		newTetromino(m_tetromino);
		m_hold_tetromino.toShowCase();
		m_is_holded = true;
		m_is_holding = true;
	} else {
		m_hold_tetromino = m_tetromino;
		m_hold_tetromino.toShowCase();
		m_hold_board.clear();
		m_hold_board.place(m_hold_tetromino);
		m_board.remove(m_tetromino);
		newTetromino();
		m_is_holded = true;
		m_is_holding = true;
	}
	predict();
}

void Game::clearLines() {
	int no_of_cleared_lines = m_board.clearLines();
	m_no_of_cleared_lines += no_of_cleared_lines;
	m_score += m_level * no_of_cleared_lines * 100;
	m_highest_score = std::max(m_highest_score, m_score);
	while (m_no_of_cleared_lines >= m_level * 10) m_level++;
}

bool Game::lose() {
	return m_is_losed;
}

void Game::restart() {
//	std::cout << "Game restarted." << std::endl;
	m_is_losed = 0;
	m_level = 1;
	m_score = 0;
	m_no_of_cleared_lines = 0;
	m_board.reset();
	m_hold_board.reset();
	m_is_holded = false;
	m_is_holding = false;
	Game::newTetromino();
}

void Game::gameOver() {
	m_is_losed = true;
}
