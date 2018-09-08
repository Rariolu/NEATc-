using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
//using System.Threading.Tasks;
using System.Xml;
using System.Xml.Serialization;

namespace NEATc__Interpreter
{
    public static class XML_Formatting
    {
        //public static void SaveGenome(this Genome genome, string filepath)
        //{
        //    filepath = filepath.EndsWith(".xml") ? filepath : filepath + ".xml";
        //    XmlWriterSettings settings = new XmlWriterSettings
        //    {
        //        Indent = true,
        //        IndentChars = "\t"
        //    };
        //    XmlWriter xmlwriter = XmlWriter.Create(filepath,settings);
        //    xmlwriter.WriteStartDocument();
        //    //xmlwriter.WriteStartElement("neatCPP");

        //    xmlwriter.WriteStartElement("genome");

        //    xmlwriter.WriteAttributeString("id", genome.ID.ToString());

        //    xmlwriter.WriteStartElement("Name");
        //    xmlwriter.WriteValue(genome.Name);
        //    xmlwriter.WriteEndElement();

        //    xmlwriter.WriteStartElement("InputCount");
        //    xmlwriter.WriteValue(genome.InputCount);
        //    xmlwriter.WriteEndElement();

        //    xmlwriter.WriteStartElement("OutputCount");
        //    xmlwriter.WriteValue(genome.OutputCount);
        //    xmlwriter.WriteEndElement();



        //    xmlwriter.WriteStartElement("idorder");

        //    for (int i = 0; i < genome.idorder.Count; i++)
        //    {
        //        int id = genome.idorder[i];

        //        int mutationtimes = genome.mutationhistory[id];

        //        xmlwriter.WriteStartElement("genomeid");

        //        xmlwriter.WriteAttributeString("id", id.ToString());

        //        xmlwriter.WriteAttributeString("mutationtimes", mutationtimes.ToString());

        //        xmlwriter.WriteEndElement();
        //    }

        //    //idorder
        //    xmlwriter.WriteEndElement();

        //    //genome
        //    xmlwriter.WriteEndElement();

        //    //neatCPP
        //    //xmlwriter.WriteEndElement();
        //    xmlwriter.WriteEndDocument();
        //    xmlwriter.Close();
        //}
        //public static bool ParseGenome(string filepath, out Genome genome)
        //{
        //    filepath = filepath.EndsWith(".xml") ? filepath : filepath + ".xml";
        //    if (!File.Exists(filepath))
        //    {
        //        genome = null;
        //        return false;
        //    }
        //    ObligatoryCustomDictionary<int, int> mutation = new ObligatoryCustomDictionary<int, int>();
        //    List<int> order = new List<int>();
        //    XmlReader xmlreader = XmlReader.Create(filepath);
        //    int inputcount=0;
        //    int outputcount=0;
        //    string name="";
        //    bool inputset = false;
        //    bool outputset = false;
        //    bool idsset = false;
        //    bool nameset = false;
        //    while(xmlreader.Read())
        //    {
        //        if (xmlreader.IsStartElement("Name"))
        //        {
        //            xmlreader.Read();
        //            name = xmlreader.Value;
        //            nameset = true;
        //        }
        //        if (xmlreader.IsStartElement("InputCount"))
        //        {
        //            xmlreader.Read();
        //            inputcount = int.Parse(xmlreader.Value);
        //            inputset = true;
        //        }
        //        if (xmlreader.IsStartElement("OutputCount"))
        //        {
        //            xmlreader.Read();
        //            outputcount = int.Parse(xmlreader.Value);
        //            outputset = true;
        //        }
        //        if (xmlreader.IsStartElement("idorder"))
        //        {
        //            idsset = true;
        //            XmlReader idorder = xmlreader.ReadSubtree();
        //            while (idorder.Read())
        //            {
        //                if (idorder.IsStartElement("genomeid"))
        //                {
        //                    int id = int.Parse(xmlreader["id"]);
        //                    int mutations = int.Parse(xmlreader["mutationtimes"]);
        //                    mutation.Add(id, mutations);
        //                    order.Add(id);
        //                }
        //            }
        //        }
        //    }
        //    xmlreader.Close();
        //    if (inputset && outputset && idsset)
        //    {
        //        int id = order[0];
        //        if (Genome.CreateGenomeFromID(inputcount,outputcount,id,out genome))
        //        {
        //            int mutations = mutation[id];
        //            genome.Mutate(mutations);
        //            for (int i = 1; i < order.Count; i++)
        //            {
        //                id = order[i];
        //                mutations = mutation[id];
        //                if (Genome.CloneWithID(id, genome, out genome))
        //                {
        //                    genome.Mutate(mutations);
        //                }
        //                else
        //                {
        //                    genome = null;
        //                    return false;
        //                }
        //            }
        //            if (nameset)
        //            {
        //                genome.Name = name;
        //            }
        //            return true;
        //        }

        //    }
        //    genome = null;
        //    return false;
        //}

        public static bool CPP_Parse(string filepath, out int id, out int inputcount, out int outputcount,out int memorycount, out string name)
        {
            id = -1;
            inputcount = -1;
            outputcount = -1;
            memorycount = 0;
            name = String.Empty;
            bool idset = false;
            bool inpset = false;
            bool outset = false;
            bool memset = false;
            Func<bool> done = () =>
            {
                return idset && inpset && outset;
            };
            filepath = filepath.EndsWith(".xml") ? filepath : filepath + ".xml";
            XmlReader xmlreader = XmlReader.Create(filepath);
            while (xmlreader.Read())
            {
                if (xmlreader.IsStartElement("genome"))
                {
                    XmlReader genome = xmlreader.ReadSubtree();
                    while (genome.Read())
                    {
                        if (xmlreader.IsStartElement("Name"))
                        {
                            xmlreader.Read();
                            name = xmlreader.Value;
                        }
                        if (done())
                        {
                            xmlreader.Close();
                            return true;
                        }
                        if (xmlreader.IsStartElement("ID"))
                        {
                            xmlreader.Read();
                            id = int.Parse(xmlreader.Value);
                            idset = true;
                        }
                        if (xmlreader.IsStartElement("InputCount"))
                        {
                            xmlreader.Read();
                            inputcount = int.Parse(xmlreader.Value);
                            inpset = true;
                        }
                        if (xmlreader.IsStartElement("OutputCount"))
                        {
                            xmlreader.Read();
                            outputcount = int.Parse(xmlreader.Value);
                            outset = true;
                        }
                        if (xmlreader.IsStartElement("MemoryCount"))
                        {
                            xmlreader.Read();
                            memorycount = int.Parse(xmlreader.Value);
                            memset = true;
                        }
                    }
                }
            }
            xmlreader.Close();
            return false;
        }
        public static void OptimiseFile(string filepath)
        {
            filepath = filepath.EndsWith(".xml") ? filepath : filepath + ".xml";
            if (!File.Exists(filepath))
            {
                return;
            }
            int inputcount = 0;
            bool inputset = false;
            int outputcount = 0;
            bool outputset = false;

            string name = "GENERICNAME";
            XmlReader xmlreader = XmlReader.Create(filepath);
            int nodeid = 0;
            Dictionary<int, int> oldID_newID = new Dictionary<int, int>();

            Dictionary<int, double> intermediatenodes = new Dictionary<int, double>();

            Dictionary<int, List<Link>> source_Link = new Dictionary<int, List<Link>>();
            while (xmlreader.Read())
            {
                if (xmlreader.IsStartElement("InputCount"))
                {
                    xmlreader.Read();
                    nodeid += inputcount = int.Parse(xmlreader.Value);
                    inputset = true;
                }
                if (xmlreader.IsStartElement("OutputCount"))
                {
                    xmlreader.Read();
                    nodeid += outputcount = int.Parse(xmlreader.Value);
                    outputset = true;
                }
                if (xmlreader.IsStartElement("Name"))
                {
                    xmlreader.Read();
                    name = xmlreader.Value;
                }
                if (xmlreader.IsStartElement("intermediates"))
                {
                    XmlReader intermediates = xmlreader.ReadSubtree();
                    while (intermediates.Read())
                    {
                        if (intermediates.IsStartElement("intermediate"))
                        {
                            int id = int.Parse(intermediates["id"]);
                            double distance = double.Parse(intermediates["distance"]);
                            oldID_newID.Add(id, nodeid++);
                            intermediatenodes.Add(id, distance);
                        }
                    }
                }
                if (xmlreader.IsStartElement("links"))
                {
                    XmlReader links = xmlreader.ReadSubtree();
                    while (links.Read())
                    {
                        if (links.IsStartElement("link"))
                        {
                            int source = int.Parse(links["source"]);
                            int destination = int.Parse(links["destination"]);
                            double weight = double.Parse(links["weight"]);
                            Link link = new Link(source, destination, weight);
                            if (!source_Link.ContainsKey(source))
                            {
                                source_Link.Add(source, new List<Link>());
                            }
                            source_Link[source].Add(link);
                        }
                    }
                }
            }
            xmlreader.Close();
            for (int i = 0; i < inputcount + outputcount; i++)
            {
                oldID_newID.Add(i, i);
            }
            if (inputset && outputset)
            {
                XmlWriter xmlwriter = XmlWriter.Create(filepath, GetSettings());
                xmlwriter.WriteStartDocument();

                xmlwriter.WriteStartElement("genome");

                xmlwriter.WriteStartElement("ID");
                xmlwriter.WriteValue(0);
                xmlwriter.WriteEndElement();

                xmlwriter.WriteStartElement("Name");
                xmlwriter.WriteValue(name);
                xmlwriter.WriteEndElement();

                xmlwriter.WriteStartElement("InputCount");
                xmlwriter.WriteValue(inputcount);
                xmlwriter.WriteEndElement();

                xmlwriter.WriteStartElement("OutputCount");
                xmlwriter.WriteValue(outputcount);
                xmlwriter.WriteEndElement();

                xmlwriter.WriteStartElement("inputs");
                for (int inp = 0; inp < inputcount; inp++)
                {
                    xmlwriter.WriteStartElement("input");
                    xmlwriter.WriteAttributeString("id", inp.ToString());
                    xmlwriter.WriteAttributeString("inpindex", inp.ToString());
                    xmlwriter.WriteEndElement();
                }
                xmlwriter.WriteEndElement();

                xmlwriter.WriteStartElement("intermediates");
                foreach(int id in intermediatenodes.Keys)
                {
                    xmlwriter.WriteStartElement("intermediate");
                    int newID = oldID_newID[id];
                    xmlwriter.WriteAttributeString("id", newID.ToString());
                    xmlwriter.WriteAttributeString("distance", intermediatenodes[id].ToString());
                    xmlwriter.WriteEndElement();
                }
                xmlwriter.WriteEndElement();

                xmlwriter.WriteStartElement("outputs");
                for (int outt = inputcount; outt < inputcount+outputcount; outt++)
                {
                    xmlwriter.WriteStartElement("output");
                    xmlwriter.WriteAttributeString("id", outt.ToString());
                    xmlwriter.WriteEndElement();
                }
                xmlwriter.WriteEndElement();

                xmlwriter.WriteStartElement("links");
                foreach(int source in source_Link.Keys)
                {
                   
                    List<Link> links = source_Link[source];
                    foreach (Link link in links)
                    {
                        xmlwriter.WriteStartElement("link");
                        int destination = link.Destination;
                        double weight = link.Weight;
                        int newSourceId = oldID_newID[source];
                        int newDestId = oldID_newID[destination];
                        xmlwriter.WriteAttributeString("source", newSourceId.ToString());
                        xmlwriter.WriteAttributeString("destination", newDestId.ToString());
                        xmlwriter.WriteAttributeString("weight", weight.ToString());
                        xmlwriter.WriteEndElement();
                    }
                }
                xmlwriter.WriteEndElement();

                xmlwriter.WriteEndElement();
                xmlwriter.WriteEndDocument();
                xmlwriter.Close();
                string content = File.ReadAllText(filepath);
                content = content.Replace("\" />", "\"/>");
                File.WriteAllText(filepath, content);
            }
        }

        public static XmlWriterSettings GetSettings()
        {
            return new XmlWriterSettings
            {
                Indent = true,
                IndentChars = "\t"
            };
        }
    }
    public class Link
    {
        public int Source;
        public int Destination;
        public double Weight;
        public Link(int _source, int _destination, double _weight)
        {
            Source = _source;
            Destination = _destination;
            Weight = _weight;
        }
    }
}