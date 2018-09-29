using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using NEATc__Interpreter;
using NeuralUtil;
using WebHacks;

namespace Sudokise
{
    public partial class InterfaceForm : Form
    {
        WholeGird gird = new WholeGird();
        public static int[][][][] ogGird;
        //public static WholeGird ogGird;
        int maxscore;
        Genome maxgenome;
        //Dictionary<int, int> scores = new Dictionary<int, int>();
        //Dictionary<int, Genome> genomes = new Dictionary<int, Genome>();
        public InterfaceForm()
        {
            InitializeComponent();
            Color[] colours = new Color[]
            {
                Color.Red,
                Color.Blue,
                Color.Green
            };
            WholeGird g;
            if (SudokuLoad.ParseSudoku(sudokufile, out g))
            {
                gird = g;
            }
            Genome ge;
            int id;
            int score;
            if (Genome.ParseGenome(genomefile, out ge) && (SudokuLoad.LoadScore(scorefile,out id, out score)))
            //if (XML_Formatting.ParseGenome(genomefile, out Genome ge) && (SudokuLoad.LoadScore(scorefile, out int id, out int score)))
            {
                if (ge.ID == id)
                {
                    maxgenome = ge;
                    maxscore = score;
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
            #region ControlStuff
            for (int X = 0; X < 3; X++)
            {
                for (int Y = 0; Y < 3; Y++)
                {
                    for (int x = 0; x < 3; x++)
                    {
                        for (int y = 0; y < 3; y++)
                        {
                            int xloc = (X * 150) + (x * 50);
                            int yloc = (Y * 150) + (y * 50);
                            gird[X][Y][x][y].Location = new Point(xloc, yloc);
                            gird[X][Y][x][y].BackColor = Fncs.MergeColours(colours[X], colours[Y]);
                            gird[X][Y][x][y].ForeColor = Color.White;
                            Controls.Add(gird[X][Y][x][y]);
                        }
                    }
                }
            }
            #endregion
            MSGFormat("{0} : {1}", Interface.GetDLLFilePath(), Interface.DLLExistsLocally() ? "dll found" : "dll not found");
            Output.SetGenericOutput(MSGFormat);
            ogGird = gird.GetIntegerValues();
            //ogGird = new WholeGird(gird);
        }
        double[] oginput;
        private void button1_Click(object sender, EventArgs e)
        {
            Genome genome;
            if (Genome.CreateNewGenome(81, 81, out genome))
            {
                if (!oginputassigned)
                {
                    oginput = gird.NormaliseCurrentValues();
                    oginputassigned = true;
                }
                double[] output = genome.GetOutput(oginput);
                int errorcount = gird.DenormaliseValues(output);
                maxgenome = genome;
                maxscore = -gird.Count(0) - errorcount;
                maxoutput = output;
            }
        }
        void MSGFormat(string format, params object[] args) => MessageBox.Show(String.Format(format, args));
        int j = 0;
        double[] maxoutput;
        int mutation = 5;
        string email = "rcoyneyr82011@gmail.com";
        bool oginputassigned = false;
        private void button2_Click(object sender, EventArgs e)
        {
            if (!oginputassigned)
            {
                oginput = gird.NormaliseCurrentValues();
                oginputassigned = true;
                maxoutput = maxgenome.GetOutput(oginput);
            }
            //int i = 0;
            for (int i = 0; i < 500; i++)
            {
                Genome max = maxgenome;//GetMax();
                j++;
                if (i % 2 == 0)
                {
                    Console.WriteLine("{0}| Name: {1}; Score: {2};", j, max.Name, maxscore);
                }

                Genome clone = max.Clone();
                int m = mutation * (i / 500 + 1);
                clone.Mutate(m);
                double[] output = clone.GetOutput(oginput);
                int errorcount = gird.DenormaliseValues(output);
                int newscore = -gird.Count(0) - errorcount;
                
                if (newscore > maxscore)
                {
                    maxoutput = output;
                    maxscore = newscore;
                    maxgenome = clone;
                    string update = String.Format("{0}| Name: {1}; Score: {2};",j, maxgenome.Name, maxscore);
                    try
                    {
                        WebHacks.Fncs.MyEmail("Sudokise Update: "+maxscore,update, email);
                    }
                    catch
                    {

                    }
                }
                else
                {
                    
                    gird.DenormaliseValues(maxoutput);
                    DisposeGenome(clone);
                }
                if (newscore > -1)
                {
                    //break;
                }
            }
            WebHacks.Fncs.MyEmail("Sudokise Finished", "It done bitch " + maxgenome.Name, email);
        }
        void DisposeGenome(Genome g)
        {
            BackgroundWorker bw = new BackgroundWorker();
            bw.DoWork += (sender, e) =>
            {
                g.Dispose();
            };
            bw.RunWorkerAsync();
        }
        private void button3_Click(object sender, EventArgs e)
        {
            Genome g = maxgenome;//GetMax();
            g.SaveGenome(genomefile);
            SudokuLoad.SaveScore(scorefile, g.ID, maxscore);//scores[g.ID]);
        }
        const string genomefile = "urgh";
        const string scorefile = "score";
        const string sudokufile = "sudokupuzzle";
        private void button4_Click(object sender, EventArgs e)
        {
            SudokuLoad.SaveSudoku(gird, sudokufile);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            
        }
    }
    public class WholeGird
    {
        public int[][][][] GetIntegerValues()
        {
            int[][][][] vals = new int[3][][][];
            for (short X = 0; X < 3; X++)
            {
                vals[X] = new int[3][][];
                for (short Y = 0; Y < 3; Y++)
                {
                    vals[X][Y] = new int[3][];
                    for (short x = 0; x < 3; x ++)
                    {
                        vals[X][Y][x] = new int[3];
                        for (short y = 0; y < 3; y++)
                        {
                            vals[X][Y][x][y] = this[X][Y][x][y].Value;
                        }
                    }
                }
            }
            return vals;
        }

        readonly MainVertical[] mainVerticals = new MainVertical[3];
        public WholeGird()
        {
            for (int i = 0; i < 3; i++)
            {
                mainVerticals[i] = new MainVertical();
            }
        }
        public WholeGird(WholeGird parent) : this()
        {
            Action<int, int, int, int> action = (X, Y, x, y) =>
            {
                this[X][Y][x][y].Value = parent[X][Y][x][y].Value;
            };
        }
        public void PerformActionForEachValue(Action<int,int,int,int> action)
        {
            for (short X = 0; X < 3; X++)
            {
                for (short Y = 0; Y < 3; Y++)
                {
                    for (short x = 0; x < 3; x++)
                    {
                        for (short y = 0; y < 3; y++)
                        {
                            action(X, Y, x, y);
                        }
                    }
                }
            }
        }
        public MainVertical this[int index]
        {
            get
            {
                if (index < 0 || index > 2)
                {
                    throw new Exception("Index has to be between 0 and 2, silly goose.");
                }
                return mainVerticals[index];
            }
        }
        public bool Contains(int val)
        {
            foreach (MainVertical mainv in mainVerticals)
            {
                if (mainv.Contains(val))
                {
                    return true;
                }
            }
            return false;
        }
        public bool VerticalLineContains(GridPosition pos, int val)
        {
            for (int i = 0; i < 3; i++)
            {
                if (this[pos.X][i][pos.x].Contains(val))
                {
                    return true;
                }
            }
            return false;
        }
        public bool HorizontalLineContains(GridPosition pos, int val)
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (this[i][pos.Y][j][pos.y].Value == val)
                    {
                        return true;
                    }
                }
            }
            return false;
        }
        public double[] NormaliseCurrentValues()
        {
            double[] output = new double[81];
            int i = 0;
            for (int X = 0; X < 3; X++)
            {
                for (int Y = 0; Y < 3; Y++)
                {
                    for (int x = 0; x < 3; x++)
                    {
                        for (int y = 0; y < 3; y++)
                        {
                            int val = this[X][Y][x][y].Value;
                            output[i++] = Formatting.Normalise(val, 0, 9);
                        }
                    }
                }
            }
            return output;
        }
        public int DenormaliseValues(double[] values)
        {
            int errorcount = 0;
            int i = 0;
            for (int X = 0; X < 3; X++)
            {
                for (int Y = 0; Y < 3; Y++)
                {
                    for (int x = 0; x < 3; x++)
                    {
                        for (int y = 0; y < 3; y++)
                        {
                            double val = values[i++];
                            int denorm = (int)Math.Round(Formatting.ReverseNormalise(val, 0, 9), MidpointRounding.AwayFromZero);
                            int ogVAL = InterfaceForm.ogGird[X][Y][x][y];
                            if (denorm != ogVAL && ogVAL != 0)
                            {
                                errorcount+=2;
                            }
                            if (denorm == 0)
                            {
                                errorcount++;
                            }
                            bool available = (denorm > -1 && denorm < 10) && !(this[X][Y].Contains(denorm) || HorizontalLineContains(new GridPosition(X, Y, x, y), denorm) || VerticalLineContains(new GridPosition(X, Y, x, y), denorm));
                            if (available)
                            {
                                this[X][Y][x][y].Value = denorm;
                            }
                            else
                            {
                                this[X][Y][x][y].Value = 0;
                                errorcount++;
                            }
                        }
                    }
                }
            }
            return errorcount;
        }
        public int Count(int val)
        {
            int count = 0;
            foreach (MainVertical mainV in mainVerticals)
            {
                count += mainV.Count(val);
            }
            return count;
        }
    }
    public class GridPosition
    {
        public int X;
        public int Y;
        public int x;
        public int y;
        public GridPosition(int _X, int _Y, int _x, int _y)
        {
            X = _X;
            Y = _Y;
            x = _x;
            y = _y;
        }
    }
    public class MainVertical
    {
        readonly Cube[] cubes = new Cube[3];
        public MainVertical()
        {
            for (int i = 0; i < 3; i++)
            {
                cubes[i] = new Cube();
            }
        }
        public Cube this[int index]
        {
            get
            {
                if (index < 0 || index > 2)
                {
                    throw new Exception("Index has to be between 0 and 2, silly goose.");
                }
                return cubes[index];
            }
        }
        public bool Contains(int val)
        {
            foreach (Cube cube in cubes)
            {
                if (cube.Contains(val))
                {
                    return true;
                }
            }
            return false;
        }
        public int Count(int val)
        {
            int count = 0;
            foreach (Cube cube in cubes)
            {
                count += cube.Count(val);
            }
            return count;
        }
    }
    public class Cube
    {
        readonly SubVertical[] subVerticals = new SubVertical[3];
        public Cube()
        {
            for (int i = 0; i < 3; i++)
            {
                subVerticals[i] = new SubVertical();
            }
        }
        public SubVertical this[int index]
        {
            get
            {
                if (index < 0 || index > 2)
                {
                    throw new Exception("Index has to be between 0 and 2, silly goose.");
                }
                return subVerticals[index];
            }
        }
        public bool Contains(int val)
        {
            foreach (SubVertical sub in subVerticals)
            {
                if (sub.Contains(val))
                {
                    return true;
                }
            }
            return false;
        }
        public int Count(int val)
        {
            int count = 0;
            foreach (SubVertical sub in subVerticals)
            {
                count += sub.Count(val);
            }
            return count;
        }
    }
    public class SubVertical
    {
        readonly IntTextBox[] inttextboxes = new IntTextBox[3];
        public SubVertical()
        {
            for (int i = 0; i < 3; i++)
            {
                IntTextBox itb = new IntTextBox
                {
                    Size = new Size(50, 50)
                };
                inttextboxes[i] = itb;
            }
        }
        public IntTextBox this[int index]
        {
            get
            {
                if (index < 0 || index > 2)
                {
                    throw new Exception("Index has to be between 0 and 2, silly goose.");
                }
                return inttextboxes[index];
            }
        }
        public bool Contains(int val)
        {
            foreach (IntTextBox itb in inttextboxes)
            {
                if (itb.Value == val)
                {
                    return true;
                }
            }
            return false;
        }
        public int Count(int val)
        {
            int count = 0;
            foreach (IntTextBox itb in inttextboxes)
            {
                if (itb.Value == val)
                {
                    count++;
                }
            }
            return count;
        }
    }
    //public class IntTextBox
    //{
    //    public int Value = 0;
    //}
    public class IntTextBox : RichTextBox
    {
        string og = "0";
        public IntTextBox()
        {
            Text = "0";
            TextChanged += IntTextBox_TextChanged;
            SetAlignment();
        }
        bool IsInt(string text)
        {
            int temp;
            if (int.TryParse(text, out temp))
            {
                return temp > -1 && temp < 10;
            }
            return false;
        }
        private void IntTextBox_TextChanged(object sender, EventArgs e)
        {
            if (IsInt(Text))
            {
                og = Text;
                SetAlignment();
            }
            else
            {
                Text = og;
            }
        }
        public int Value
        {
            get
            {
                return int.Parse(Text);
            }
            set
            {
                if (value > -1 && value < 10)
                {
                    Text = value.ToString();
                }
            }
        }
        void SetAlignment()
        {
            SelectAll();
            SelectionAlignment = HorizontalAlignment.Center;
            DeselectAll();
        }
    }
}