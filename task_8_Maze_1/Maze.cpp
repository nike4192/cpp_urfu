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

int clamp(const int min, const int max, int value)
{
	return std::min(std::max(value, min), max);
}

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

void Maze::idx_ref_clamp_sort(int& i1, int& j1, int& i2, int& j2)
// Подразумевается сделать (min_i, min_j, max_i, max_j)
{
	/*
	0┐000
	0└┐00
	00└┐0
	000└┐
	0000└ < для такого результата, здесь приписан небольшой костыль
	потому что все i и j "загоняются" в размеры массива
	и эти точки сравниваются относительно положения друг друга,
	не только геттерами right() и down()
	*/
	i1 = clamp(0, width, i1), j1 = clamp(0, height, j1); // clamp to maze size !NOT ARRAY SIZE
	i2 = clamp(0, width, i2), j2 = clamp(0, height, j2); // clamp to maze size !NOT ARRAY SIZE
	
	if (i1 > i2) { // sort i
		int temp = i1;
		i1 = i2, i2 = temp;
	}

	if (j1 > j2) { // sort j
		int temp = j1;
		j1 = j2, j2 = temp;
	}

	// верхние clamp укорачивают не до самих размеров массива,
	// поэтому левый i и верхний j (минимум) должен вписываться в размеры массива
	// чтобы при взятии c1 в [has\make\remove]Connection - не ломалось
	i1 = std::min(i1, width - 1); // clamp to array size
	j1 = std::min(j1, height - 1); // clamp to array size
}

bool Maze::hasConnection(int i1, int j1, int i2, int j2)
{
	idx_ref_clamp_sort(i1, j1, i2, j2); // just for check and clamp with sort
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
	idx_ref_clamp_sort(i1, j1, i2, j2); // just for check and clamp with sort
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
	idx_ref_clamp_sort(i1, j1, i2, j2); // just for check and clamp with sort
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

	while(makeConnection(x, y, x + axis_flag, y + !axis_flag))
	{
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
			int lb = hasConnection(i - 1, j, i, j) ? 8 : 0, // left   flag-bit
				tb = hasConnection(i, j - 1, i, j) ? 4 : 0, // top    flag-bit
				rb = hasConnection(i, j, i + 1, j) ? 2 : 0, // right  flag-bit
				bb = hasConnection(i, j, i, j + 1) ? 1 : 0; // bottom flag-bit

			int bitmask = lb | tb | rb | bb; // bitmask
			char c = BITMASK_CHARS[bitmask];

			std::cout << char(c);

		}
		std::cout << std::endl;
	}

}
