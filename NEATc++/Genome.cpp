#include "Genome.h"

Genome::Genome(int inputcount, int outputcount) : Genome(inputcount, outputcount, time(NULL))
{
	ConsoleManager::Output("New Rand in Genome");
}

Genome::Genome(int inputcount, int outputcount, int randseed) : Genome(inputcount,outputcount,0,randseed)
{
	//_id = randseed;
	//rand = new CSRand();
	//for (int i = 0; i < inputcount; i++)
	//{
	//	InputNode* inp = new InputNode(i, rand);
	//	_nodes.push_back(inp);
	//	_inputnodes.push_back(inp);
	//}
	//for (int i = 0; i < outputcount; i++)
	//{
	//	OutputNode* outt = new OutputNode(rand);
	//	_nodes.push_back(outt);
	//	_outputnodes.push_back(outt);
	//}
	//InputCount = inputcount;
	//OutputCount = outputcount;
}

Genome::Genome(int inputcount, int outputcount, int memorycount, int randseed) : Genome(inputcount,outputcount,memorycount,memorycount,randseed)
{

}

Genome::Genome(int inputcount, int outputcount, int stmcount, int ltmcount, int randseed)
{
	_id = randseed;
	rand = new CSRand();
	for (int i = 0; i < inputcount; i++)
	{
		InputNode* inp = new InputNode(i, rand);
		_nodes.push_back(inp);
		_inputnodes.push_back(inp);
	}
	for (int i = 0; i < outputcount; i++)
	{
		OutputNode* outt = new OutputNode(rand);
		_nodes.push_back(outt);
		_outputnodes.push_back(outt);
	}

	_memorypresentnode = new MemoryPresentNode();
	_nodes.push_back(_memorypresentnode);

	for (int i = 0; i < /*memorycount*/stmcount; i++)
	{
		OutputMemoryNode* outputmemorynode = new OutputMemoryNode(rand);
		_stoutputmemorynodes.push_back(outputmemorynode);
		InputMemoryNode* inputmemorynode = new InputMemoryNode(outputmemorynode);
		_stinputmemorynodes.push_back(inputmemorynode);
		_nodes.push_back(outputmemorynode);
		_nodes.push_back(inputmemorynode);
	}

	for (int i = 0; i < ltmcount; i++)
	{
		OutputMemoryNode* omn = new OutputMemoryNode(rand);
		_ltoutputmemorynodes.push_back(omn);
		InputMemoryNode* imn = new InputMemoryNode(omn);
		_ltinputmemorynodes.push_back(imn);
		_nodes.push_back(omn);
		_nodes.push_back(imn);
	}

	InputCount = inputcount;
	OutputCount = outputcount;
	STMemoryCount = stmcount;
	LTMemoryCount = ltmcount;
}

int Genome::ID()
{
	return _id;
}

Genome* Genome::Clone(int genomeid)
{
	//vector<InputNode*> inputs;
	//vector<OutputNode*> outputs;
	//vector<Node*> allnodes;
	//vector<Node*> intermediates;
	//vector<InputMemoryNode*> inputmemorynodes;
	//vector<OutputMemoryNode*> outputmemorynodes;
	//map<int, Node*> nodedict;
	//MemoryPresentNode* memorypresentnode = new MemoryPresentNode(_memorypresentnode->GetNodeID());
	//allnodes.push_back(memorypresentnode);
	//nodedict.insert(make_pair(memorypresentnode->GetNodeID(), memorypresentnode));
	//CSRand* newRAND = new CSRand();//(genomeid + Operations::RandomNumber(1,11));// *Operations::RandomNumber(1, RAND_MAX));
	//
	////ConsoleManager::Output("The amount of inputs is "+to_string(_inputnodes.size())+" , the amount of outputs is "+to_string(_outputnodes.size())+" and the amount of intermediates is "+to_string(_intermediatenodes.size()));
	//for (vector<InputNode*>::iterator iN = _inputnodes.begin(); iN < _inputnodes.end(); iN++)
	//{
	//	InputNode* inode = new InputNode((*iN)->GetInputIndex(), newRAND, (*iN)->GetNodeID());
	//	inputs.push_back(inode);
	//	allnodes.push_back(inode);
	//	nodedict.insert(make_pair(inode->GetNodeID(), inode));
	//	//ConsoleManager::Output("InputNode "+to_string(inode->GetNodeID())+" added.");
	//}
	////ConsoleManager::Output("Input nodes created");
	//for (vector<OutputNode*>::iterator oN = _outputnodes.begin(); oN < _outputnodes.end(); oN++)
	//{
	//	OutputNode* onode = new OutputNode(newRAND, (*oN)->GetNodeID());
	//	outputs.push_back(onode);
	//	allnodes.push_back(onode);
	//	nodedict.insert(make_pair(onode->GetNodeID(), onode));
	//	//ConsoleManager::Output("OutputNode " + to_string(onode->GetNodeID()) + " added.");
	//}
	////ConsoleManager::Output("Output nodes created");
	//for (vector<Node*>::iterator intN = _intermediatenodes.begin(); intN < _intermediatenodes.end(); intN++)
	//{
	//	Node* intnode = new Node(newRAND, (*intN)->GetNodeID());
	//	intnode->SetDistance((*intN)->GetDistance());
	//	intermediates.push_back(intnode);
	//	allnodes.push_back(intnode);
	//	nodedict.insert(make_pair(intnode->GetNodeID(), intnode));
	//	//ConsoleManager::Output("IntermediateNode: " + to_string(intnode->GetNodeID()) + " added.");
	//}
	//if (STMemoryCount > 0)
	//{
	//	for (vector<InputMemoryNode*>::iterator inpmemnode = inputmemorynodes.begin(); inpmemnode < inputmemorynodes.end(); inpmemnode++)
	//	{
	//		OutputMemoryNode* omn = (*inpmemnode)->GetOutputMemoryNode();
	//		OutputMemoryNode* outputmem = new OutputMemoryNode(newRAND, omn->GetNodeID());
	//		InputMemoryNode* inputmem = new InputMemoryNode(outputmem, newRAND, (*inpmemnode)->GetNodeID());
	//		inputmemorynodes.push_back(inputmem);
	//		outputmemorynodes.push_back(outputmem);
	//		allnodes.push_back(inputmem);
	//		allnodes.push_back(outputmem);
	//	}
	//}
	////ConsoleManager::Output("The amount of nodes in parent is " + to_string(_nodes.size()) + " and the amount of nodes in nodedict is "+to_string(nodedict.size()));
	////ConsoleManager::Output("Intermediate nodes created");
	//for (vector<Node*>::iterator n = _nodes.begin(); n < _nodes.end(); n++)
	//{
	//	if (!(*n)->IsInput())
	//	{
	//		int thisID = (*n)->GetNodeID();
	//		//ConsoleManager::Output("thisID is " + to_string(thisID));
	//		vector<Node::Link*> inps = (*n)->GetInputs();
	//		//ConsoleManager::Output(to_string(thisID) + ": inputs found");
	//		int iterations = 0;
	//		if (inps.size() > 0)
	//		{
	//			for (vector<Node::Link*>::iterator inp = inps.begin(); inp < inps.end(); inp++)
	//			{
	//				//ConsoleManager::Output("Iteration: " + to_string(iterations++));
	//				int source = (*inp)->GetSource()->GetNodeID();
	//				double weight = (*inp)->GetWeight();
	//				Node* sourcen = NULL;
	//				Node* dest = NULL;
	//				map<int, Node*>::iterator s = nodedict.find(source);
	//				if (s != nodedict.end())
	//				{
	//					sourcen = s->second;
	//				}
	//				map<int, Node*>::iterator d = nodedict.find(thisID);
	//				if (d != nodedict.end())
	//				{
	//					dest = d->second;
	//				}
	//				if (sourcen != NULL && dest != NULL)
	//				{
	//					Node::Link* link = new Node::Link(sourcen, dest, newRAND, weight);
	//					sourcen->AddOutput(link);
	//					dest->AddInput(link);
	//				}
	//				else
	//				{
	//					ConsoleManager::Output("NULL found you pillock.");
	//					if (sourcen != NULL)
	//					{
	//						ConsoleManager::Output("Just dest is NULL");
	//					}
	//					else if (dest != NULL)
	//					{
	//						ConsoleManager::Output("Just sourcen is NULL");
	//					}
	//					else
	//					{
	//						ConsoleManager::Output("THEY'RE BOTH NULL YOU PRICK!");
	//					}
	//				}
	//			}
	//		}
	//		else
	//		{
	//			//ConsoleManager::Output("Zero inputs found.");
	//		}
	//		//ConsoleManager::Output("Loop for " + to_string(thisID) + " terminated.");
	//	}
	//	
	//}
	//Genome* newgenome = new Genome(InputCount, OutputCount,STMemoryCount,LTMemoryCount, genomeid);
	//newgenome->SetNodes(allnodes, inputs, outputs, intermediates,inputmemorynodes,outputmemorynodes,memorypresentnode);
	//newgenome->SetRand(newRAND);
	//return newgenome;
	for (int i = 0; i < _nodes.size(); i++)
	{
		_nodes[i]->CreateClone();
	}
	vector<Node*> clonenodes;
	for (int i = 0; i < _nodes.size(); i++)
	{
		clonenodes.push_back(_nodes[i]->GetClone());
	}
	vector<Node*> cloneintermediates;
	for (int i = 0; i < _intermediatenodes.size(); i++)
	{
		cloneintermediates.push_back(_intermediatenodes[i]->GetClone());
	}
	vector<InputNode*> cloneinputnodes;
	for (int i = 0; i < _inputnodes.size(); i++)
	{
		cloneinputnodes.push_back(_inputnodes[i]->GetINClone());
	}
	

	vector<Node::Link*>* linkclones = new vector<Node::Link*>();
	for (int i = 0; i < links->size(); i++)
	{
		linkclones->push_back(links->at(i)->GetClone());
	}

	Genome* _clone = new Genome(GetInputCount(), GetOutputCount(), GetSTMemoryCount(), GetLTMemoryCount(), genomeid);
	
	_clone->SetLinks(linkclones);

	return _clone;
}

vector<InputNode*> Genome::GetInputNodes()
{
	return _inputnodes;
}

vector<Node*> Genome::GetIntermediateNodes()
{
	return _intermediatenodes;
}

vector<OutputNode*> Genome::GetOutputNodes()
{
	return _outputnodes;
}

vector<InputMemoryNode*> Genome::GetLTInputMemoryNodes()
{
	return _ltinputmemorynodes;
}

vector<OutputMemoryNode*> Genome::GetLTOutputMemoryNodes()
{
	return _ltoutputmemorynodes;
}

vector<InputMemoryNode*> Genome::GetSTInputMemoryNodes()
{
	return _stinputmemorynodes;
}

vector<OutputMemoryNode*> Genome::GetSTOutputMemoryNodes()
{
	return _stoutputmemorynodes;
}

MemoryPresentNode* Genome::GetMemoryPresentNode()
{
	return _memorypresentnode;
}

vector<Node*> Genome::GetNodes()
{
	return _nodes;
}

void Genome::SetNodes(vector<Node*> allnodes, vector<InputNode*> inputnodes, vector<OutputNode*> outputnodes, vector<Node*> intermediatenodes, vector<InputMemoryNode*> ltinputmemorynodes, vector<OutputMemoryNode*> ltoutputmemorynodes,vector<InputMemoryNode*> stinputmemorynodes, vector<OutputMemoryNode*> stoutputmemorynodes, MemoryPresentNode* memorypresentnode)
{
	_nodes = allnodes;
	_inputnodes = inputnodes;
	_outputnodes = outputnodes;
	_intermediatenodes = intermediatenodes;
	_ltinputmemorynodes = ltinputmemorynodes;
	_ltoutputmemorynodes = ltoutputmemorynodes;
	_stinputmemorynodes = stinputmemorynodes;
	_stoutputmemorynodes = stoutputmemorynodes;
	_memorypresentnode = memorypresentnode;
}

void Genome::SetLinks(vector<Node::Link*>* _links)
{
	links->~vector();
	links = _links;
}

void Genome::SetRand(CSRand* _rand)
{
	rand = _rand;
}

Genome::~Genome()
{
	for (vector<Node*>::iterator n = _nodes.begin(); n < _nodes.end(); n++)
	{
		(*n)->~Node();
	}
	rand->~CSRand();
	links->~vector();
}

void Genome::AddNode(Node* prevnode, Node* nextnode)
{
	Node* newnode = new Node(rand);
	newnode->RandomiseDistance(prevnode->GetDistance(), nextnode->GetDistance());
	prevnode->AddOutput(newnode);
	newnode->AddOutput(nextnode);
	_nodes.push_back(newnode);
	_intermediatenodes.push_back(newnode);
}

void Genome::RemoveNode(Node* node)
{
	vector<Node*>::iterator it = GetNodeIterator(node);
	if (it != _nodes.end())
	{
		_nodes.erase(it);
	}
	vector<Node*>::iterator interim = GetIntermediateNodeIterator(node);
	if (interim != _intermediatenodes.end())
	{
		_intermediatenodes.erase(interim);
	}
}

vector<Node*>::iterator Genome::GetNodeIterator(Node* node)
{
	return find(_nodes.begin(), _nodes.end(), node);
}

vector<Node*>::iterator Genome::GetIntermediateNodeIterator(Node* node)
{
	return find(_intermediatenodes.begin(), _intermediatenodes.end(), node);
}

void Genome::ResetMemory()
{
	if (_nodes.size() > 0)
	{
		for (vector<Node*>::iterator i = _nodes.begin(); i < _nodes.end(); i++)
		{
			(*i)->ResetMemory();
		}
	}
	else
	{
		ConsoleManager::Output("There are no nodes in this genome, curious");
	}
}

double Genome::GetOutput(vector<double> inputs, int outputnum)
{
	if (outputnum < 0 || outputnum >= _outputnodes.size())
	{
		return 0;
	}
	return _outputnodes.at(outputnum)->GetNodeValue(inputs);
}

void Genome::Mutate(int iterations = 1)
{
	for (int i = 0; i < iterations; i++)
	{
		if (rand->NextDouble() < WeightMutation)
		{
			for (int i = 0; i < 3; i++)
			{
				int nodeindex = rand->Next(_nodes.size());
				_nodes[nodeindex]->MutateWeight();
			}
			
		}
		if (rand->NextDouble() < LinkMutation)
		{
			int nodeindexA = GetRandomNodeIndex();
			int nodeindexB = GetRandomNodeIndex(nodeindexA, _nodes[nodeindexA]->GetDistance());
			Node* prevnode;
			Node* nextnode;
			if (_nodes[nodeindexA]->GetDistance() < _nodes[nodeindexB]->GetDistance())
			{
				prevnode = _nodes[nodeindexA];
				nextnode = _nodes[nodeindexB];
			}
			else
			{
				prevnode = _nodes[nodeindexB];
				nextnode = _nodes[nodeindexA];
			}
			prevnode->AddOutput(nextnode);
		}
		if (rand->NextDouble() < NodeMutation)
		{
			if (rand->NextBool())
			{
				int nodeIndexA = GetRandomNodeIndex();
				int nodeIndexB = GetRandomNodeIndex(nodeIndexA, _nodes[nodeIndexA]->GetDistance());
				Node* prevnode;
				Node* nextnode;
				if (_nodes[nodeIndexA]->GetDistance() < _nodes[nodeIndexB]->GetDistance())
				{
					prevnode = _nodes[nodeIndexA];
					nextnode = _nodes[nodeIndexB];
				}
				else
				{
					prevnode = _nodes[nodeIndexB];
					nextnode = _nodes[nodeIndexA];
				}
				AddNode(prevnode, nextnode);
			}
			else
			{
				if (_intermediatenodes.size() > 0)
				{
					int nodeindex = rand->Next(_intermediatenodes.size());
					Node* n = _intermediatenodes[nodeindex];
					n->RemoveFromGenome();
					RemoveNode(n);
					n->~Node();
				}
			}
		}
		if (rand->NextDouble() < Adjustment)
		{
			for (vector<Node*>::iterator interim = _intermediatenodes.begin(); interim < _intermediatenodes.end(); interim++)
			{
				(*interim)->RemoveWeakInputs();
				(*interim)->ImproveStrongInputs();
			}
			for (vector<OutputNode*>::iterator outputnode = _outputnodes.begin(); outputnode < _outputnodes.end(); outputnode++)
			{
				(*outputnode)->RemoveWeakInputs();
				(*outputnode)->ImproveStrongInputs();
			}
		}
		//if (rand->NextDouble() < metamutation)
		//{
		//	WeightMutation = MetaMutate(WeightMutation);
		//	LinkMutation = MetaMutate(LinkMutation);
		//	NodeMutation = MetaMutate(NodeMutation);
		//	if (rand->NextDouble() < metametamutation)
		//	{
		//		metamutation = MetaMutate(metamutation);
		//	}
		//}
	}
}

double Genome::MetaMutate(double value)
{
	double t = value + (value * rand->NextDouble(-0.25, 0.25));
	if (t <= 0)
	{
		t = 0.001;
	}
	else if (t >= 1)
	{
		t = 0.999;
	}
	return t;
}

int Genome::GetRandomNodeIndex()
{
	return GetRandomNodeIndex(-1, -1);
}

int Genome::GetRandomNodeIndex(int ignoredindex, int ignoreddistance)
{
	int distance = ignoreddistance;
	int node;
	while (distance == ignoreddistance)
	{
		node = rand->NextWithIgnorance(_nodes.size(), ignoredindex);
		distance = _nodes[node]->GetDistance();
	}
	return node;
}

CSRand* Genome::GetRand()
{
	return rand;
}

int Genome::GetInputCount()
{
	return InputCount;
}

int Genome::GetOutputCount()
{
	return OutputCount;
}

int Genome::GetLTMemoryCount()
{
	return LTMemoryCount;
}

int Genome::GetSTMemoryCount()
{
	return STMemoryCount;
}

Genome* Genome::Merge(Genome* a, Genome* b,int mergeid)
{
	if (a->GetInputCount() != b->GetInputCount() || a->GetOutputCount() != b->GetOutputCount() || a->GetLTMemoryCount() != b->GetLTMemoryCount() || a->GetSTMemoryCount() != b->GetSTMemoryCount())
	{
		return NULL;
	}
	vector<InputNode*> inputs;
	vector<OutputNode*> outputs;
	vector<Node*> allnodes;
	vector<Node*> intermediates;

	vector<InputMemoryNode*> ltinputmemorynodes;
	vector<OutputMemoryNode*> ltoutputmemorynodes;

	vector<InputMemoryNode*> stinputmemorynodes;
	vector<OutputMemoryNode*> stoutputmemorynodes;

	map<int, Node*> nodedict;

	MemoryPresentNode* memorypresentnode = new MemoryPresentNode(a->GetMemoryPresentNode()->GetNodeID(),a->GetSTMemoryCount() > 0 && a->GetLTMemoryCount() > 0);
	allnodes.push_back(memorypresentnode);
	nodedict.insert(make_pair(memorypresentnode->GetNodeID(), memorypresentnode));

	Genome* newgenome = new Genome(a->GetInputCount(), a->GetOutputCount(), mergeid);
	CSRand* newRAND = new CSRand(mergeid + Operations::RandomNumber(1, 11));
	vector<InputNode*> _ainputs = a->GetInputNodes();
	//vector<InputNode*> _binputs = b->GetInputNodes();
	vector<Node*> _aintermediates = a->GetIntermediateNodes();
	vector<Node*> _bintermediates = b->GetIntermediateNodes();
	vector<OutputNode*> _aoutputs = a->GetOutputNodes();
	//vector<OutputNode*> _boutputs = b->GetOutputNodes();
	vector<Node*> _aAllnodes = a->GetNodes();
	vector<Node*> _bAllnodes = b->GetNodes();

	vector<InputMemoryNode*> _aLTInputMemoryNodes = a->GetLTInputMemoryNodes();
	vector<OutputMemoryNode*> _aLTOutputMemoryNodes = a->GetLTOutputMemoryNodes();
	vector<InputMemoryNode*> _aSTInputMemoryNodes = a->GetSTInputMemoryNodes();
	vector<OutputMemoryNode*> _aSTOutputMemoryNodes = a->GetSTOutputMemoryNodes();

	for (int i = 0; i < a->GetInputCount(); i++)
	{
		int inpid = _ainputs[i]->GetNodeID();
		
		InputNode* inp = new InputNode(i, newRAND, inpid);
		inputs.push_back(inp);
		allnodes.push_back(inp);
		nodedict.insert(make_pair(inpid, inp));
	}
	for (int i = 0; i < _aintermediates.size(); i++)
	{
		Node* aint = _aintermediates[i];
		int id = aint->GetNodeID();
		Node* n = new Node(newRAND,id);
		n->SetDistance(aint->GetDistance());
		intermediates.push_back(n);
		allnodes.push_back(n);
		nodedict.insert(make_pair(id,n));
	}
	for (int i = 0; i < _bintermediates.size(); i++)
	{
		Node* bint = _bintermediates[i];
		int id = bint->GetNodeID();
		map<int, Node*>::iterator temp = nodedict.find(id);
		if (temp != nodedict.end())
		{
			Node* n = new Node(newRAND, id);
			n->SetDistance(bint->GetDistance());
			intermediates.push_back(n);
			allnodes.push_back(n);
			nodedict.insert(make_pair(id, n));
		}
	}
	for (int i = 0; i < a->GetOutputCount(); i++)
	{
		int outid = _aoutputs[i]->GetNodeID();
		OutputNode* out = new OutputNode(newRAND, outid);
		outputs.push_back(out);
		allnodes.push_back(out);
		nodedict.insert(make_pair(outid, out));
	}
	for (int i = 0; i < a->GetSTMemoryCount(); i++)
	{
		int inpmemid = _aSTInputMemoryNodes[i]->GetNodeID();
		int outmemid = _aSTInputMemoryNodes[i]->GetOutputMemoryNode()->GetNodeID();
		OutputMemoryNode* outputmem = new OutputMemoryNode(newRAND, outmemid);
		InputMemoryNode* inputmem = new InputMemoryNode(outputmem, newRAND, inpmemid);
		inputmemorynodes.push_back(inputmem);
		outputmemorynodes.push_back(outputmem);
		allnodes.push_back(inputmem);
		allnodes.push_back(outputmem);
		nodedict.insert(make_pair(inpmemid, inputmem));
		nodedict.insert(make_pair(outmemid, outputmem));
	}
	for (int i = 0; i < a->GetLTMemoryCount(); i++)
	{
		int inpmemid = _aLTInputMemoryNodes[i]->GetNodeID();
		int outmemid = _aLTInputMemoryNodes[i]->GetOutputMemoryNode()->GetNodeID();
		OutputMemoryNode* outputmem = new OutputMemoryNode(newRAND, outmemid);
		InputMemoryNode* inputmem = new InputMemoryNode(outputmem, newRAND, inpmemid);
		inputmemorynodes.push_back(inputmem);
		outputmemorynodes.push_back(outputmem);
		allnodes.push_back(inputmem);
		allnodes.push_back(outputmem);
		nodedict.insert(make_pair(inpmemid, inputmem));
		nodedict.insert(make_pair(outmemid, outputmem));
	}
	for (int i = 0; i < _aAllnodes.size(); i++)
	{
		Node* node = _aAllnodes[i];
		vector<Node::Link*> node_inputs = node->GetInputs();
		if (node_inputs.size() > 0)
		{
			for (vector<Node::Link*>::iterator i = node_inputs.begin(); i < node_inputs.end(); i++)
			{
				if ((*i)->GetSource() != NULL && (*i)->GetDestination() != NULL)
				{
					int sourceid = (*i)->GetSource()->GetNodeID();
					int destid = (*i)->GetDestination()->GetNodeID();
					map<int, Node*>::iterator s = nodedict.find(sourceid);
					map<int, Node*>::iterator d = nodedict.find(destid);
					if (s != nodedict.end() && d != nodedict.end())
					{
						Node::Link* link = new Node::Link(s->second, d->second, newRAND, (*i)->GetWeight());
						s->second->AddOutput(link);
						d->second->AddInput(link);
					}
				}
			}
		}
	}
	for (int i = 0; i < _bAllnodes.size(); i++)
	{
		Node* node = _bAllnodes[i];
		vector<Node::Link*> node_inputs = node->GetInputs();
		if (node_inputs.size() > 0)
		{
			for (vector<Node::Link*>::iterator i = node_inputs.begin(); i < node_inputs.end(); i++)
			{
				if ((*i)->GetSource() != NULL && (*i)->GetDestination() != NULL)
				{
					int sourceid = (*i)->GetSource()->GetNodeID();
					int destid = (*i)->GetDestination()->GetNodeID();
					map<int, Node*>::iterator s = nodedict.find(sourceid);
					map<int, Node*>::iterator d = nodedict.find(destid);
					if (s != nodedict.end() && d != nodedict.end())
					{
						if (!d->second->HasInput(sourceid))
						{
							Node::Link* link = new Node::Link(s->second, d->second, newRAND, (*i)->GetWeight());
							s->second->AddOutput(link);
							d->second->AddInput(link);
						}
					}
				}
			}
		}
	}
	newgenome->SetNodes(allnodes, inputs, outputs, intermediates,inputmemorynodes,outputmemorynodes,memorypresentnode);
	newgenome->SetRand(newRAND);
	return newgenome;
}

Genome* Genome::GetGenomeWithCommonProperties(Genome* a, Genome* b, int mergeid)
{
	if (a->GetInputCount() != b->GetInputCount() || a->GetOutputCount() != b->GetOutputCount() || a->GetSTMemoryCount() != b->GetSTMemoryCount() || a->GetLTMemoryCount() != b->GetLTMemoryCount())
	{
		return NULL;
	}
	map<int, Node*> aNodes = a->GetNodeMap();
	map<int, Node*> bNodes = b->GetNodeMap();
	vector<Node*> commonNodes;
	CSRand* newRAND = new CSRand(mergeid);
	vector<int> aDeletionIndexes;
	for (map<int, Node*>::iterator aNode = aNodes.begin(); aNode != aNodes.end(); aNode++)
	{
		map<int, Node*>::iterator biter = bNodes.find(aNode->first);
		if (biter == bNodes.end())
		{
			aDeletionIndexes.push_back(aNode->first);
		}
	}
	if (aDeletionIndexes.size() > 0)
	{
		for (vector<int>::iterator index = aDeletionIndexes.begin(); index < aDeletionIndexes.end(); index++)
		{
			aNodes.erase(aNodes.find((*index)));
		}
	}

	vector<int> bDeletionIndexes;
	for (map<int, Node*>::iterator bNode = bNodes.begin(); bNode != bNodes.end(); bNode++)
	{
		map<int, Node*>::iterator aiter = aNodes.find(bNode->first);
		if (aiter == aNodes.end())
		{
			bDeletionIndexes.push_back(bNode->first);
		}
	}
	if (bDeletionIndexes.size() > 0)
	{
		for (vector<int>::iterator index = bDeletionIndexes.begin(); index < bDeletionIndexes.end(); index++)
		{
			bNodes.erase(bNodes.find((*index)));
		}
	}

	vector<InputNode*> _inputs;
	vector<OutputNode*> _outputs;
	vector<Node*> _intermediates;
	vector<Node*> _allnodes;

	vector<InputMemoryNode*> _stinputmemorynodes;
	vector<OutputMemoryNode*> _stoutputmemorynodes;

	vector<InputMemoryNode*> _ltinputmemorynodes;
	vector<OutputMemoryNode*> _ltoutputmemorynodes;

	map<int, Node*> nodedict;

	MemoryPresentNode* _memorypresentnode = new MemoryPresentNode(a->GetMemoryPresentNode()->GetNodeID(),a->GetSTMemoryCount() > 0 && a->GetLTMemoryCount() > 0);
	_allnodes.push_back(_memorypresentnode);
	nodedict.insert(make_pair(_memorypresentnode->GetNodeID(), _memorypresentnode));

	for (map<int, Node*>::iterator aNode = aNodes.begin(); aNode != aNodes.end(); aNode++)
	{
		Node* currentNode = aNode->second;
		int nodeid = currentNode->GetNodeID();
		if (currentNode->IsInput())
		{
			InputNode* inp = new InputNode(nodeid, newRAND, nodeid);
			_inputs.push_back(inp);
			_allnodes.push_back(inp);
			nodedict.insert(make_pair(nodeid, inp));
		}
		else if (currentNode->IsOutput())
		{
			OutputNode* out = new OutputNode(newRAND, nodeid);
			_outputs.push_back(out);
			_allnodes.push_back(out);
			nodedict.insert(make_pair(nodeid, out));
		}
		else if (currentNode->IsInputMemoryNode())
		{
			InputMemoryNode* currentAsIMN = (InputMemoryNode*)currentNode;
			OutputMemoryNode* currentOutputMN = currentAsIMN->GetOutputMemoryNode();

			int inpID = nodeid;
			int outID = currentOutputMN->GetNodeID();

			OutputMemoryNode* out = new OutputMemoryNode(newRAND, outID);
			InputMemoryNode* inp = new InputMemoryNode(out, newRAND, inpID);

			_inputmemorynodes.push_back(inp);
			_outputmemorynodes.push_back(out);

			_allnodes.push_back(inp);
			_allnodes.push_back(out);

			nodedict.insert(make_pair(inpID, inp));
			nodedict.insert(make_pair(outID, out));
		}
		else if (currentNode->IsOutputMemoryNode())
		{
			//Do nothing for now, just leaving this here in case it's necessary at some point.
		}
		else if (currentNode->IsMemoryPresentNode())
		{
			_memorypresentnode = new MemoryPresentNode(nodeid,((MemoryPresentNode*)currentNode)->STMNodesPresent());
			_allnodes.push_back(_memorypresentnode);
			nodedict.insert(make_pair(nodeid, _memorypresentnode));
		}
		else
		{
			Node* n = new Node(newRAND, nodeid);
			n->SetDistance(currentNode->GetDistance());
			_intermediates.push_back(n);
			_allnodes.push_back(n);
			nodedict.insert(make_pair(nodeid, n));
		}
	}
	for (map<int, Node*>::iterator node = nodedict.begin(); node != nodedict.end(); node++)
	{
		Node* n = node->second;
		int nodeid = node->first;
		Node* aNode = aNodes.find(nodeid)->second;
		Node* bNode = bNodes.find(nodeid)->second;
		if (!n->IsInput())
		{
			vector<Node::Link*> aInputs = aNode->GetInputs();

			vector<Node::Link*> bInputs = bNode->GetInputs();
			if (aInputs.size() > 0 && bInputs.size() > 0)
			{
				for (vector<Node::Link*>::iterator aInput = aInputs.begin(); aInput < aInputs.end(); aInput++)
				{
					Node* Asource = (*aInput)->GetSource();
					if (Asource != NULL)
					{
						int sourceid = Asource->GetNodeID();
						map<int, Node*>::iterator nodedictsource = nodedict.find(sourceid);
						if (nodedictsource != nodedict.end())
						{
							for (vector<Node::Link*>::iterator bInput = bInputs.begin(); bInput < bInputs.end(); bInput++)
							{
								Node* Bsource = (*bInput)->GetSource();
								if (Bsource != NULL)
								{
									if (Bsource->GetNodeID() == sourceid)
									{
										double aWeight = (*aInput)->GetWeight();
										double bWeight = (*bInput)->GetWeight();
										double newWeight = (aWeight + bWeight) / 2;
										Node* source = nodedictsource->second;
										Node::Link* link = new Node::Link(source, n, newRAND, newWeight);
										source->AddOutput(link);
										n->AddInput(link);
										break;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	Genome* genome = new Genome(a->GetInputCount(), b->GetInputCount(), mergeid);
	genome->SetRand(newRAND);
	genome->SetNodes(_allnodes, _inputs, _outputs, _intermediates, _inputmemorynodes,_outputmemorynodes,_memorypresentnode);
	cout << "A nodes: " << a->GetNodes().size()<< "; B nodes: " << b->GetNodes().size() << "; New nodes: "<<genome->GetNodes().size() << endl;
	return genome;
}

void Genome::Train(vector<double> inputs, vector<double> outputs)
{
	
}

map<int, Node*> Genome::GetNodeMap()
{
	map<int, Node*> _map;
	if (_nodes.size() > 0)
	{
		for (vector<Node*>::iterator n = _nodes.begin(); n < _nodes.end(); n++)
		{
			_map.insert(make_pair((*n)->GetNodeID(), (*n)));
		}
	}
	return _map;
}