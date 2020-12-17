#include <iostream>

#include "Maze.h"

int main() {
	Maze* maze = new Maze(5, 5);
	maze->buildSteps();
	maze->printMaze();
}