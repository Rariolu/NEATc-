using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using NEATc__Interpreter;

namespace Demo
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            Output.SetGenericOutput(MSGFormat);
            Interface.SetOutputEventHandler(Output.GenerateOutput);
        }
        private void button1_Click(object sender, EventArgs e)
        {
            Interface.Initialise();
            MessageBox.Show("Initialised");
        }
        private void button2_Click(object sender, EventArgs e)
        {
            int a = Interface.GetNum();
            Interface.SetNum(15);
            int b = Interface.GetNum();
            MSGFormat("a: {0}; b: {1};", a, b);
        }
        public void MSGFormat(string format, params object[] args)
        {
            MessageBox.Show(String.Format(format, args));
        }
        private void button3_Click(object sender, EventArgs e)
        {
            int id = Interface.CreateNewGenome(2, 1,0);
            MSGFormat("Id: {0};", id);
        }
        private void button4_Click(object sender, EventArgs e)
        {
            int id = Interface.CreateNewGenome(2, 1,0);
            double num = Interface.GetOutputFromGenome(id, 2, new double[] { 1, 2 }, 0);
            MSGFormat("Num: {0};", num);
        }
        private void button5_Click(object sender, EventArgs e)
        {
            Genome genome;// = new Genome(3, 2);
            if (Genome.CreateNewGenome(3, 2, out genome))
            {
                double[] o = genome.GetOutput(new double[] { 1, 2, 1 });
                MSGFormat("Output: {0}; {1};", o[0], o[1]);
            }
            else
            {
                MessageBox.Show("Woopsie doodles.");
            }
        }
        private void button6_Click(object sender, EventArgs e)
        {
            double d = Interface.RANDOUBLE();
            MSGFormat("d: {0};", d);
        }
        private void button7_Click(object sender, EventArgs e)
        {
            Genome genome;
            if (Genome.CreateNewGenome(3, 2, out genome))
            {
                double[] preo = genome.GetOutput(new double[] { 1, 2, 1 });
                genome.Mutate(5);
                double[] o = genome.GetOutput(new double[] { 1, 2, 1 });
                Output.GenerateOutput("Before mutation: {0}; {1};\nAfter mutation: {2}; {3}",true, preo[0], preo[1], o[0], o[1]);
            }
        }
        Genome btn8genome;
        bool initialised = false;
        private void button8_Click(object sender, EventArgs e)
        {
            if (!initialised)
            {
                if (Genome.CreateNewGenome(3, 2, out btn8genome))
                {
                    double[] o = btn8genome.GetOutput(new double[] { 1, 2, 1 });
                    initialised = true;
                    MSGFormat("Current Output: {0}; {1};", o[0], o[1]);
                }
            }
            else
            {
                btn8genome.Mutate(5);
                double[] o = btn8genome.GetOutput(new double[] { 1, 2, 1 });
                MSGFormat("Current Output: {0}; {1};", o[0], o[1]);
            }
        }

        private void button9_Click(object sender, EventArgs e)
        {
            Interface.SetConsoleActivation(false);
            if (Genome.CreateNewGenome(3, 2, out Genome urgh))
            {
                double[] o1 = urgh.GetOutput(new double[] { 1, 2, 1 });
                MSGFormat("urgh: [0]: {0}; [1]: {1};", o1[0], o1[1]);
                Interface.SetConsoleActivation(true);
                Genome clone = urgh.Clone();
                double[] o2 = clone.GetOutput(new double[] { 1, 2, 1 });
                MSGFormat("clone: [0]: {0}; [1]: {1};", o2[0], o2[1]);
                clone.Mutate(5);
                Interface.SetConsoleActivation(false);
                MSGFormat("urgh: [0]: {0}; [1]: {1};", o1[0], o1[1]);
                Interface.SetConsoleActivation(true);
                o2 = clone.GetOutput(new double[] { 1, 2, 1 });
                MSGFormat("clone: [0]: {0}; [1]: {1};", o2[0], o2[1]);
            }
        }
        const string file = "belppyyijytkj";
        private void button11_Click(object sender, EventArgs e)
        {
            //double[] input = new double[] { 1, 2, 1 };
            //Genome g;
            //if (XML_Formatting.ParseGenome(file,out g))
            //{
            //    double[] output = g.GetOutput(input);
            //    MSGFormat("[0]: {0}; [1]: {1};", output[0], output[1]);
            //}
            //else
            //{
            //    Genome oldG;
            //    if (Genome.CreateNewGenome(3, 2, out oldG))
            //    {
            //        oldG.Mutate(5);
            //        double[] output = oldG.GetOutput(input);
            //        oldG.SaveGenome(file);
            //        MSGFormat("[0]: {0}; [1]: {1};", output[0], output[1]);
            //    }
            //}
        }
        private void button12_Click(object sender, EventArgs e)
        {
            int id = 0;
            bool exists = Interface.GenomeExists(id);
            MSGFormat("{0}: {1}", id, exists ? "exists" : "doesn't exist");
        }
        private void button13_Click(object sender, EventArgs e)
        {
            Interface.TestPrint();
        }
        private void button14_Click(object sender, EventArgs e)
        {
            string file = "cppxml.xml";
            bool parse = Interface.ParseGenome(file);
            Genome.ParseGenome(file, out Genome g);
            MSGFormat("{0} : {1}", file, parse ? "parse succeeded" : "parse failed");
        }
        private void button10_Click(object sender, EventArgs e)
        {
            if (Genome.CreateGenomeFromID(3,2,5,out Genome g))
            {
                double[] output = g.GetOutput(new double[] { 1, 2, 1 });
                MSGFormat("[0]: {0}; [1]: {1}", output[0], output[1]);
                g.Mutate(100);
                output = g.GetOutput(new double[] { 1, 2, 1 });
                MSGFormat("[0]: {0}; [1]: {1}", output[0], output[1]);
                Interface.SaveGenome(5,"cppxml.xml");
            }
        }
        private void button15_Click(object sender, EventArgs e)
        {
            string file = "cppxml.xml";
            if (Genome.ParseGenome(file,out Genome genome))
            {
                genome.Mutate(100);
                double[] output = genome.GetOutput(new double[] { 1, 2, 1 });
                MSGFormat("[0]: {0}; [1]: {1}", output[0], output[1]);
                Genome genome2 = genome.Clone();
                genome2.SaveGenome(file);
            }
        }
        private void button16_Click(object sender, EventArgs e)
        {
            new Form2().ShowDialog();
        }
    }
}