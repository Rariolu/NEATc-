using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
//using System.Threading.Tasks;

namespace NEATc__Interpreter
{
    public class Genome : IDisposable
    {
        static int GenomeIndex = 0;
        string name = "";
        public string Name
        {
            get
            {
                return name;
            }
            set
            {
                string temp = value;
                if (temp.Length > 100)
                {
                    temp = temp.Remove(0, 1);
                }
                name = temp;
            }
        }
        public readonly int ID;
        public readonly int InputCount;
        public readonly int OutputCount;
        public readonly int MemoryCount;
        private Genome(int inputcount, int outputcount, int memorycount)
        {
            try
            {
                ID = Interface.CreateNewGenome(inputcount, outputcount, memorycount);
                if (ID == -1)
                {
                    throw new Exception("Local DLL not present.");
                }
            }
            catch(Exception err)
            {
                throw new Exception("C++ library is being a dick", err);
            }
            InputCount = inputcount;
            OutputCount = outputcount;
            MemoryCount = memorycount;
            Name = Util.GetLetter(ID + GenomeIndex++).ToString();
        }
        private Genome(int inputcount, int outputcount,int memorycount, int id, bool createnew = true)
        {
            if (createnew)
            {
                try
                {
                    int tempid = Interface.CreateGenomeWithID(inputcount, outputcount,memorycount, id);
                    if (tempid == -1)
                    {
                        throw new Exception("jgrijgoirjgroij");
                    }
                }
                catch (Exception err)
                {
                    throw new Exception("C++ library is being a dick", err);
                }
            }
            ID = id;
            InputCount = inputcount;
            OutputCount = outputcount;
            MemoryCount = memorycount;
            //mutationhistory.ItemAdded += (key, value) =>
            //{
            //    idorder.Add(key);
            //};
            //mutationhistory[ID] = 0;
            Name = Util.GetLetter(ID + GenomeIndex++).ToString();
        }
        private Genome(Genome parent,int newid)
        {
            InputCount = parent.InputCount;
            OutputCount = parent.OutputCount;
            //mutationhistory = parent.mutationhistory;
            //idorder = parent.idorder;
            ID = newid;
            //mutationhistory[ID] = 0;
            //mutationhistory.ItemAdded = (key, value) =>
            //{
            //    idorder.Add(key);
            //};
            Name = parent.Name + Util.GetLetter(ID + GenomeIndex++);
        }
        public Genome Clone()
        {
            //Console.WriteLine("Clone C# started");
            int cloneid = Interface.CloneGenome(ID);
            Genome clone = new Genome(this, cloneid);
            //Console.WriteLine("Clone C# ended");
            return clone;
        }
        public Genome CloneWithID(int newid)
        {
            int temp = Interface.CloneGenomeWithID(ID,newid);
            if (temp != newid)
            {
                throw new Exception("Cloning error occurred.");
            }
            Genome clone = new Genome(this, newid);
            return clone;
        }
        public static bool CloneWithID(int newid,Genome ogGenome, out Genome genome)
        {
            try
            {
                genome = ogGenome.CloneWithID(newid);
                return true;
            }
            catch(Exception err)
            {
                Output.GenerateOutput("CloneWithID threw an exception: \"{0}\".", err.Message);
                genome = null;
                return false;
            }
        }
        public static bool CreateNewGenome(int inputcount, int outputcount, out Genome genome, int memorycount = 0)
        {
            try
            {
                genome = new Genome(inputcount, outputcount,memorycount);
                return true;
            }
            catch(Exception err)
            {
                Console.WriteLine(err.Message);
                genome = null;
                return false;
            }
        }
        public static bool CreateGenomeFromID(int inputcount, int outputcount, int id, out Genome genome)
        {

            try
            {
                genome = new Genome(inputcount, outputcount, id);
                return true;
            }
            catch
            {
                genome = null;
                return false;
            }
        }
        public double[] GetOutput(double[] inputs)
        {
            Interface.ResetMemory(ID);
            double[] output = new double[OutputCount];
            for (int i = 0; i < OutputCount; i++)
            {
                output[i] = Interface.GetOutputFromGenome(ID, InputCount, inputs, i);
            }
            return output;
        }
        public void Mutate(int iterations = 1)
        {
            iterations = Math.Abs(iterations);
            Interface.Mutate(ID, iterations);
            //mutationhistory[ID]+=iterations;
        }

        public void Dispose()
        {
            Interface.RemoveGenome(ID);
        }
        public static bool ParseGenome(string filepath, out Genome genome)
        {
            filepath = filepath.EndsWith(".xml") ? filepath : filepath + ".xml";
            genome = null;
            if (!File.Exists(filepath))
            {
                return false;
            }
            if (XML_Formatting.CPP_Parse(filepath,out int _id, out int _inputcount, out int _outputcount, out int memorycount, out string n_ame))
            {
                genome = new Genome(_inputcount, _outputcount,memorycount, _id,false);
                if (!String.IsNullOrEmpty(n_ame))
                {
                    genome.Name = n_ame;
                }
                return Interface.ParseGenome(filepath);
            }
            return false;
        }
        public void SaveGenome(string filepath)
        {
            filepath = filepath.EndsWith(".xml") ? filepath : filepath + ".xml";
            Interface.SaveGenome(ID, filepath);
            if (File.Exists(filepath))
            {
                string content = File.ReadAllText(filepath);
                int idclose = content.IndexOf("</ID>");
                if (idclose > -1)
                {
                    idclose += 6;
                    content = content.Insert(idclose, String.Format("\n\t<Name>{0}</Name>\n",Name));
                    File.WriteAllText(filepath, content);
                    //XML_Formatting.OptimiseFile(filepath);
                }
            }
        }
        public static bool Merge(Genome a, Genome b, out Genome merged)
        {
            merged = null;
            if (a.InputCount != b.InputCount || a.OutputCount != b.OutputCount)
            {
                return false;
                //throw new Exception(String.Format("A's input is {0} and B's input is {1}. A's output is {2} and B's output is {3}. Inputs and outputs of both genomes need to match.", a.InputCount, b.InputCount, a.OutputCount, b.OutputCount));
            }
            int aID = a.ID;
            int bID = b.ID;
            Console.WriteLine("A: {0}; B: {1}", aID, bID);
            int newID = Interface.Merge(aID, bID);
            if (newID == -1)
            {
                return false;
            }
            merged = new Genome(a.InputCount, a.OutputCount,a.MemoryCount, newID, false);
            int namelength = Math.Max(a.Name.Length, b.Name.Length);
            string newname = "";
            for (int i = 0; i < namelength; i++)
            {
                if (i % 2 == 0)
                {
                    newname += a.Name[i % a.Name.Length];
                }
                else
                {
                    newname += b.Name[i % b.Name.Length];
                }
            }

            merged.Name = newname;
            return true;
        }
        public static bool GetCommon(Genome a, Genome b, out Genome common)
        {
            common = null;
            if (a.InputCount != b.InputCount || a.OutputCount != b.OutputCount)
            {
                Console.WriteLine("Inputs and outputs don't match.");
                return false;
            }
            int aID = a.ID;
            int bID = b.ID;
            int newID = Interface.GetCommon(aID, bID);
            if (newID == -1)
            {
                Console.WriteLine("-1 returned.");
                return false;
            }
            common = new Genome(a.InputCount, a.OutputCount,a.MemoryCount, newID, false);
            int namelength = Math.Min(a.Name.Length, b.Name.Length);
            string newname = "";
            for (int i = 0; i < namelength; i++)
            {
                if (a.Name[i] == b.Name[i])
                {
                    newname += a.Name[i];
                }
            }
            common.Name = newname;
            return true;
        }
    }
}