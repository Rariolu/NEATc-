#ifndef _XML_FORMATTING_H

#define _XML_FORMATTING_H

#include <fstream>
#include <sstream>
#include <stack>
#include"Genome.h"
#include"GenomeManager.h"

enum TagType
{
	OPEN, CLOSE
};

class XML_Formatting
{
	public:
		static void SaveGenome(Genome* genome, string filepath);
		static string ConvertGenomeToXML(Genome* genome);
		static Genome* ParseGenome(string filepath);
		static Genome* ParseGenomeDirect(string content);
		static string ReadFile(string filepath);
	private:
		static const string genomeopentag;
		static const string genomeclosetag;
		static const string inputsopentag;
		static const string inputsclosetag;
		static const string intermediatesopentag;
		static const string intermediatesclosetag;
		static const string outputsopentag;
		static const string outputsclosetag;
		static const string linksopentag;
		static const string linksclosetag;
		static bool IsTag(string text,stack<string>* elementsstack);
		static vector<string> opentags;
		static vector<string> closetags;
		static vector<string> OpenTags();
		static vector<string> CloseTags();
		static string GetNameFromTag(string tag,TagType tagtype);
		class ProtoNode
		{
			public:
				ProtoNode(int id)
				{
					_nodeid = id;
				}
				int ID()
				{
					return _nodeid;
				}
			private:
				int _nodeid;
		};
		class ProtoInputNode : ProtoNode
		{
			public:
				ProtoInputNode(int id, int index) : ProtoNode(id)
				{
					_inputindex = index;
				}
				int urgh()
				{
					return ID();
				}
				int Index()
				{
					return _inputindex;
				}
			private:
				int _inputindex;
		};
		class ProtoIntermediateNode : ProtoNode
		{
			public:
				ProtoIntermediateNode(int id, double distance) : ProtoNode(id)
				{
					_distance = distance;
				};
				int urgh()
				{
					return ID();
				}
				double Distance()
				{
					return _distance;
				}
			private:
				double _distance;
		};
		class ProtoLink
		{
			public:
				ProtoLink(int source, int destination, double weight)
				{
					_source = source;
					_destination = destination;
					_weight = weight;
				}
				int Source()
				{
					return _source;
				}
				int Destination()
				{
					return _destination;
				}
				double Weight()
				{
					return _weight;
				}
			private:
				int _source;
				int _destination;
				double _weight;
		};
};

#endif