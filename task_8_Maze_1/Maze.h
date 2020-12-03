#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include "MCell.h"

int clamp(const int min, const int max, int value); // helper function

class Maze
{
private:
	class MCell* m_field;

public:

	const int width;
	const int height;

	Maze(int n, int m);
	~Maze();

	void buildSteps();

	const MCell &cell(int i, int j) const;
	void idx_ref_clamp_sort(int& i1, int& j1, int& i2, int& j2); // helper function
	bool hasConnection(int i1, int j1, int i2, int j2);
	bool makeConnection(int i1, int j1, int i2, int j2);
	bool removeConnection(int i1, int j1, int i2, int j2);
	void printMaze();
};

#endif // MAZE_H