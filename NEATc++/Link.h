#ifndef _LINK_H
#define _LINK_H

#include"Node.h"

//class Node;

class Link
{
	public:
		Link(Node* source, Node* destination);
		~Link();
	private:
		Node * _source;
		Node* _destination;
		double weight;
};

#endif