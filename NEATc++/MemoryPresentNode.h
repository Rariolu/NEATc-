#ifndef _MEMORYPRESENTNODE_H
#define _MEMORYPRESENTNODE_H

#include "Node.h"
class MemoryPresentNode : public Node
{
	public:
		MemoryPresentNode();
		MemoryPresentNode(int nodeid, bool _stmnodespresent);
		~MemoryPresentNode();
		bool STMNodesPresent();
		double GetNodeValue(vector<double> inputs);
	private:
		bool firstiteration = true;
		bool stmnodespresent = true;
};

#endif