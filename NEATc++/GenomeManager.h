#ifndef  _GENOME_MANAGER_H
#define _GENOME_MANAGER_H

#include<iostream>
#include<map>
#include"Genome.h"

using namespace std;

class GenomeManager
{
	public:
		static int CreateNewGenome(int inputcount, int outputcount, int memorycount);
		static int CreateGenomeWithID(int inputcount, int outputcount,int memorycount, int genomeid);
		static Genome* GetGenome(int id);
		static int CloneGenome(int genome);
		static int CloneGenome(int genome, int newgenomeid);
		static void IDCheck(int _id);
		static void RemoveGenome(int id);
		static void InsertGenome(int id, Genome* genome);
		static int Count();
		static int Merge(int genomeA, int genomeB);
		static int Merge(int genomeA, int genomeB, int mergeid);
		static int GetCommon(int genomeA, int genomeB);
		static int GetCommon(int genomeA, int genomeB, int mergeid);
	private:
		static int id;
		static map<int, Genome*> genomes;
};

#endif // ! _GENOME_MANAGER_H
