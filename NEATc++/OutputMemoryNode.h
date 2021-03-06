#ifndef _OUTPUTMEMORY_H
#define _OUTPUTMEMORY_H

#include "Node.h"
class OutputMemoryNode : public Node
{
	public:
		OutputMemoryNode();
		OutputMemoryNode(CSRand* _rand);
		OutputMemoryNode(CSRand* _rand, int nodeid);
		~OutputMemoryNode();
		double GetNodeValue(vector<double> inputs);
		double GetPreviousIterationOutput();
	private:
		double previousIterationOutput = 0;
};

#endif