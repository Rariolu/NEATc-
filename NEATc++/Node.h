#ifndef _NODE_H
#define _NODE_H

#include<iostream>
#include "Operations.h"
#include<vector>
#include"CSRand.h"

using namespace std;

class Node
{
	public:
		class Link
		{
			public:
				Link(Node* source, Node* destination) : Link(source, destination, new CSRand())
				{
					ConsoleManager::Output("New Rand in Link");
				}
				Link(Node* source, Node* destination, CSRand* _rand)
				{
					_source = source;
					_destination = destination;
					weight = _rand->NextDouble();
					rand = _rand;
				};
				Link(Node* source, Node* destination, CSRand* _rand, double _weight)
				{
					try
					{
						_source = source;
						_destination = destination;
						rand = _rand;
						weight = _weight;
					}
					catch (exception err)
					{
						ConsoleManager::Output(err.what());
					}
				}
				~Link()
				{

				}
				Node* GetDestination()
				{
					return _destination;
				}
				Node* GetSource()
				{
					return _source;
				}
				double GetWeight()
				{
					return weight;
				}
				void MutateWeight()
				{
					double weightacc = rand->NextWeight();
					while (weight + weightacc > 1 || weight + weightacc < 0)
					{
						weightacc *= 0.1;
					}
					weight += weightacc;
				}
				void SetWeight(double val)
				{
					weight = val;
				}
				Link* GetClone()
				{
					if (_source->GetClone() && _destination->GetClone())
					{
						return new Link(_source->GetClone(), _destination->GetClone(), rand, weight);
					}
					return NULL;
				}
			private:
				Node * _source;
				Node* _destination;
				double weight;
				CSRand* rand;
			};
			Node();
			Node(CSRand* _rand);
			Node(CSRand* _rand, int id);
			~Node();
			void AddInput(Node* node);
			void AddInput(Link* link);
			void AddOutput(Node* node);
			void AddOutput(Link* link);
			virtual double GetNodeValue(vector<double> inputs);
			void ResetMemory();
			void RemoveInput(Link* link);
			void RemoveInput(int index);
			void RemoveOutput(Link* link);
			void RemoveOutput(int index);
			void RemoveFromGenome();
			void RandomiseDistance(double min, double max);
			double GetDistance();
			void MutateWeight();
			int GetNodeID();
			vector<Link*> GetInputs();
			vector<Link*> GetOutputs();
			void SetDistance(double d);
			bool IsInput();
			bool IsOutput();

			bool IsInputMemoryNode();
			bool IsOutputMemoryNode();
			bool IsMemoryPresentNode();

			void RemoveWeakInputs();
			void ImproveStrongInputs();
			static int GetNodeNum();
			static void CheckNodeNum(int value);
			bool HasInput(int nodeid);

			Node* GetClone();
			virtual void CreateClone();
		protected:
			bool isInput = false;
			bool isOutput = false;
			bool isInputMemoryNode = false;
			bool isOutputMemoryNode = false;
			bool isMemoryPresentNode = false;
			int inputIndex = 0;
			double distancefromstart;
			CSRand* rand;
			static int nodenum;

			Node* _clone;
		private:
			vector<Link*> _inputs;
			vector<Link*> _outputs;
			double memorisedOutput;
			bool memorised = false;
			double Memorise(double value);
			
			int nodeid;
			double minweight = 0.0001;
			double strongweight = 0.998;
			

			vector<Link*>* links;
};

#endif