#ifndef _MEMORYPRESENTNODE_H
#define _MEMORYPRESENTNODE_H

#include "Node.h"
class MemoryPresentNode : public Node
{
	public:
		MemoryPresentNode();
		MemoryPresentNode(int nodeid);
		~MemoryPresentNode();
		double GetNodeValue(vector<double> inputs);
	private:
		bool firstiteration = true;
};

#endif