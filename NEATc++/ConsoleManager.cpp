#include "ConsoleManager.h"

bool ConsoleManager::actuallyoutput = true;
msgoutput ConsoleManager::outputeventhandler = NULL;

void ConsoleManager::Output(string text)
{
	char* cstr = Operations::StrToCharPointer(text);
	Output(cstr);
	delete[] cstr;
}

void ConsoleManager::Output(char* text)
{
	if (actuallyoutput && outputeventhandler)
	{
		try
		{
			cout << text << endl;
			//outputeventhandler(text);
		}
		catch (exception err)
		{
			cout << err.what() << endl;
			cout << text << endl;
		}
	}
}

void ConsoleManager::Output(int number)
{
	Output(to_string(number));
}

void ConsoleManager::SetActivation(bool active)
{
	actuallyoutput = active;
}

void ConsoleManager::SetOutputEventHandler(msgoutput oeh)
{
	outputeventhandler = oeh;
}