#include "Tetromino.h"
#include <algorithm>
#include <random>
#include <chrono>

std::mt19937 rng((unsigned)std::chrono::steady_clock::now().time_since_epoch().count());

// { I, J, L, O, S, T, Z,};

bool tetrominos[7][4][16] = {
{
	{
	0, 0, 0, 0,
	1, 1, 1, 1,
	0, 0, 0, 0,
	0, 0, 0, 0,
	},
	{
	0, 0, 1, 0,
	0, 0, 1, 0,
	0, 0, 1, 0,
	0, 0, 1, 0,
	},
	{
	0, 0, 0, 0,
	0, 0, 0, 0,
	1, 1, 1, 1,
	0, 0, 0, 0,
	},
	{
	0, 1, 0, 0,
	0, 1, 0, 0,
	0, 1, 0, 0,
	0, 1, 0, 0,
	},
}, // I
{
	{
	1, 0, 0, 0,
	1, 1, 1, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	},
	{
	0, 1, 1, 0,
	0, 1, 0, 0,
	0, 1, 0, 0,
	0, 0, 0, 0,
	},
	{
	0, 0, 0, 0,
	1, 1, 1, 0,
	0, 0, 1, 0,
	0, 0, 0, 0,
	},
	{
	0, 1, 0, 0,
	0, 1, 0, 0,
	1, 1, 0, 0,
	0, 0, 0, 0,
	},
}, // J
{
	{
	0, 0, 1, 0,
	1, 1, 1, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	},
	{
	0, 1, 0, 0,
	0, 1, 0, 0,
	0, 1, 1, 0,
	0, 0, 0, 0,
	},
	{
	0, 0, 0, 0,
	1, 1, 1, 0,
	1, 0, 0, 0,
	0, 0, 0, 0,
	},
	{
	1, 1, 0, 0,
	0, 1, 0, 0,
	0, 1, 0, 0,
	0, 0, 0, 0,
	},
}, // L
{
	{
	0, 1, 1, 0,
	0, 1, 1, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	},
	{
	0, 1, 1, 0,
	0, 1, 1, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	},
	{
	0, 1, 1, 0,
	0, 1, 1, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	},
	{
	0, 1, 1, 0,
	0, 1, 1, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	},
}, // O
{
	{
	0, 1, 1, 0,
	1, 1, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	},
	{
	0, 1, 0, 0,
	0, 1, 1, 0,
	0, 0, 1, 0,
	0, 0, 0, 0,
	},
	{
	0, 0, 0, 0,
	0, 1, 1, 0,
	1, 1, 0, 0,
	0, 0, 0, 0,
	},
	{
	1, 0, 0, 0,
	1, 1, 0, 0,
	0, 1, 0, 0,
	0, 0, 0, 0,
	},
}, // S
{
	{
	0, 1, 0, 0,
	1, 1, 1, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	},
	{
	0, 1, 0, 0,
	0, 1, 1, 0,
	0, 1, 0, 0,
	0, 0, 0, 0,
	},
	{
	0, 0, 0, 0,
	1, 1, 1, 0,
	0, 1, 0, 0,
	0, 0, 0, 0,
	},
	{
	0, 1, 0, 0,
	1, 1, 0, 0,
	0, 1, 0, 0,
	0, 0, 0, 0,
	},
}, // T
{
	{
	1, 1, 0, 0,
	0, 1, 1, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	},
	{
	0, 0, 1, 0,
	0, 1, 1, 0,
	0, 1, 0, 0,
	0, 0, 0, 0,
	},
	{
	0, 0, 0, 0,
	1, 1, 0, 0,
	0, 1, 1, 0,
	0, 0, 0, 0,
	},
	{
	0, 1, 0, 0,
	1, 1, 0, 0,
	1, 0, 0, 0,
	0, 0, 0, 0,
	},
}, // Z
};

// Wall kick data

int order[7] = { 0, 1, 2, 3, 4, 5, 6 };
int idx = 0;

void shuffle() {
	for (int i = 0; i < 7; i++) {
		std::swap(order[i], order[i + rng() % (7 - i)]);
	}
}

Tetromino::Tetromino() {
	if (idx == 0) shuffle();
	this->m_x = 3;
	this->m_y = 0;
	this->m_id = order[idx];
	this->m_color = order[idx];
	this->m_rotation = 0;
	idx = (idx + 1) % 7;
	return;
}

int Tetromino::get(int i, int j) {
	return tetrominos[this->getId()][this->getRotation()][i * 4 + j];
}

Tetromino Tetromino::addX(int add) {
	Tetromino res = *this;
	res.m_x += add;
	return res;
}

Tetromino Tetromino::addY(int add) {
	Tetromino res = *this;
	res.m_y += add;
	return res;
}

Tetromino Tetromino::addRotation(int add) {
	Tetromino res = *this;
	res.m_rotation = (m_rotation + 4 + add) % 4;
	return res;
}

void reset() {
	idx = 0;
}

void Tetromino::toMainBoard() {
	m_x = 3, m_y = 0, m_rotation = 0;
}

void Tetromino::toShowCase() {
	m_x = 0, m_y = 0, m_rotation = 0;
}