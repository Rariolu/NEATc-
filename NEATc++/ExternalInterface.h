#ifndef _EXTERNAL_INTERFACE_H
#define _EXTERNAL_INTERFACE_H


//#include <iostream>
#include<Windows.h>
#include"URGH.h"
#include"Operations.h"
#include"GenomeManager.h"
#include"CSRand.h"
#include"XML_Formatting.h"

using namespace std;



extern "C"
{
	/*typedef void(__stdcall *PFN_MYCALLBACK)();
	int __stdcall TestDelegate(PFN_MYCALLBACK callback);*/

	XI_EXPORT void TestPrint(msgoutput output);
	XI_EXPORT int TestDLL();

	XI_EXPORT void Initialise();
	XI_EXPORT void SetNum(int num);
	XI_EXPORT int GetNum();
	XI_EXPORT double RANDOUBLE();

	XI_EXPORT bool GenomeExists(int id);
	XI_EXPORT int CreateNewGenome(int inputcount, int outputcount, int memorycount);
	XI_EXPORT double GetOutputFromGenome(int genome, int inputcount, double* inputs, int outputnum);
	XI_EXPORT void ResetMemory(int genomeid);
	XI_EXPORT void Mutate(int genomeid, int iterations);
	XI_EXPORT int CloneGenome(int genome);
	XI_EXPORT int CreateGenomeWithID(int inputcount, int outputcount, int memorycount, int genomeid);
	XI_EXPORT int CloneGenomeWithID(int genome, int newgenomeid);
	XI_EXPORT void RemoveGenome(int id);
	XI_EXPORT void SaveGenome(int id, char* filepath);
	XI_EXPORT bool ParseGenome(char* filepath);
	//XI_EXPORT int Merge(int genomeA, int genomeB);
	//XI_EXPORT int GetCommon(int genomeA, int genomeB);

	XI_EXPORT void SetConsoleActivation(bool active);
	XI_EXPORT void SetOutputEventHandler(msgoutput output);
}

#endif