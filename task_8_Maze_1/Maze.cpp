#include <iostream>
#include <algorithm>

#include "Maze.h"
#include "MCell.h"

	// То что помечено комментариями на английском,
	// скорее дублирование кода

/*
	Загромажденный код, где много проверок, чтобы не сломать [has\make\remove]Connection
	Единственное интересное в нем - использование битовых масок для взятия символа
*/

char BITMASK_CHARS[] = {
	'0', // 0b0000 0
	'0', // 0b0001 bottom
	'0', // 0b0010 right
	218, // 0b0011 ┌
	'0', // 0b0100 top
	179, // 0b0101 │
	192, // 0b0110 └
	195, // 0b0111 ├
	'0', // 0b1000 left
	191, // 0b1001 ┐
	196, // 0b1010 ─
	194, // 0b1011 ┬
	217, // 0b1100 ┘
	180, // 0b1101 ┤
	193, // 0b1110 ┴
	197, // 0b1111 ┼
};

Maze::Maze(int n, int m) : width(n), height(m)
{
	this->m_field = new MCell[n * m];
}

Maze::~Maze()
{
	delete[] this->m_field;
}

const MCell& Maze::cell(int i, int j) const
{
	return this->m_field[i * width + j];
}

bool Maze::hasConnection(int i1, int j1, int i2, int j2)
{
	if (!(i2 - i1 ^ j2 - j1)) return false; // just for check - not diagonal

	bool right = (i2 - i1) == 1; // check right
	bool bottom = (j2 - j1) == 1; // check bottom

	MCell* c1 = (MCell*)&cell(i1, j1); // left top cell(min_i, min_j)

	return
		(c1->right() * right) ||
		(c1->down()  * bottom);
}

bool Maze::makeConnection(int i1, int j1, int i2, int j2)
{
	if (!(i2 - i1 ^ j2 - j1)) return false; // just for check - not diagonal

	bool right = (i2 - i1) == 1; // check right
	bool bottom = (j2 - j1) == 1; // check bottom

	MCell* c1 = (MCell*)&cell(i1, j1); // left top cell(min_i, min_j)

	return
		(c1->m_right = right) ||
		(c1->m_down  = bottom);
}

bool Maze::removeConnection(int i1, int j1, int i2, int j2)
{
	if (!(i2 - i1 ^ j2 - j1)) return false; // just for check - not diagonal

	bool right = (i2 - i1) == 1; // check right
	bool bottom = (j2 - j1) == 1; // check bottom

	MCell* c1 = (MCell*)&cell(i1, j1); // left top cell(min_i, min_j)

	if (right) return !(c1->m_right = false);
	if (bottom) return !(c1->m_down  = false);

	return false;
}

void Maze::buildSteps()
{
	int x = 0, y = 0;
	bool axis_flag = true; // Можно поменять начало: true - по x, false - по y

	while(x < width && y < height)
	{
		makeConnection(x, y, x + axis_flag, y + !axis_flag);

		x +=  axis_flag,
		y += !axis_flag;

		axis_flag = !axis_flag;
	}
}

void Maze::printMaze()
{
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			int lb = i > 0 && hasConnection(i - 1, j, i, j) ? 8 : 0, // left   flag-bit
				tb = j > 0 && hasConnection(i, j - 1, i, j) ? 4 : 0, // top    flag-bit
				rb = hasConnection(i, j, i + 1, j) ? 2 : 0, // right  flag-bit
				bb = hasConnection(i, j, i, j + 1) ? 1 : 0; // bottom flag-bit

			int bitmask = lb | tb | rb | bb; // bitmask
			char c = BITMASK_CHARS[bitmask];

			std::cout << char(c);

		}
		std::cout << std::endl;
	}

}
