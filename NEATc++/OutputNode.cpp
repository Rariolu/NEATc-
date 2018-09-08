#include "OutputNode.h"

OutputNode::OutputNode() : OutputNode(new CSRand())
{

}

OutputNode::OutputNode(CSRand* _rand) : Node(_rand)
{
	distancefromstart = 10000;
	isOutput = true;
	//cout << "Outputnode constructor" << endl;
}

OutputNode::OutputNode(CSRand* _rand, int nodeid) : Node(_rand, nodeid)
{
	distancefromstart = 10000;
	isOutput = true;
}

OutputNode::~OutputNode()
{

}