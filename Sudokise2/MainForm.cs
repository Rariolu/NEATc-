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
using SudokuShiat;

namespace Sudokise2
{
    public partial class MainForm : Form
    {
        const int mutation = 5;
        const string email = "rcoyneyr82011@gmail.com";
        Random rand = new Random();
        Stack<Genome> otherparents = new Stack<Genome>();
        Genome prevcommon;
        const string genomefile = "urgh2";
        const string scorefile = "score";
        const string sudokufile = "sudokupuzzle";
        WholeGrid currentpuzzle = new WholeGrid();
        Genome maxgenome;
        double maxscore = -10000;
        bool puzzleassigned = false;
        bool genomeassigned = false;
        double[] ogInput;
        bool genomechanged = false;
        int maxiteration = -1;
        public MainForm()
        {
            InitializeComponent();
            if (SudokuLoad.ParseSudoku(sudokufile, out WholeGrid grid))
            {
                currentpuzzle = grid;
                ogInput = currentpuzzle.NormaliseCurrentValues();
                puzzleassigned = true;
            }
            else
            {
                MessageBox.Show("Puzzle not parsed.");
            }
            bool g = Genome.ParseGenome(genomefile, out Genome ge);
            bool s = SudokuLoad.LoadScore(scorefile, out int id, out double score);
            if (g && s)
            {
                if (ge.ID == id)
                {
                    maxgenome = ge;
                    prevcommon = maxgenome;
                    maxscore = score;
                    genomeassigned = true;
                    Console.WriteLine("Successfully parsed.");
                }
                else
                {
                    MessageBox.Show("Didn't parse properly. 1");
                }
            }
            else
            {
                MessageBox.Show("Didn't parse properly. 2");
            }
        }
        private void MainForm_KeyDown(object sender, KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.F1:
                    Save();
                    break;
                case Keys.F5:
                    Console.Beep(440, 125);
                    StartTraining();
                    break;
                case Keys.Escape:
                    Close();
                    break;
                case Keys.F3:
                    Console.Beep(440, 125);
                    XML_Formatting.OptimiseFile("urgh2");
                    break;
            }
        }
        void Save()
        {
            if (genomeassigned && genomechanged)
            {
                maxgenome.SaveGenome(genomefile);
                SudokuLoad.SaveScore(scorefile, maxgenome.ID, maxscore);
                genomechanged = false;
            }
        }
        BackgroundWorker bw;
        bool ended = false;
        void StartTraining()
        {
            bw = new BackgroundWorker
            {
                WorkerReportsProgress = true,
                WorkerSupportsCancellation = true
            };
            bw.DoWork += starttraining;
            bw.ProgressChanged += (sender, e) =>
            {
                if (!ended)
                {
                    string t = e.UserState as string;
                    if (e.ProgressPercentage % 200 == 0 || t.Contains("True"))
                    {
                        Console.WriteLine(t);
                    }
                    if (richTextBox1.Text.Length > 10000)
                    {
                        richTextBox1.Text = "";
                    }
                    if (e.ProgressPercentage % 1000 == 0 && e.ProgressPercentage > 0)
                    {
                        richTextBox1.Text += "\nCurrent: {" + t + "}\n";
                        richTextBox1.Text += "Max: {" + String.Format("{0}| Name: {1}; Score: {2};", maxiteration, maxgenome.Name, maxscore) + "}\n\n";
                        richTextBox1.SelectionStart = richTextBox1.Text.Length;
                        Save();
                    }
                }
                else
                {
                    Console.WriteLine("ProgressChanged called after closure.");
                }
            };
            bw.RunWorkerAsync();
        }
        void starttraining(object sender, EventArgs e)
        {
            if (puzzleassigned)
            {
                if (!genomeassigned)
                {
                    if (Genome.CreateNewGenome(81, 81, out Genome g))
                    {
                        maxgenome = g;
                        maxscore = -10000;
                        genomeassigned = true;
                    }
                }
                if (genomeassigned)
                {
                    Console.WriteLine("-1| Name: {0}; Score: {1};", maxgenome.Name, maxscore);
                    for (int i = 0; i < 30000; i++)
                    {
                        try
                        {
                            OneTrainingIteration(i, sender as BackgroundWorker);
                        }
                        catch (Exception err)
                        {
                            if (!EmailAttempt("Fuckin' POS error.", err.Message + "\n\n" + err.StackTrace))
                            {
                                break;
                            }
                        }
                        if (maxscore > -1)
                        {
                            break;
                        }
                    }
                    EmailAttempt("Sudokise Finished", "It done bitch " + maxgenome.Name + " : " + maxscore);
                    Save();
                }
            }
            else
            {
                MessageBox.Show("Puzzle hasn't been assigned you asshole.");
            }
        }
        void DisposeGenome(Genome g)
        {
            //BackgroundWorker bw = new BackgroundWorker();
            //bw.DoWork += (sender, e) =>
            //{
                g.Dispose();
            //};
            //bw.RunWorkerAsync();
        }

        void OneTrainingIteration(int i, BackgroundWorker bw)
        {
            Genome clone = maxgenome;
            bool merged = false;
            bool commoned = false;
            if (rand.Next(3) > 0 && otherparents.Count > 0)
            {
                Genome p = otherparents.Pop();
                if (rand.Next(2) == 0 || otherparents.Count < 1)
                {
                    if (rand.Next(2) == 0 && otherparents.Count > 0)
                    {
                        Genome p2 = otherparents.Pop();

                        if (Genome.Merge(p, p2, out clone))
                        {
                            merged = true;
                        }

                    }
                    else
                    {
                        if (Genome.Merge(maxgenome, p, out clone))
                        {
                            merged = true;
                        }
                    }
                }
                else
                {
                    Console.WriteLine("Commoning attempt. {0}:{1} {2}:{3}", prevcommon.ID, Interface.GenomeExists(prevcommon.ID), p.ID, Interface.GenomeExists(p.ID));
                    if (Genome.GetCommon(prevcommon, p, out clone))
                    {
                        prevcommon = clone;
                        commoned = true;
                        merged = true;
                    }
                    else
                    {
                        Console.WriteLine("Commoning failed. {0}:{1} {2}:{3}",prevcommon.ID,Interface.GenomeExists(prevcommon.ID),p.ID, Interface.GenomeExists(p.ID));
                    }
                }
            }
            if (!merged)
            {
                clone = maxgenome.Clone();
                int m = mutation * (i / 500 + 1) % 20;
                clone.Mutate(m);
            }

            double[] output = clone.GetOutput(ogInput);
            double errorcount = currentpuzzle.CheckDenormalisedValues(output, out string t);
            //System.IO.File.WriteAllText("blep.txt", t);
            double newscore = -errorcount;
            string message = String.Format("{0}| Name: {1}; Score: {2}; {3}", i, clone.Name, newscore, commoned);
            bw.ReportProgress(i, message);
            if (newscore > maxscore)
            {
                otherparents.Clear();
                genomechanged = true;
                maxgenome = clone;
                prevcommon = clone;
                maxscore = newscore;
                maxiteration = i;
                string update = String.Format("{0}| Name: {1}; Score: {2};", i, maxgenome.Name, maxscore);
                EmailAttempt("Sudokise Update: " + maxscore, update);
            }
            else if (newscore == maxscore && !merged)
            {
                otherparents.Push(clone);
            }
            else
            {
                DisposeGenome(clone);
            }
        }
        void Output(string format, params object[] args)
        {
            BackgroundWorker bw = new BackgroundWorker();
            bw.DoWork += (sender, e) =>
            {
                Console.WriteLine(format, args);
            };
            bw.RunWorkerAsync();
        }

        private void MainForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            Save();
        }
        bool EmailAttempt(string subject, string body)
        {
            try
            {
                WebHacks.Fncs.MyEmail(subject, body, email);
                return true;
            }
            catch
            {
                return false;
            }
        }
        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (bw != null)
            {
                ended = true;
                bw.CancelAsync();
            }
        }
    }
}