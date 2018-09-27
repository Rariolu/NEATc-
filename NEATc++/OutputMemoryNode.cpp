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

void OutputMemoryNode::SetValue(double val)
{
	previousIterationOutput = val;
}

void OutputMemoryNode::CreateClone()
{
	if (!_clone)
	{
		_clone = new OutputMemoryNode(rand, GetNodeID());
	}
}

OutputMemoryNode* OutputMemoryNode::GetOMNClone()
{
	return GetOMNClone(false);
}

OutputMemoryNode* OutputMemoryNode::GetOMNClone(bool longterm)
{
	OutputMemoryNode* omnclone = (OutputMemoryNode*)_clone;
	if (longterm)
	{
		omnclone->SetValue(GetPreviousIterationOutput());
	}
	return omnclone;
}