#include "MemoryPresentNode.h"

MemoryPresentNode::MemoryPresentNode() : Node()
{
	isMemoryPresentNode = true;
	distancefromstart = 0;
}

MemoryPresentNode::MemoryPresentNode(int nodeid, bool _stmnodespresent) : Node(new CSRand(), nodeid)
{
	isMemoryPresentNode = true;
	distancefromstart = 0;
	stmnodespresent = _stmnodespresent;
}

MemoryPresentNode::~MemoryPresentNode()
{

}

double MemoryPresentNode::GetNodeValue(vector<double> inputs)
{
	double val = firstiteration || (!stmnodespresent) ? 0 : 1;
	firstiteration = false;
	return val;
}

bool MemoryPresentNode::STMNodesPresent()
{
	return stmnodespresent;
}