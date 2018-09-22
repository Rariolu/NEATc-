#include "XML_Formatting.h"

const string XML_Formatting::genomeopentag = "<genome>";
const string XML_Formatting::inputsopentag = "<inputs>";
const string XML_Formatting::intermediatesopentag = "<intermediates>";
const string XML_Formatting::outputsopentag = "<outputs>";
const string XML_Formatting::linksopentag = "<links>";

const string XML_Formatting::genomeclosetag = "</genome>";
const string XML_Formatting::inputsclosetag = "</inputs>";
const string XML_Formatting::intermediatesclosetag = "</intermediates>";
const string XML_Formatting::outputsclosetag = "</outputs>";
const string XML_Formatting::linksclosetag = "</links>";

vector<string> XML_Formatting::opentags;
vector<string> XML_Formatting::closetags;

string XML_Formatting::ConvertGenomeToXML(Genome* genome)
{
	int id = genome->ID();

	string content = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";

	content += "<genome>\n";

	content += "\t<ID>" + to_string(id) + "</ID>\n";

	int inputcount = genome->GetInputCount();
	int outputcount = genome->GetOutputCount();

	int ltmemorycount = genome->GetLTMemoryCount();
	int stmemorycount = genome->GetSTMemoryCount();

	content += "\t<InputCount>" + to_string(inputcount) + "</InputCount>\n";

	content += "\t<OutputCount>" + to_string(outputcount) + "</OutputCount>\n";

	content += "\t<STMemoryCount>" + to_string(stmemorycount) + "</STMemoryCount>\n";

	content += "\t<LTMemoryCount>" + to_string(ltmemorycount) + "</LTMemoryCount>\n";

	content += "\t<MemoryPresentNode>"+to_string(genome->GetMemoryPresentNode()->GetNodeID())+"</MemoryPresentNode>\n";

	content += "\t<inputs>\n";

	vector<InputNode*> inputs = genome->GetInputNodes();

	for (vector<InputNode*>::iterator inp = inputs.begin(); inp < inputs.end(); inp++)
	{
		int id = (*inp)->GetNodeID();
		int inputindex = (*inp)->GetInputIndex();
		content += "\t\t<input id=\"" + to_string(id) + "\" inpindex=\"" + to_string(inputindex) + "\"/>\n";
	}

	content += "\t</inputs>\n";

	content += "\t<intermediates>\n";

	vector<Node*> intermediates = genome->GetIntermediateNodes();

	for (vector<Node*>::iterator interim = intermediates.begin(); interim < intermediates.end(); interim++)
	{
		int id = (*interim)->GetNodeID();
		double distance = (*interim)->GetDistance();
		content += "\t\t<intermediate id=\"" + to_string(id) + "\" distance=\"" + to_string(distance) + "\"/>\n";
	}

	content += "\t</intermediates>\n";

	content += "\t<outputs>\n";

	vector<OutputNode*> outputs = genome->GetOutputNodes();

	for (vector<OutputNode*>::iterator output = outputs.begin(); output < outputs.end(); output++)
	{
		int id = (*output)->GetNodeID();
		content += "\t\t<output id=\"" + to_string(id) + "\"/>\n";
	}

	content += "\t</outputs>\n";

	content += "\t<links>\n";

	vector<Node*> nodes = genome->GetNodes();

	for (vector<Node*>::iterator node = nodes.begin(); node < nodes.end(); node++)
	{
		vector<Node::Link*> inputlinks = (*node)->GetInputs();
		if (inputs.size() > 0)
		{
			for (vector<Node::Link*>::iterator inp = inputlinks.begin(); inp < inputlinks.end(); inp++)
			{
				Node* source = (*inp)->GetSource();
				Node* destination = (*inp)->GetDestination();
				double weight = (*inp)->GetWeight();
				if (source != NULL && destination != NULL)
				{
					int s = source->GetNodeID();
					int d = destination->GetNodeID();
					content += "\t\t<link source=\"" + to_string(s) + "\" destination=\"" + to_string(d) + "\" weight=\"" + to_string(weight) + "\"/>\n";
				}
			}
		}
	}

	content += "\t</links>\n";

	content += "</genome>\n";

	return content;
}

void XML_Formatting::SaveGenome(Genome* genome, string filepath)
{
	/*int id = genome->ID();

	string content = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";

	content += "<genome>\n";

	content += "\t<ID>" + to_string(id) + "</ID>\n";

	int inputcount = genome->GetInputCount();
	int outputcount = genome->GetOutputCount();

	content += "\t<InputCount>" + to_string(inputcount) + "</InputCount>\n";

	content += "\t<OutputCount>" + to_string(outputcount) + "</OutputCount>\n";

	content += "\t<inputs>\n";

	vector<InputNode*> inputs = genome->GetInputNodes();

	for (vector<InputNode*>::iterator inp = inputs.begin(); inp < inputs.end(); inp++)
	{
		int id = (*inp)->GetNodeID();
		int inputindex = (*inp)->GetInputIndex();
		content += "\t\t<input id=\"" + to_string(id) + "\" inpindex=\"" + to_string(inputindex) + "\"/>\n";
	}

	content += "\t</inputs>\n";

	content += "\t<intermediates>\n";

	vector<Node*> intermediates = genome->GetIntermediateNodes();

	for (vector<Node*>::iterator interim = intermediates.begin(); interim < intermediates.end(); interim++)
	{
		int id = (*interim)->GetNodeID();
		double distance = (*interim)->GetDistance();
		content += "\t\t<intermediate id=\"" + to_string(id) + "\" distance=\"" + to_string(distance) + "\"/>\n";
	}

	content += "\t</intermediates>\n";

	content += "\t<outputs>\n";

	vector<OutputNode*> outputs = genome->GetOutputNodes();

	for (vector<OutputNode*>::iterator output = outputs.begin(); output < outputs.end(); output++)
	{
		int id = (*output)->GetNodeID();
		content += "\t\t<output id=\"" + to_string(id) + "\"/>\n";
	}

	content += "\t</outputs>\n";

	content += "\t<links>\n";

	vector<Node*> nodes = genome->GetNodes();

	for (vector<Node*>::iterator node = nodes.begin(); node < nodes.end(); node++)
	{
		vector<Node::Link*> inputlinks = (*node)->GetInputs();
		if (inputs.size() > 0)
		{
			for (vector<Node::Link*>::iterator inp = inputlinks.begin(); inp < inputlinks.end(); inp++)
			{
				Node* source = (*inp)->GetSource();
				Node* destination = (*inp)->GetDestination();
				double weight = (*inp)->GetWeight();
				if (source != NULL && destination != NULL)
				{
					int s = source->GetNodeID();
					int d = destination->GetNodeID();
					content += "\t\t<link source=\"" + to_string(s) + "\" destination=\"" + to_string(d) + "\" weight=\"" + to_string(weight) + "\"/>\n";
				}
			}
		}
	}

	content += "\t</links>\n";

	content += "</genome>\n";*/

	string content = ConvertGenomeToXML(genome);
	ofstream file;
	file.open(filepath, ios::out);
	file << content;
	file.close();
	cout << "Saved " << filepath << endl;
}

Genome* XML_Formatting::ParseGenomeDirect(string content)
{
	Genome* genome = NULL;
	stack<string>* elements = new stack<string>();
	istringstream stream(content);
	string line;
	bool idset = false;
	int id;
	bool inpset = false;
	int inputcount;
	bool outset = false;
	int outputcount;

	bool stmemset = false;
	bool ltmemset = false;
	int stmemorycount = 0;
	int ltmemorycount = 0;

	bool memorypresentset = false;
	int memorypresentnodeid;

	vector<ProtoInputNode> protoinputs;
	vector<ProtoIntermediateNode> protointermediates;
	vector<ProtoNode> protooutputs;
	vector<ProtoLink> links;

	map<int, int> memorymappings;

	while (getline(stream, line))
	{
		if (!IsTag(line, elements))
		{
			if (elements->size() > 0)
			{
				if (elements->top() == genomeopentag)
				{
					if (Operations::Contains(line, "<ID>"))
					{
						string num = Operations::GetTextBetween(line, "<ID>", "</ID>");
						IntWrapper* n = new IntWrapper();
						if (Operations::TryParse(num, n))
						{
							//cout << "ID: " << n->Number << endl;
							id = n->Number;
							idset = true;
						}
					}
					if (Operations::Contains(line, "<InputCount>"))
					{
						string inpcount = Operations::GetTextBetween(line, "<InputCount>", "</InputCount>");
						IntWrapper* n = new IntWrapper();
						if (Operations::TryParse(inpcount, n))
						{
							//cout << "InputCount: " << n->Number << endl;
							inputcount = n->Number;
							inpset = true;
						}
						n->~IntWrapper();
					}
					if (Operations::Contains(line, "<OutputCount>"))
					{
						string outcount = Operations::GetTextBetween(line, "<OutputCount>", "</OutputCount>");
						IntWrapper* n = new IntWrapper();
						if (Operations::TryParse(outcount, n))
						{
							//cout << "OutputCount: " << n->Number << endl;
							outputcount = n->Number;
							outset = true;
						}
						n->~IntWrapper();
					}

					if (Operations::Contains(line, "<STMemoryCount>"))
					{
						string memcount = Operations::GetTextBetween(line, "<STMemoryCount>", "</STMemoryCount>");
						IntWrapper* n = new IntWrapper();
						if (Operations::TryParse(memcount,n))
						{
							stmemorycount = n->Number;
							stmemset = true;
						}
						n->~IntWrapper();
					}
					if (Operations::Contains(line, "<LTMemoryCount>"))
					{
						string ltmemcount = Operations::GetTextBetween(line, "<LTMemoryCount>", "</LTMemoryCount>");
						IntWrapper* n = new IntWrapper();
						if (Operations::TryParse(ltmemcount,n))
						{
							ltmemorycount = n->Number;
							ltmemset = true;
						}
					}
					if (Operations::Contains(line, "<MemoryPresentNode>"))
					{
						string memorypresentid = Operations::GetTextBetween(line, "<MemoryPresentNode>", "</MemoryPresentNode>");
						IntWrapper* n = new IntWrapper();
						if (Operations::TryParse(memorypresentid, n))
						{
							memorypresentnodeid = n->Number;
							memorypresentset = true;
						}
						n->~IntWrapper();
					}
				}
				else if (elements->top() == inputsopentag)
				{
					if (Operations::Contains(line, "<input id"))
					{
						string inpid = Operations::GetTextBetween(line, "id=\"", "\" inp");
						IntWrapper* n = new IntWrapper();
						if (Operations::TryParse(inpid, n))
						{
							string inpindex = Operations::GetTextBetween(line, "inpindex=\"", "\"/>");
							IntWrapper* nn = new IntWrapper();
							if (Operations::TryParse(inpindex, nn))
							{
								ProtoInputNode protoinput(n->Number, nn->Number);
								protoinputs.push_back(protoinput);
							}
						}
					}
				}
				else if (elements->top() == intermediatesopentag)
				{
					if (Operations::Contains(line, "<intermediate id"))
					{
						string interid = Operations::GetTextBetween(line, "id=\"", "\" distance");
						IntWrapper* n = new IntWrapper();
						if (Operations::TryParse(interid, n))
						{
							string distance = Operations::GetTextBetween(line, "distance=\"", "\"/>");
							DoubleWrapper* d = new DoubleWrapper();
							if (Operations::DoubleTryParse(distance, d))
							{
								ProtoIntermediateNode protointermediate(n->Number, d->Number);
								protointermediates.push_back(protointermediate);
							}
						}
					}
				}
				else if (elements->top() == outputsopentag)
				{
					if (Operations::Contains(line, "<output id"))
					{
						string outid = Operations::GetTextBetween(line, "id=\"", "\"/>");
						IntWrapper* n = new IntWrapper();
						if (Operations::TryParse(outid, n))
						{
							ProtoNode protooutput(n->Number);
							protooutputs.push_back(protooutput);
						}
					}
				}
				else if (elements->top() == linksopentag)
				{
					if (Operations::Contains(line, "<link source"))
					{
						string surce = Operations::GetTextBetween(line, "source=\"", "\" dest");
						IntWrapper* s = new IntWrapper();
						if (Operations::TryParse(surce, s))
						{
							string dstination = Operations::GetTextBetween(line, "destination=\"", "\" weight");
							IntWrapper* d = new IntWrapper();
							if (Operations::TryParse(dstination, d))
							{
								string wight = Operations::GetTextBetween(line, "weight=\"", "\"/>");
								DoubleWrapper* w = new DoubleWrapper();
								if (Operations::DoubleTryParse(wight, w))
								{
									ProtoLink protolink(s->Number, d->Number, w->Number);
									links.push_back(protolink);
								}
							}
						}
					}
				}
			}
		}
	}
	if (idset && inpset && outset)
	{
		if (!GenomeManager::GetGenome(id))
		{
			CSRand* rand = new CSRand(id + Operations::RandomNumber(1, 11));

			vector<InputNode*> inputs;
			vector<OutputNode*> outputs;
			vector<Node*> allnodes;
			vector<Node*> intermediates;

			vector<InputMemoryNode*> inputmemorynodes;
			vector<OutputMemoryNode*> outputmemorynodes;

			MemoryPresentNode* memorypresentnode = new MemoryPresentNode(memorypresentnodeid,stmemorycount > 0 && ltmemorycount > 0);

			map<int, Node*> nodedict;
			
			for (int i = 0; i < protoinputs.size(); i++)
			{
				ProtoInputNode pinp = protoinputs[i];
				InputNode* inp = new InputNode(pinp.Index(), rand, pinp.urgh());
				inputs.push_back(inp);
				allnodes.push_back(inp);
				nodedict.insert(make_pair(pinp.urgh(), inp));
				Node::CheckNodeNum(pinp.urgh());
			}
			for (int i = 0; i < protointermediates.size(); i++)
			{
				ProtoIntermediateNode pintp = protointermediates[i];
				Node* intermediate = new Node(rand, pintp.urgh());
				intermediate->SetDistance(pintp.Distance());
				intermediates.push_back(intermediate);
				allnodes.push_back(intermediate);
				nodedict.insert(make_pair(pintp.urgh(), intermediate));
				Node::CheckNodeNum(pintp.urgh());
			}
			for (int i = 0; i < protooutputs.size(); i++)
			{
				ProtoNode poutp = protooutputs[i];
				OutputNode* output = new OutputNode(rand, poutp.ID());
				outputs.push_back(output);
				allnodes.push_back(output);
				nodedict.insert(make_pair(poutp.ID(), output));
				Node::CheckNodeNum(poutp.ID());
			}
			for (int i = 0; i < links.size(); i++)
			{
				ProtoLink protolink = links[i];
				int source = protolink.Source();
				int destination = protolink.Destination();
				double weight = protolink.Weight();
				map<int, Node*>::iterator s = nodedict.find(source);
				map<int, Node*>::iterator d = nodedict.find(destination);
				if (s != nodedict.end() && d != nodedict.end())
				{
					Node* sourcen = s->second;
					Node* dest = d->second;
					if (sourcen != NULL && dest != NULL)
					{
						Node::Link* link = new Node::Link(sourcen, dest, rand, weight);
						sourcen->AddOutput(link);
						dest->AddInput(link);
					}
					else
					{
						cout << "One of them wasn't swell." << endl;
					}
				}
				else
				{
					cout << "What the actual fuck? " << endl;
				}
			}
			genome = new Genome(inputcount, outputcount,stmemorycount,ltmemorycount, id);
			genome->SetNodes(allnodes, inputs, outputs, intermediates, inputmemorynodes, outputmemorynodes,memorypresentnode);
			genome->SetRand(rand);
			//GenomeManager::InsertGenome(id, genome);
		}
	}
	return genome;
}

Genome* XML_Formatting::ParseGenome(string filepath)
{
	string content = ReadFile(filepath);
	Genome* genome = ParseGenomeDirect(content);
	if (genome)
	{
		GenomeManager::InsertGenome(genome->ID(), genome);
	}
	return genome;
	//Genome* genome = NULL;
	//stack<string>* elements = new stack<string>();
	//istringstream stream(content);
	//string line;
	//bool idset = false;
	//int id;
	//bool inpset = false;
	//int inputcount;
	//bool outset = false;
	//int outputcount;
	//vector<ProtoInputNode> protoinputs;
	//vector<ProtoIntermediateNode> protointermediates;
	//vector<ProtoNode> protooutputs;
	//vector<ProtoLink> links;
	//while (getline(stream, line))
	//{
	//	if (!IsTag(line, elements))
	//	{
	//		if (elements->size() > 0)
	//		{
	//			if (elements->top() == genomeopentag)
	//			{
	//				if (Operations::Contains(line, "<ID>"))
	//				{
	//					string num = Operations::GetTextBetween(line, "<ID>", "</ID>");
	//					IntWrapper* n = new IntWrapper();
	//					if (Operations::TryParse(num, n))
	//					{
	//						//cout << "ID: " << n->Number << endl;
	//						id = n->Number;
	//						idset = true;
	//					}
	//				}
	//				if (Operations::Contains(line, "<InputCount>"))
	//				{
	//					string inpcount = Operations::GetTextBetween(line, "<InputCount>", "</InputCount>");
	//					IntWrapper* n = new IntWrapper();
	//					if (Operations::TryParse(inpcount, n))
	//					{
	//						//cout << "InputCount: " << n->Number << endl;
	//						inputcount = n->Number;
	//						inpset = true;
	//					}
	//				}
	//				if (Operations::Contains(line, "<OutputCount>"))
	//				{
	//					string outcount = Operations::GetTextBetween(line, "<OutputCount>", "</OutputCount>");
	//					IntWrapper* n = new IntWrapper();
	//					if (Operations::TryParse(outcount, n))
	//					{
	//						//cout << "OutputCount: " << n->Number << endl;
	//						outputcount = n->Number;
	//						outset = true;
	//					}
	//				}
	//			}
	//			else if (elements->top() == inputsopentag)
	//			{
	//				if (Operations::Contains(line, "<input id"))
	//				{
	//					string inpid = Operations::GetTextBetween(line, "id=\"", "\" inp");
	//					IntWrapper* n = new IntWrapper();
	//					if (Operations::TryParse(inpid, n))
	//					{
	//						string inpindex = Operations::GetTextBetween(line, "inpindex=\"", "\"/>");
	//						IntWrapper* nn = new IntWrapper();
	//						if (Operations::TryParse(inpindex, nn))
	//						{
	//							ProtoInputNode protoinput(n->Number, nn->Number);
	//							protoinputs.push_back(protoinput);
	//						}
	//					}
	//				}
	//			}
	//			else if (elements->top() == intermediatesopentag)
	//			{
	//				if (Operations::Contains(line, "<intermediate id"))
	//				{
	//					string interid = Operations::GetTextBetween(line, "id=\"", "\" distance");
	//					IntWrapper* n = new IntWrapper();
	//					if (Operations::TryParse(interid, n))
	//					{
	//						string distance = Operations::GetTextBetween(line, "distance=\"", "\"/>");
	//						DoubleWrapper* d = new DoubleWrapper();
	//						if (Operations::DoubleTryParse(distance, d))
	//						{
	//							ProtoIntermediateNode protointermediate(n->Number, d->Number);
	//							protointermediates.push_back(protointermediate);
	//						}
	//					}
	//				}
	//			}
	//			else if (elements->top() == outputsopentag)
	//			{
	//				if (Operations::Contains(line, "<output id"))
	//				{
	//					string outid = Operations::GetTextBetween(line, "id=\"", "\"/>");
	//					IntWrapper* n = new IntWrapper();
	//					if (Operations::TryParse(outid, n))
	//					{
	//						ProtoNode protooutput(n->Number);
	//						protooutputs.push_back(protooutput);
	//					}
	//				}
	//			}
	//			else if (elements->top() == linksopentag)
	//			{
	//				if (Operations::Contains(line, "<link source"))
	//				{
	//					string surce = Operations::GetTextBetween(line, "source=\"", "\" dest");
	//					IntWrapper* s = new IntWrapper();
	//					if (Operations::TryParse(surce, s))
	//					{
	//						string dstination = Operations::GetTextBetween(line, "destination=\"", "\" weight");
	//						IntWrapper* d = new IntWrapper();
	//						if (Operations::TryParse(dstination, d))
	//						{
	//							string wight = Operations::GetTextBetween(line, "weight=\"", "\"/>");
	//							DoubleWrapper* w = new DoubleWrapper();
	//							if (Operations::DoubleTryParse(wight, w))
	//							{
	//								ProtoLink protolink(s->Number, d->Number, w->Number);
	//								links.push_back(protolink);
	//							}
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
	//if (idset && inpset && outset)
	//{
	//	if (!GenomeManager::GetGenome(id))
	//	{
	//		vector<InputNode*> inputs;
	//		vector<OutputNode*> outputs;
	//		vector<Node*> allnodes;
	//		vector<Node*> intermediates;
	//		map<int, Node*> nodedict;
	//		CSRand* rand = new CSRand(id + Operations::RandomNumber(1, 11));
	//		for (int i = 0; i < protoinputs.size(); i++)
	//		{
	//			ProtoInputNode pinp = protoinputs[i];
	//			InputNode* inp = new InputNode(pinp.Index(), rand, pinp.urgh());
	//			inputs.push_back(inp);
	//			allnodes.push_back(inp);
	//			nodedict.insert(make_pair(pinp.urgh(), inp));
	//			Node::CheckNodeNum(pinp.urgh());
	//		}
	//		for (int i = 0; i < protointermediates.size(); i++)
	//		{
	//			ProtoIntermediateNode pintp = protointermediates[i];
	//			Node* intermediate = new Node(rand, pintp.urgh());
	//			intermediate->SetDistance(pintp.Distance());
	//			intermediates.push_back(intermediate);
	//			allnodes.push_back(intermediate);
	//			nodedict.insert(make_pair(pintp.urgh(), intermediate));
	//			Node::CheckNodeNum(pintp.urgh());
	//		}
	//		for (int i = 0; i < protooutputs.size(); i++)
	//		{
	//			ProtoNode poutp = protooutputs[i];
	//			OutputNode* output = new OutputNode(rand, poutp.ID());
	//			outputs.push_back(output);
	//			allnodes.push_back(output);
	//			nodedict.insert(make_pair(poutp.ID(), output));
	//			Node::CheckNodeNum(poutp.ID());
	//		}
	//		for (int i = 0; i < links.size(); i++)
	//		{
	//			ProtoLink protolink = links[i];
	//			int source = protolink.Source();
	//			int destination = protolink.Destination();
	//			double weight = protolink.Weight();
	//			map<int, Node*>::iterator s = nodedict.find(source);
	//			map<int, Node*>::iterator d = nodedict.find(destination);
	//			if (s != nodedict.end() && d != nodedict.end())
	//			{
	//				Node* sourcen = s->second;
	//				Node* dest = d->second;
	//				if (sourcen != NULL && dest != NULL)
	//				{
	//					Node::Link* link = new Node::Link(sourcen, dest, rand,weight);
	//					sourcen->AddOutput(link);
	//					dest->AddInput(link);
	//				}
	//				else
	//				{
	//					cout << "One of them wasn't swell." << endl;
	//				}
	//			}
	//			else
	//			{
	//				cout << "What the actual fuck? " << endl;
	//			}
	//		}
	//		genome = new Genome(inputcount, outputcount, id);
	//		genome->SetNodes(allnodes, inputs, outputs, intermediates);
	//		genome->SetRand(rand);
	//		GenomeManager::InsertGenome(id, genome);
	//	}
	//}
	//return genome;
}

string XML_Formatting::ReadFile(string filepath)
{
	//https://stackoverflow.com/questions/2912520/read-file-contents-into-a-string-in-c
	ifstream ifs(filepath);
	string content((std::istreambuf_iterator<char>(ifs)),(std::istreambuf_iterator<char>()));
	ifs.close();
	return content;
}

bool XML_Formatting::IsTag(string text, stack<string>* elementsstack)
{
	vector<string> opentags = OpenTags();
	for (vector<string>::iterator opentag = opentags.begin(); opentag < opentags.end(); opentag++)
	{
		if (Operations::Contains(text, (*opentag)))
		{
			elementsstack->push((*opentag));
			return true;
		}
	}
	vector<string> closetags = CloseTags();
	for (vector<string>::iterator closetag = closetags.begin(); closetag < closetags.end(); closetag++)
	{
		if (Operations::Contains(text, (*closetag)))
		{
			string opname = GetNameFromTag(elementsstack->top(), OPEN);
			string closname = GetNameFromTag((*closetag), CLOSE);
			if (opname == closname)
			{
				elementsstack->pop();
			}
			return true;
		}
	}
	return false;
}

string XML_Formatting::GetNameFromTag(string tag, TagType tagtype)
{
	string op = tagtype == OPEN ? "<" : "</";
	string t = "";
	if (!(Operations::Contains(tag, op) && Operations::Contains(tag, ">")))
	{
		t = tag.substr(tagtype, tag.length() - 1);
	}
	return t;
}

vector<string> XML_Formatting::OpenTags()
{
	if (opentags.size() < 1)
	{
		opentags.push_back(genomeopentag);
		opentags.push_back(inputsopentag);
		opentags.push_back(intermediatesopentag);
		opentags.push_back(outputsopentag);
		opentags.push_back(linksopentag);
	}
	return opentags;
}

vector<string> XML_Formatting::CloseTags()
{
	if (closetags.size() < 1)
	{
		closetags.push_back(genomeclosetag);
		closetags.push_back(inputsclosetag);
		closetags.push_back(intermediatesclosetag);
		closetags.push_back(outputsclosetag);
		closetags.push_back(linksclosetag);
	}
	return closetags;
}