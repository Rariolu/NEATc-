#include "OutputMemoryNode.h"

OutputMemoryNode::OutputMemoryNode() : OutputMemoryNode(new CSRand())
{
	
}

OutputMemoryNode::OutputMemoryNode(CSRand* rand) : Node(rand)
{
	isOutputMemoryNode = true;
	distancefromstart = 10000;
}

OutputMemoryNode::OutputMemoryNode(CSRand* _rand, int nodeid) : Node(_rand,nodeid)
{
	isOutputMemoryNode = true;
	distancefromstart = 10000;
}

OutputMemoryNode::~OutputMemoryNode()
{

}

double OutputMemoryNode::GetNodeValue(vector<double> inputs)
{
	return previousIterationOutput = Node::GetNodeValue(inputs);
}

double OutputMemoryNode::GetPreviousIterationOutput()
{
	return previousIterationOutput;
}