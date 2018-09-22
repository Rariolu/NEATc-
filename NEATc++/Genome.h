#ifndef _GENOME_H
#define _GENOME_H

#include"InputNode.h"
#include"OutputNode.h"
#include"InputMemoryNode.h"
#include"OutputMemoryNode.h"
#include"MemoryPresentNode.h"
//#include"NodeHeaders.h"
#include<map>

using namespace std;

class Genome
{
	public:
		Genome(int inputcount, int outputcount);
		Genome(int inputcount, int outputcount, int randseed);
		Genome(int inputcount, int outputcount, int memorycount, int randseed);
		Genome(int inputcount, int outputcount, int stmcount, int ltmcount, int randseed);
		~Genome();
		double GetOutput(vector<double> inputs, int outputnum);
		void ResetMemory();
		void Mutate(int iterations);
		CSRand* GetRand();
		int GetInputCount();
		int GetOutputCount();

		int GetLTMemoryCount();
		int GetSTMemoryCount();

		void SetNodes(vector<Node*> allnodes, vector<InputNode*> inputnodes, vector<OutputNode*> outputnodes, vector<Node*> intermediatenodes, vector<InputMemoryNode*> inputmemorynodes, vector<OutputMemoryNode*> outputmemorynodes, MemoryPresentNode* memorypresentnode);
		vector<InputNode*> GetInputNodes();
		vector<Node*> GetIntermediateNodes();
		vector<OutputNode*> GetOutputNodes();

		vector<InputMemoryNode*> GetInputMemoryNodes();
		vector<OutputMemoryNode*> GetOutputMemoryNodes();

		MemoryPresentNode* GetMemoryPresentNode();

		vector<Node*> GetNodes();
		void SetRand(CSRand* _rand);
		Genome* Clone(int genomeid);
		int ID();
		static Genome* Merge(Genome* a, Genome* b, int mergeid);
		static Genome* GetGenomeWithCommonProperties(Genome* a, Genome* b, int mergeid);
		void Train(vector<double> inputs, vector<double> outputs);
		map<int, Node*> GetNodeMap();
	private:
		int _id;
		vector<Node*> _nodes;
		vector<InputNode*> _inputnodes;
		vector<OutputNode*> _outputnodes;
		vector<Node*> _intermediatenodes;

		vector<OutputMemoryNode*> _outputmemorynodes;
		vector<InputMemoryNode*> _inputmemorynodes;
		MemoryPresentNode* _memorypresentnode;

		vector<OutputMemoryNode*> _stoutputmemorynodes;
		vector<InputMemoryNode*> _stinputmemorynodes;

		vector<Node::Link*>* links;

		CSRand* rand;
		double WeightMutation = 0.8;
		double LinkMutation = 0.15;
		double Adjustment = 0.4;
		double NodeMutation = 0.1;
		double metamutation = 0.1;
		double metametamutation = 0.05;
		int InputCount;
		int OutputCount;

		int STMemoryCount;
		int LTMemoryCount;

		double MetaMutate(double value);
		void AddNode(Node* prevnode, Node* nextnode);
		void RemoveNode(Node* node);
		vector<Node*>::iterator GetNodeIterator(Node* node);
		vector<Node*>::iterator GetIntermediateNodeIterator(Node* node);
		int GetRandomNodeIndex();
		int GetRandomNodeIndex(int ignoredindex,int ignoreddistance);
};

#endif