#include "XMLWriter.h"

XMLWriter::XMLWriter()
{

}

XMLWriter::~XMLWriter()
{

}

void XMLWriter::Finalise(string filepath)
{
	ofstream file;
	file.open(filepath, ios::out | ios::app);
	file << content;
	file.close();
}

void XMLWriter::WriteStartDocument()
{
	content += "<?xml version=\"1.0\" encoding=\"utf - 8\"?>\n";
}