#include "MemoryPresentNode.h"

MemoryPresentNode::MemoryPresentNode() : Node()
{
	isMemoryPresentNode = true;
	distancefromstart = 0;
}

MemoryPresentNode::MemoryPresentNode(int nodeid) : Node(new CSRand(), nodeid)
{
	isMemoryPresentNode = true;
	distancefromstart = 0;
}

MemoryPresentNode::~MemoryPresentNode()
{

}

double MemoryPresentNode::GetNodeValue(vector<double> inputs)
{
	double val = firstiteration ? 0 : 1;
	firstiteration = false;
	return val;
}