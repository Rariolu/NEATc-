#ifndef _INPUTMEMORYNODE_H
#define _INPUTMEMORYNODE_H

#include "OutputMemoryNode.h"

class InputMemoryNode : public Node
{
	public:
		InputMemoryNode(OutputMemoryNode* outputmemorynode);
		InputMemoryNode(OutputMemoryNode* outputmemorynode, CSRand* _rand);
		InputMemoryNode(OutputMemoryNode* outputmemorynode, CSRand* _rand, int nodeid);
		~InputMemoryNode();
		double GetNodeValue(vector<double> inputs);
		OutputMemoryNode* GetOutputMemoryNode();
		void CreateClone();
		InputMemoryNode* GetIMNClone();
	private:
		OutputMemoryNode* outputMemoryNode;
};

#endif