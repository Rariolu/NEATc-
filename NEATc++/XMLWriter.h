#ifndef _XML_WRITER_H

#define _XML_WRITER_H

#include <fstream>
#include"Operations.h"
#include<stack>

using namespace std;

class XMLWriter
{
	public:
		XMLWriter();
		~XMLWriter();
		void Finalise(string filepath);
		void WriteStartDocument();
		
	private:
		string content = "";
		class Element
		{
			public:
				Element()
				{

				}
				~Element()
				{

				}
			private:
				bool oneline = false;
		};
		stack<Element*> elements;
};

#endif