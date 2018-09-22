#include "InputNode.h"

InputNode::InputNode(int index) : InputNode(index,new CSRand())
{

}

InputNode::InputNode(int index, CSRand* _rand) : Node(_rand)
{
	//cout << "InputNode created" << endl;
	Init(index, _rand);
}

InputNode::InputNode(int index, CSRand* _rand, int nodeID) : Node(_rand,nodeID)
{
	Init(index, _rand);
}

void InputNode::Init(int index, CSRand* _rand)
{
	isInput = true;
	inputIndex = index;
	distancefromstart = 0;
}

InputNode::~InputNode()
{
	
}

int InputNode::GetInputIndex()
{
	return inputIndex;
}

void InputNode::CreateClone()
{
	if (!_clone)
	{
		_clone = new InputNode(inputIndex, rand, GetNodeID());
	}
}