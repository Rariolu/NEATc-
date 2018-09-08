#include "Node.h"

int Node::nodenum = 0;

Node::Node() : Node(new CSRand())
{
	//ConsoleManager::Output("New Rand in Node.");
	//cout << "New Rand in Node" << endl;
}

Node::Node(CSRand* _rand) : Node(_rand, nodenum++)
{

}

Node::Node(CSRand* _rand,int id)
{
	//cout << "Node constructor started" << endl;
	rand = _rand;
	//cout << "Rand set" << endl;
	//cout << "Node constructor done" << endl;
	nodeid = id;
}

Node::~Node()
{
	if (_inputs.size() > 0)
	{
		for (vector<Link*>::iterator inp = _inputs.begin(); inp < _inputs.end(); inp++)
		{
			if ((*inp) != NULL)
			{
				(*inp)->~Link();
			}
		}
	}
	_inputs.clear();
	if (_outputs.size() > 0)
	{
		for (vector<Link*>::iterator out = _outputs.begin(); out < _outputs.end(); out++)
		{
			if ((*out) != NULL)
			{
				(*out)->~Link();
			}
		}
	}
	_outputs.clear();
}

void Node::RandomiseDistance(double min, double max)
{
	distancefromstart = rand->NextDouble(min+1, max);
	//cout << "Distance set to" << distancefromstart << endl;
}

double Node::GetDistance()
{
	return distancefromstart;
}

void Node::AddInput(Node* othernode)
{
	Link* link = new Link(othernode, this,rand);
	AddInput(link);
	othernode->AddOutput(link);
}

void Node::AddInput(Link* link)
{
	//cout << "Node::AddInput called" << endl;
	_inputs.push_back(link);
}

void Node::AddOutput(Link* link)
{
	//cout << "Node::AddOUtput called" << endl;
	try
	{
		_outputs.push_back(link);
	}
	catch (exception err)
	{
		ConsoleManager::Output(err.what());
		//cout << err.what() << endl;
	}
	//cout << "Node::AddOutput finished" << endl;
}

void Node::AddOutput(Node* othernode)
{
	Link* link = new Link(this, othernode,rand);
	AddOutput(link);
	othernode->AddInput(link);
}

void Node::ResetMemory()
{
	//cout << "Node::ResetMemory() called" << endl;
	memorisedOutput = 0;
	memorised = false;
	//cout << "Node::ResetMemory() ended" << endl;
}

double Node::GetNodeValue(vector<double> inputs)
{
	if (memorised)
	{
		return memorisedOutput;
	}
	if (isInput)
	{
		return Memorise(inputs.at(inputIndex));
	}
	double sum = 0;
	for (vector<Link*>::iterator i = _inputs.begin(); i < _inputs.end(); i++)
	{
		Node* source = (*i)->GetSource();
		if (source != NULL)
		{
			sum += source->GetNodeValue(inputs) * (*i)->GetWeight();
		}
		else
		{
			RemoveInput((*i));
		}
	}
	return Memorise(Operations::Sigmoid(sum));
}

double Node::Memorise(double value)
{
	memorised = true;
	return memorisedOutput = value;
}

void Node::RemoveInput(Link* link)
{
	//TODO: GetInputIterator being annoying, putting its functionality here for now.
	vector<Link*>::iterator i = find(_inputs.begin(),_inputs.end(),link);
	if (i != _inputs.end())
	{
		_inputs.erase(i);
	}
}

void Node::RemoveOutput(Link* link)
{
	//TODO: GetOutputIterator being annoying, putting its functionality here for now.
	vector<Link*>::iterator i = find(_outputs.begin(), _outputs.end(), link);
	if (i != _outputs.end())
	{
		_outputs.erase(i);
	}
}

void Node::RemoveFromGenome()
{
	for (vector<Link*>::iterator i = _inputs.begin(); i < _inputs.end(); i++)
	{
		(*i)->GetSource()->RemoveOutput((*i));
	}
	for (vector<Link*>::iterator i = _outputs.begin(); i < _outputs.end(); i++)
	{
		(*i)->GetDestination()->RemoveInput((*i));
	}
}

void Node::MutateWeight()
{
	//cout << "Weight mutation started" << endl;
	bool inputsexist = _inputs.size() > 0;
	bool outputsexist = _outputs.size() > 0;
	if ((rand->NextBool() || !outputsexist) && inputsexist)
	{
		if (inputsexist)
		{
			int offset = rand->Next(2);
			for (int inputindex = 0; inputindex < _inputs.size()-1; inputindex+=2)
			{
				//int inputindex = rand->Next(_inputs.size());
				_inputs[inputindex+offset]->MutateWeight();
			}
		}
		else
		{
			ConsoleManager::Output("No inputs here mate.");
			//cout << "No inputs here mate." << endl;
		}
	}
	else
	{
		if (outputsexist)
		{
			int outputindex = rand->Next(_outputs.size());
			_outputs[outputindex]->MutateWeight();
		}
		else
		{
			//ConsoleManager::Output("No outputs here mate. InputsExist: " + to_string(inputsexist) + " yabadaba.");
			//cout << "No outputs here mate. InputsExist: "<<inputsexist<<" yabadaba." << endl;
		}
	}
	//cout << "Weight mutation ended" << endl;
}

int Node::GetNodeID()
{
	return nodeid;
}

vector<Node::Link*> Node::GetInputs()
{
	return _inputs;
}

vector<Node::Link*> Node::GetOutputs()
{
	return _outputs;
}

void Node::SetDistance(double d)
{
	distancefromstart = d;
}

bool Node::IsInput()
{
	return isInput;
}

bool Node::IsOutput()
{
	return isOutput;
}

bool Node::IsInputMemoryNode()
{
	return isInputMemoryNode;
}

bool Node::IsOutputMemoryNode()
{
	return isOutputMemoryNode;
}

bool Node::IsMemoryPresentNode()
{
	return isMemoryPresentNode;
}

void Node::RemoveWeakInputs()
{
	if (_inputs.size() > 0)
	{
		vector<Link*> inputstoberemoved;
		for (vector<Link*>::iterator i = _inputs.begin(); i < _inputs.end(); i++)
		{
			if ((*i)->GetWeight() < minweight)
			{
				inputstoberemoved.push_back((*i));
				//i = _inputs.erase(i);
			}
		}
		for (vector<Link*>::iterator i = inputstoberemoved.begin(); i < inputstoberemoved.end(); i++)
		{
			RemoveInput((*i));
			//cout << "Input removed mwuhahaha" << endl;
		}
	}
}

void Node::ImproveStrongInputs()
{
	if (_inputs.size() > 0)
	{
		for (vector<Link*>::iterator i = _inputs.begin(); i < _inputs.end(); i++)
		{
			if ((*i)->GetWeight() >= strongweight)
			{
				(*i)->SetWeight(1);
			}
		}
	}
}

int Node::GetNodeNum()
{
	return nodenum;
}

void Node::CheckNodeNum(int value)
{
	if (nodenum < value)
	{
		nodenum = value + 1;
	}
}

bool Node::HasInput(int nodeid)
{
	if (_inputs.size() > 0)
	{
		for (vector<Link*>::iterator i = _inputs.begin(); i < _inputs.end(); i++)
		{
			Node* source = (*i)->GetSource();
			if (source != NULL)
			{
				if (source->GetNodeID() == nodeid)
				{
					return true;
				}
			}
		}
	}
	return false;
}