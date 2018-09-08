#ifndef _INPUTNODE_H
#define _INPUTNODE_H

#include "Node.h"

class InputNode : public Node
{
	public:
		InputNode(int index);
		InputNode(int index, CSRand* _rand);
		InputNode(int index, CSRand* _rand, int nodeID);
		~InputNode();
		int GetInputIndex();
	private:
		void Init(int index, CSRand* _rand);
};

#endif