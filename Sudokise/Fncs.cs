using System.Drawing;

namespace Sudokise
{
    public static class Fncs
    {
        public static Color MergeColours(Color a, Color b)
        {
            int newR = (a.R + b.R) / 2;
            int newG = (a.G + b.G) / 2;
            int newB = (a.B + b.B) / 2;
            return Color.FromArgb(newR, newG, newB);
        }
        //public static int CheckValues(double[] genomeoutput)
        //{
        //    int errorcount = 0;
        //    int i = 0;
        //    for (short X = 0; X < 3; X++)
        //    {
        //        for (short Y = 0; Y < 3; Y++)
        //        {
        //            for (short x = 0; x < 3; x++)
        //            {
        //                for (short y = 0; y < 3; y++)
        //                {

        //                }
        //            }
        //        }
        //    }
        //}
    }
}