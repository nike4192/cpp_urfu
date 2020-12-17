#ifndef MCELL_H
#define MCELL_H

#include "Maze.h"

class MCell
{
	friend class Maze;
private:
	MCell();
	bool m_down = false;
	bool m_right = false;

public:
	bool down();
	bool right();
};

#endif // MCELL_H