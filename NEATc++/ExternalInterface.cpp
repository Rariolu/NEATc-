#include "ExternalInterface.h"

int Operations::num = 9;
CSRand* Operations::randd = new CSRand();

void TestPrint(msgoutput output)
{
	if (output)
	{
		output((char*)"KYS");
	}
}

int TestDLL()
{
	return 5;
}

void Initialise()
{
	//Seed the random number generator
	srand(time(NULL));
}

void SetNum(int num)
{
	Operations::num = num;
}

int GetNum()
{
	return Operations::num;
}

double RANDOUBLE()
{
	return Operations::randd->NextDouble(0, 10);
}

bool GenomeExists(int id)
{
	return GenomeManager::GetGenome(id);
}

//int CreateNewGenome(int inputcount, int outputcount, int memorycount)
//{
//	return CreateNewGenome(inputcount, outputcount, memorycount, memorycount);
//	//return GenomeManager::CreateNewGenome(inputcount, outputcount,memorycount);
//}

int CreateNewGenome(int inputcount, int outputcount, int ltmemorycount, int stmemorycount)
{
	return GenomeManager::CreateNewGenome(inputcount, outputcount, ltmemorycount, stmemorycount);
}

double GetOutputFromGenome(int genome,int inputcount, double* inputs, int outputnum)
{
	Genome* g = GenomeManager::GetGenome(genome);
	if (!g)
	{
		return 0;
	}
	vector<double> vinputs = Operations::GetVectorFromPointerThingy(inputs,inputcount);
	//for (int i = 0; i < inputcount; i++)
	//{
	//	vinputs.push_back(inputs[i]);
	//}
	return g->GetOutput(vinputs, outputnum);
}

void ResetMemory(int genomeid)
{
	Genome* genome = GenomeManager::GetGenome(genomeid);
	if (genome)
	{
		genome->ResetMemory();
	}
}

void Mutate(int genomeid, int iterations)
{
	Genome* genome = GenomeManager::GetGenome(genomeid);
	if (genome)
	{
		genome->Mutate(iterations);
	}
}

int CloneGenome(int genome)
{
	return GenomeManager::CloneGenome(genome);
}

//int CreateGenomeWithID(int inputcount, int outputcount,int memorycount, int genomeid)
//{
//	return GenomeManager::CreateGenomeWithID(inputcount, outputcount, memorycount,genomeid);
//}

int CreateGenomeWithID(int inputcount, int outputcount, int ltmemorycount, int stmemorycount, int genomeid)
{
	return GenomeManager::CreateGenomeWithID(inputcount, outputcount, ltmemorycount, stmemorycount, genomeid);
}

int CloneGenomeWithID(int genome, int newgenomeid)
{
	return GenomeManager::CloneGenome(genome, newgenomeid);
}

void RemoveGenome(int id)
{
	GenomeManager::RemoveGenome(id);
}

void SaveGenome(int id, char* filepath)
{
	Genome* genome = GenomeManager::GetGenome(id);
	if (genome)
	{
		XML_Formatting::SaveGenome(genome, string(filepath));
	}
}

bool ParseGenome(char* filepath)
{
	string file = string(filepath);
	Genome* genome = XML_Formatting::ParseGenome(file);
	return genome;
}

void SetConsoleActivation(bool active)
{
	ConsoleManager::SetActivation(active);
}

void SetOutputEventHandler(msgoutput output)
{
	ConsoleManager::SetOutputEventHandler(output);
}

//int Merge(int genomeA, int genomeB)
//{
//	return GenomeManager::Merge(genomeA, genomeB);
//}
//
//int GetCommon(int genomeA, int genomeB)
//{
//	return GenomeManager::GetCommon(genomeA, genomeB);
//}