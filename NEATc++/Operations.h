#ifndef _OPERATIONS_H
#define _OPERATIONS_H

#include <stdlib.h> /* srand, rand */
#include <time.h>   
#include <math.h>
#include<map>
#include"CSRand.h"
#include"ConsoleManager.h"
#include"IntWrapper.h"
#include"DoubleWrapper.h"

using namespace std;

class Operations
{
	public:
		//This version is kinda shitty but it'll do for now. Remember to delete pointer afterwards.
		static char* StrToCharPointer(string text);
		static double RandomDouble();
		static double RandomDouble(double min, double max);
		static double Sigmoid(double val);
		static double ReverseSigmoid(double val);
		static int RandomNumber(int min, int max);
		static bool Contains(string ogText, string excerpt);
		static int GetIndexOFbefore(string ogText, string excerpt);
		static int GetIndexOFafter(string ogText, string excerpt);
		static string GetTextBetween(string ogText, string a, string b);
		static bool TryParse(string text, IntWrapper* number);
		static bool DoubleTryParse(string text, DoubleWrapper* number);
		static bool IsNumber(char c);
		static vector<double> GetVectorFromPointerThingy(double* values, int length);
		static int num;
		static CSRand* randd;
		static map<char, int> nums;
		

	private:

};

#endif