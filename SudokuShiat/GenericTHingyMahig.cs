using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NeuralUtil;

namespace SudokuShiat
{
    public delegate T Initialiser<T>();
    public delegate void IterableAction<T>(T item);
    public abstract class GenericTHingyMahig<T> where T : new()
    {
        T[] items;
        int _quantity;
        public GenericTHingyMahig(int quantity = 3) : this(() => { return new T(); },quantity)
        {

        }
        public GenericTHingyMahig(Initialiser<T> init, int quantity = 3)
        {
            if (quantity >= 0)
            {
                items = new T[quantity];
                for (int i = 0; i < quantity; i++)
                {
                    items[i] = init();
                }
            }
            _quantity = quantity;
        }
        public T this[int index]
        {
            get
            {
                if (index < 0 || index >= _quantity)
                {
                    throw new Exception("Index out of bounds, bitch.");
                }
                return items[index];
            }
            set
            {
                if (index < 0 || index >= _quantity)
                {
                    throw new Exception("Index out of bounds, bitch.");
                }
                items[index] = value;
            }
        }
        public void PerformActionForEach(IterableAction<T> action)
        {
            for (int i = 0; i < 3; i++)
            {
                action(items[i]);
            }
        }
        public abstract bool Contains(int val);
        public abstract int Count(int val);
    }
    public class SubVertical : GenericTHingyMahig<int>
    {
        public SubVertical() : base(() => { return 0; })
        {

        }
        public override bool Contains(int val)
        {
            for (int i = 0; i < 3; i++)
            {
                if (this[i] == val)
                {
                    return true;
                }
            }
            return false;
        }
        public override int Count(int val)
        {
            int count = 0;
            for (int i = 0; i < 3; i++)
            {
                if (this[i] == val)
                {
                    count++;
                }
            }
            return count;
        }
    }
    public class Cube : GenericTHingyMahig<SubVertical>
    {
        public override bool Contains(int val)
        {
            for (int i = 0; i < 3; i++)
            {
                if (this[i].Contains(val))
                {
                    return true;
                }
            }
            return false;
        }
        public override int Count(int val)
        {
            int count = 0;
            for (int i = 0; i < 3; i++)
            {
                count += this[i].Count(val);
            }
            return count;
        }
    }
    public class MainVertical : GenericTHingyMahig<Cube>
    {
        public override bool Contains(int val)
        {
            for (int i = 0; i < 3; i++)
            {
                if (this[i].Contains(val))
                {
                    return true;
                }
            }
            return false;
        }
        public override int Count(int val)
        {
            int count = 0;
            for (int i = 0; i < 3; i++)
            {
                count += this[i].Count(val);
            }
            return count;
        }
    }
    public class WholeGrid : GenericTHingyMahig<MainVertical>
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
                    for (short x = 0; x < 3; x++)
                    {
                        vals[X][Y][x] = new int[3];
                        for (short y = 0; y < 3; y++)
                        {
                            vals[X][Y][x][y] = this[X][Y][x][y];
                        }
                    }
                }
            }
            return vals;
        }
        public override bool Contains(int val)
        {
            for (int i = 0; i < 3; i++)
            {
                if (this[i].Contains(val))
                {
                    return true;
                }
            }
            return false;
        }
        public override int Count(int val)
        {
            int count = 0;
            for (int i = 0; i < 3; i++)
            {
                count += this[i].Count(val);
            }
            return count;
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
                            int val = this[X][Y][x][y];
                            output[i++] = Formatting.Normalise(val, 0, 9);
                        }
                    }
                }
            }
            return output;
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
                    if (this[i][pos.Y][j][pos.y] == val)
                    {
                        return true;
                    }
                }
            }
            return false;
        }
        public double CheckDenormalisedValues(double[] values)
        {
            string t;
            return CheckDenormalisedValues(values, out t);
        }
        public double CheckDenormalisedValues(double[] values, out string text)
        {
            text = "";
            double errorcount = 0;
            int i = 0;
            for (short X = 0; X < 3; X++)
            {
                for (short Y = 0; Y < 3; Y++)
                {
                    for (short x = 0; x < 3; x++)
                    {
                        for (short y = 0; y < 3; y++)
                        {
                            double val = values[i++];
                            int denorm = (int)Math.Round(Formatting.ReverseNormalise(val, 0, 9), MidpointRounding.AwayFromZero);
                            int ogVAL = this[X][Y][x][y];
                            text += denorm + "|";
                            if (denorm != ogVAL && ogVAL != 0)
                            {
                                errorcount += 2;
                            }
                            if (denorm == 0)
                            {
                                errorcount++;
                            }
                            bool available = (denorm > -1 && denorm < 10) && !(this[X][Y].Contains(denorm) || HorizontalLineContains(new GridPosition(X, Y, x, y), denorm) || VerticalLineContains(new GridPosition(X, Y, x, y), denorm));
                            if (!available)
                            {
                                errorcount++;
                            }
                        }
                    }
                }
            }
            return errorcount;
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
}