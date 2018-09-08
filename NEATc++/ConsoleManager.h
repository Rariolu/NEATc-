#ifndef _CONSOLE_MANAGER_H
#define _CONSOLE_MANAGER_H

#include<iostream>
#include<string>
#include<vector>
#include"Operations.h"

using namespace std;

extern "C"
{
	typedef void(__stdcall* msgoutput)(char* text);
}

class ConsoleManager
{
	public:
		static void Output(string text);
		static void Output(char* text);
		static void Output(int number);
		static void SetActivation(bool active);
		static void SetOutputEventHandler(msgoutput oeh);
	private:
		static bool actuallyoutput;
		static msgoutput outputeventhandler;
};

#endif