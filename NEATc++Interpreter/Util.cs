using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//using System.Threading.Tasks;

namespace NEATc__Interpreter
{
    public static class Util
    {
        public static char[] Letters
        {
            get
            {
                return Enumerable.Range('A', 26).Select(x => (char)x).ToArray();
            }
        }
        public static char GetLetter(int index)
        {
            return Letters.GetElementRegardlessOfIndex(index);
        }
        public static T GetElementRegardlessOfIndex<T>(this T[] array, int index)
        {
            index = index % array.Length;
            return array[index];
        }
        public static Random rand = new Random();
        public static T GetRandomElement<T>(this IEnumerable<T> array)
        {
            if (array.Count() < 1)
            {
                return default(T);
            }
            return array.ElementAt(rand.Next(array.Count()));
        }
        public static bool RandomBool()
        {
            return rand.NextDouble() > 0.5;
        }
    }
}