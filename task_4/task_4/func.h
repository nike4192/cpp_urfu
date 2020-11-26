#ifndef FUNC_H
#define FUNC_H

#include <iostream>

struct NumSequence {
	int start;
	int step;
	int (*seqFunction)(const NumSequence &seq, int prev);
};

NumSequence genArithProgression(const int start, const int step);
NumSequence genGeomProgression(const int start, const int step);

void printProgression(NumSequence(*prgGen)(const int start, const int step), int start, int step);

#endif