#include <iostream>
#include "Maze.h"

int main() {

	// 1
	Maze* m = new Maze(5, 5);
	m->buildSteps();
	m->printMaze();

	return 0;
}                                          