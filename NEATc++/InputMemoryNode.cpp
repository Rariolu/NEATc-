#include "InputMemoryNode.h"



InputMemoryNode::InputMemoryNode(OutputMemoryNode* outputmemorynode) : InputMemoryNode(outputmemorynode,new CSRand())
{
	//outputMemoryNode = outputmemorynode;
}

InputMemoryNode::InputMemoryNode(OutputMemoryNode* outputmemorynode, CSRand* _rand) : InputMemoryNode(outputmemorynode,_rand,nodenum++)
{

}

InputMemoryNode::InputMemoryNode(OutputMemoryNode* outputmemorynode, CSRand* _rand, int nodeid) : Node(_rand,nodeid)
{
	outputMemoryNode = outputmemorynode;
	isInputMemoryNode = true;
	distancefromstart = 0;
}

InputMemoryNode::~InputMemoryNode()
{
	//outputMemoryNode->~OutputMemoryNode();
}

double InputMemoryNode::GetNodeValue(vector<double> inputs)
{
	cout << "Received node value from the input node" << endl;
	return outputMemoryNode->GetPreviousIterationOutput();
}

OutputMemoryNode* InputMemoryNode::GetOutputMemoryNode()
{
	return outputMemoryNode;
}

void InputMemoryNode::CreateClone()
{
	if (!_clone)
	{
		GetOutputMemoryNode()->CreateClone();
		OutputMemoryNode* omnclone = (OutputMemoryNode*)GetOutputMemoryNode()->GetClone();
		_clone = new InputMemoryNode(omnclone, rand, GetNodeID());
		
	}
}

InputMemoryNode* InputMemoryNode::GetIMNClone()
{
	return (InputMemoryNode*)_clone;
}