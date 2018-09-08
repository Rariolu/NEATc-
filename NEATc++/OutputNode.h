#ifndef _OUTPUTNODE_H

#define _OUTPUTNODE_H

#include "Node.h"
class OutputNode : public Node
{
	public:
		OutputNode();
		OutputNode(CSRand* _rand);
		OutputNode(CSRand* _rand, int nodeid);
		~OutputNode();
};

#endif