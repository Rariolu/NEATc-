#include "GenomeManager.h"

int GenomeManager::id = 0;
map<int, Genome*> GenomeManager::genomes;

int GenomeManager::CreateNewGenome(int inputcount, int outputcount, int memorycount)
{
	//cout << "CreateNewGenome called" << endl;
	int genomeid = id++;
	Genome* genome = new Genome(inputcount, outputcount,memorycount,genomeid);
	genomes.insert(make_pair(genomeid, genome));
	return genomeid;
}

Genome* GenomeManager::GetGenome(int id)
{
	map<int,Genome*>::iterator i = genomes.find(id);
	if (i != genomes.end())
	{
		return i->second;
	}
	return NULL;
}

int GenomeManager::CloneGenome(int genome)
{
	int genomeid = id++;
	return CloneGenome(genome, genomeid);
}

int GenomeManager::CreateGenomeWithID(int inputcount, int outputcount, int memorycount, int genomeid)
{
	if (!GetGenome(genomeid))
	{
		Genome* genome = new Genome(inputcount, outputcount,memorycount, genomeid);
		genomes.insert(make_pair(genomeid, genome));
		IDCheck(genomeid);
		return genomeid;
	}
	ConsoleManager::Output("Genome already existed you pathetic worm!");
	return -1;
}

int GenomeManager::CloneGenome(int genome, int newgenomeid)
{
	//cout << "C++ Clone started" << endl;
	if (!GetGenome(newgenomeid))
	{
		Genome* prevgenome = GetGenome(genome);
		if (prevgenome)
		{
			Genome* clonegenome = prevgenome->Clone(newgenomeid);
			genomes.insert(make_pair(newgenomeid, clonegenome));
			IDCheck(newgenomeid);
			//cout << "C++ Clone ended" << endl;
			return newgenomeid;
		}
	}
	//cout << "C++ Clone ended" << endl;
	return -1;
}

void GenomeManager::IDCheck(int _id)
{
	if (_id > id)
	{
		id = _id + 1;
	}
}

void GenomeManager::RemoveGenome(int id)
{
	Genome* genome = GetGenome(id);
	if (genome)
	{
		for (map<int, Genome*>::iterator i = genomes.begin(); i != genomes.end(); i++)
		{
			if (i->first == id)
			{
				i->second->~Genome();
				genomes.erase(i);
				break;
			}
		}
	}
}

void GenomeManager::InsertGenome(int genomeid, Genome* genome)
{
	if (!GetGenome(genomeid))
	{
		genomes.insert(make_pair(genomeid, genome));
		if (genomeid > id)
		{
			id = genomeid + 1;
		}
	}
	else
	{
		cout << "genome already in that id" << endl;
	}
}

int GenomeManager::Count()
{
	return genomes.size();
}

int GenomeManager::Merge(int genomeA, int genomeB)
{
	return Merge(genomeA, genomeB, id++);
}

int GenomeManager::Merge(int genomeA, int genomeB, int mergeid)
{
	Genome* a = GetGenome(genomeA);
	Genome* b = GetGenome(genomeB);
	if (a && b)
	{
		Genome* a_b = Genome::Merge(a, b, mergeid);
		if (a_b)
		{
			InsertGenome(mergeid, a_b);
			return mergeid;
		}
	}
	return -1;
}

int GenomeManager::GetCommon(int genomeA, int genomeB)
{
	return GetCommon(genomeA, genomeB, id++);
}

int GenomeManager::GetCommon(int genomeA, int genomeB, int mergeid)
{
	Genome* a = GetGenome(genomeA);
	Genome* b = GetGenome(genomeB);
	cout << genomeA << " : " << genomeB << endl;
	bool aexists = a;
	bool bexists = b;
	cout << "A: " << aexists << "; B: " << bexists << endl;
	if (a && b)
	{
		Genome* a_b = Genome::GetGenomeWithCommonProperties(a, b, mergeid);
		if (a_b)
		{
			InsertGenome(mergeid, a_b);
			return mergeid;
		}
	}
	return -1;
}