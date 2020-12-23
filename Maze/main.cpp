#include <iostream>
#include <algorithm>

#include "Maze.h"
#include "MTreeNode.h"

void mazeBuildGridSteps(Maze* maze) {
	
	int x = 0, y = 0;
	bool axis_flag = true;
	int n = maze->width - 1,
		m = maze->height - 1;

	while (x < maze->width && y < maze->height)
	{
		int temp_x = x, temp_y = y;

		if (x < n) maze->makeConnection(x, y, x + 1, y);
		if (y < m) maze->makeConnection(x, y, x, y + 1);

		while (x < n && y < m) // recursion start for right or down
		{
			maze->makeConnection(x, y, x + !axis_flag, y + axis_flag);

			x += !axis_flag;
			y +=  axis_flag;
		} // recursion end

		x = temp_x +  axis_flag;
		y = temp_y + !axis_flag;

		axis_flag = !axis_flag;
	}
}

void buildTree(Maze* maze, MTreeNode* parent) // i, j [0, +Infinity]
{
	if (parent == nullptr) return;

	int i = parent->i(),
		j = parent->j();

	MCell cell = maze->cell(i, j);

	if (cell.right())
		if (parent->addChild(i + 1, j))
			buildTree(maze, (MTreeNode*)parent->hasChild(i + 1, j));

	if (cell.down())
		if (parent->addChild(i, j + 1))
			buildTree(maze, (MTreeNode*)parent->hasChild(i, j + 1));
}

void printWeightTree(MTreeNode* parent, int n, int m, int weight = 0, int* buffer = nullptr) // buffer for recursion: no argument can be passed
{ // Use only [parent, n, m] arguments
	bool printFlag = false;

	if (weight < 0) weight = 0; // Non-negative value

	if (buffer == nullptr) {
		int buffer_size = n * m;

		buffer = new int[buffer_size];
		for (int i = 0; i < buffer_size; i++)
			buffer[i] = -1;

		printFlag = true;
	}

	int i = parent->i(),
		j = parent->j();

	if (parent->childCount() > 0) { // Если есть потомки
		if (parent->hasChild(i + 1, j) != nullptr) { // Проход от предка к правому потомку с записью в буффер
			MTreeNode* childNodeX = (MTreeNode*)parent->hasChild(i + 1, j);
			for (int x = i; x < childNodeX->i(); x++)
				buffer[j * n + x] = weight;
			printWeightTree(childNodeX, n, m, weight + 1, buffer); // рекурсия
		}

		if (parent->hasChild(i, j + 1) != nullptr) { // Проход от предка к нижнему потомку с записью в буффер
			MTreeNode* childNodeY = (MTreeNode*)parent->hasChild(i, j + 1);
			for (int y = j; y < childNodeY->j(); y++)
				buffer[y * n + i] = weight;
			printWeightTree(childNodeY, n, m, weight + 1, buffer); // рекурсия
		}
	} else // Если нет потомков
		buffer[j * n + i] = weight; // End of tree

	if (printFlag) { // Вывод в консоль из буфера
		for (int y = 0; y < m; y++) {
			for (int x = 0; x < n; x++) {
				int value = buffer[y * n + x]; // Value
				if (value < 0) std::cout << "x"; //Empty Value
				else std::cout << value; // Print Value
				if (x < n - 1) std::cout << ' '; // Print Glue
			}
			std::cout << std::endl;
		}
	}
	
}

int main()
{
	const int width = 5, height = 5;
	
	/* 1 */
	Maze* maze = new Maze(width, height);
	mazeBuildGridSteps(maze);
	maze->printMaze();

	std::cout /* ATTENTION: that piece of code depends on the already output*/
		<< std::endl // DELIMITER (new line)
		<< "\033[s" // Save cursor position
		<< "\033[" << (height + 1) << "A" // Move the cursor up <height + 1> lines, because the first character <std::endl> printed
		<< "0" // Insert 0
		<< "\033[u"; // Restore cursor position

	/* 2 */
	MTreeNode* treeRoot = MTreeNode::beginTree(0, 0);
	buildTree(maze, treeRoot);
	printWeightTree(treeRoot, maze->width, maze->height);

	return 0;
}