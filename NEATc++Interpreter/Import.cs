using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
//using System.Threading.Tasks;

namespace NEATc__Interpreter
{
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void msgoutput(string text);

    internal static class Import
    {
        internal const string dllname = "NEATc++";

        [DllImport(dllname)]
        internal static extern void TestPrint([MarshalAs(UnmanagedType.FunctionPtr)] msgoutput output);
        [DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int TestDLL();

        [DllImport(dllname)]
        internal static extern void Initialise();
        [DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void SetNum(int num);
        [DllImport(dllname)]
        internal static extern int GetNum();
        [DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        internal static extern double RANDOUBLE();

        [DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool GenomeExists(int id);
        [DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int CreateNewGenome(int inputcount, int outputcount, int ltmemorycount,int stmemorycount);
        [DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        internal static extern double GetOutputFromGenome(int genome,int inputcount, double[] inputs, int outputnum);
        [DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void ResetMemory(int genomeid);
        [DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void Mutate(int genomeid, int iterations);
        [DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int CloneGenome(int genome);
        [DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int CreateGenomeWithID(int inputcount, int outputcount,int ltmemorycount, int stmemorycount, int genomeid);
        [DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int CloneGenomeWithID(int genome, int newgenomeid);
        [DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void RemoveGenome(int id);
        [DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void SaveGenome(int id,string filepath);
        [DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool ParseGenome(string filepath);
        //[DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        //internal static extern int Merge(int genomeA, int genomeB);
        //[DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        //internal static extern int GetCommon(int genomeA, int genomeB);

        [DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void SetConsoleActivation(bool active);
        [DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void SetOutputEventHandler(msgoutput output);
    }
    public static class Interface
    {
        public static bool DLLExistsLocally()
        {
            bool output = File.Exists(Import.dllname + ".dll");
            if (!output)
            {
                Output.GenerateOutput("{0}.dll doesn't exist, what the hell are you?",Import.dllname);
                return false;
            }
            try
            {
                int val = Import.TestDLL();
                return val == 5;
            }
            catch(Exception err)
            {
                Output.GenerateOutput(err.Message);
                return false;
            }
        }

        public static void TestPrint()
        {
            if (DLLExistsLocally())
            {
                msgoutput msg = Console.WriteLine;
                Import.TestPrint(msg);
                return;
            }
        }

        public static string GetDLLFilePath()
        {
            return Path.GetFullPath(Import.dllname + ".dll");
        }
        public static void Initialise()
        {
            if (DLLExistsLocally())
            {
                Import.Initialise();
                return;
            }
        }
        public static int GetNum()
        {
            if (DLLExistsLocally())
            {
                return Import.GetNum();
            }
            return -1;
        }
        public static void SetNum(int num)
        {
            if (DLLExistsLocally())
            {
                Import.SetNum(num);
                return;
            }
        }
        public static double RANDOUBLE()
        {
            if (DLLExistsLocally())
            {
                return Import.RANDOUBLE();
            }
            return -1;
        }

        public static bool GenomeExists(int id)
        {
            if (DLLExistsLocally())
            {
                return Import.GenomeExists(id);
            }
            return false;
        }
        public static int CreateNewGenome(int inputcount, int outputcount, int ltmemorycount, int stmemorycount)
        {
            if (DLLExistsLocally())
            {
                return Import.CreateNewGenome(inputcount, outputcount, ltmemorycount, stmemorycount);
            }
            return -1;
        }
        public static double GetOutputFromGenome(int genome, int inputcount, double[] inputs, int outputnum)
        {
            if (DLLExistsLocally())
            {
                return Import.GetOutputFromGenome(genome, inputcount, inputs, outputnum);
            }
            return -1;
        }
        public static void ResetMemory(int genomeid)
        {
            if (DLLExistsLocally())
            {
                Import.ResetMemory(genomeid);
                return;
            }
        }
        public static void Mutate(int genomeid, int iterations)
        {
            if (DLLExistsLocally())
            {
                Import.Mutate(genomeid, iterations);
                return;
            }
        }
        public static int CloneGenome(int genome)
        {
            if (DLLExistsLocally())
            {
                return Import.CloneGenome(genome);
            }
            return -1;
        }
        public static int CreateGenomeWithID(int inputcount, int outputcount,int ltmemorycount, int stmemorycount, int genomeid)
        {
            if (DLLExistsLocally())
            {
                return Import.CreateGenomeWithID(inputcount, outputcount,ltmemorycount,stmemorycount, genomeid);
            }
            return -1;
        }
        public static int CloneGenomeWithID(int genome, int newgenomeid)
        {
            if (DLLExistsLocally())
            {
                return Import.CloneGenomeWithID(genome, newgenomeid);
            }
            return -1;
        }
        public static void RemoveGenome(int id)
        {
            if (DLLExistsLocally())
            {
                Import.RemoveGenome(id);
                return;
            }
        }
        public static void SaveGenome(int id,string filepath)
        {
            if (DLLExistsLocally())
            {
                Import.SaveGenome(id, filepath);
                return;
            }
        }

        public static bool ParseGenome(string filepath)
        {
            if (DLLExistsLocally())
            {
                return Import.ParseGenome(filepath);
            }
            return false;
        }

        //public static int Merge(int genomeA, int genomeB)
        //{
        //    if (DLLExistsLocally())
        //    {
        //        return Import.Merge(genomeA, genomeB);
        //    }
        //    return -1;
        //}

        //public static int GetCommon(int genomeA, int genomeB)
        //{
        //    if (DLLExistsLocally())
        //    {
        //        return Import.GetCommon(genomeA, genomeB);
        //    }
        //    return -1;
        //}

        public static void SetConsoleActivation(bool active)
        {
            if (DLLExistsLocally())
            {
                Import.SetConsoleActivation(active);
                return;
            }
        }

        public static void SetOutputEventHandler(msgoutput output)
        {
            if (DLLExistsLocally())
            {
                Import.SetOutputEventHandler(output);
                return;
            }
        }
    }
}