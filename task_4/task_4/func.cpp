#include "func.h"

const int SEQ_NUM_COUNTS = 10;

int arithSeqFunction(const NumSequence &seq, int prev) {
	return prev + seq.step;
};

NumSequence genArithProgression(const int start, const int step)
{
	return NumSequence{ start, step, arithSeqFunction };
}

int geomSeqFunction(const NumSequence &seq, int prev) {
	return prev * seq.step;
};

NumSequence genGeomProgression(const int start, const int step)
{
	return NumSequence{ start, step, geomSeqFunction };
}

void printProgression(NumSequence(*prgGen)(const int start, const int step), int start, int step)
{
	NumSequence ns = prgGen(start, step);
	int prev = ns.start;

	for (int i = 0;;)
	{
		std::cout << prev;
		if (++i >= SEQ_NUM_COUNTS)
		{
			std::cout << "" << std::endl;
			break;
		}
		else
			std::cout << ", ";
		prev = ns.seqFunction(ns, prev);
	}
}