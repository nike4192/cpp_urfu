#include <iostream>

#include "Maze.h"
void mazeBuildSteps(Maze* maze) {

	int x = 0, y = 0;
	bool axis_flag = true; // Можно поменять начало: true - по x, false - по y

	while (x < maze->width && y < maze->height)
	{
		maze->makeConnection(x, y, x + axis_flag, y + !axis_flag);

		x += axis_flag,
			y += !axis_flag;

		axis_flag = !axis_flag;
	}
}
int main() {
	Maze* maze = new Maze(5, 5);
	mazeBuildSteps(maze);
	maze->printMaze();
}