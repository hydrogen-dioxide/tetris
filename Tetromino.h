#pragma once

class Tetromino { // { I, J, L, O, S, T, Z,};

public:
	Tetromino();
	Tetromino(int x, int y, int id, int rotation) : m_x(x), m_y(y), m_id(id), m_rotation(rotation) { m_color = id; };
	friend void reset();
	
	void setX(int x) { m_x = x; };
	void setY(int y) { m_y = y; };
	void setId(int id) { m_id = id;  };
	void setColor(int color) { m_color = color; };
	void setRotation(int rotation) { m_rotation = rotation; };

	int getX() const { return m_x; };
	int getY() const { return m_y; };
	int getId() const { return m_id; };
	int getColor() { return m_color; };
	int getRotation() const { return m_rotation; };

	int get(int i, int j);

	friend bool operator== (const Tetromino& A, const Tetromino& B) {
		return A.m_x == B.m_x && A.m_y == B.m_y && A.m_id == B.m_id && A.m_rotation == B.m_rotation;
	}

	Tetromino addX(int);
	Tetromino addY(int);
	Tetromino addRotation(int);

	void toMainBoard();
	void toShowCase();

private:
	int m_x, m_y, m_id, m_color, m_rotation;
};

const Tetromino NONE{ -1, -1, -1, -1 };