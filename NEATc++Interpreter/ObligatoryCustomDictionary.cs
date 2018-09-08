using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//using System.Threading.Tasks;

namespace NEATc__Interpreter
{
    public delegate void ItemAdded<T, U>(T key, U value);
    [Serializable]
    public class ObligatoryCustomDictionary<T, U> where T : new()
        where U : new()
    {
        [NonSerialized]
        public ItemAdded<T, U> ItemAdded = (key, val) => { };
        public List<T> keys = new List<T>();
        public T[] Keys
        {
            get
            {
                return keys.ToArray();
            }
        }
        public bool ContainsKey(T key)
        {
            return keys.Contains(key);
        }
        public List<U> values = new List<U>();
        public void Add(T key, U value)
        {
            if (!keys.Contains(key))
            {
                keys.Add(key);
                values.Add(value);
                ItemAdded(key, value);
            }
        }
        public void Remove(T key)
        {
            if (keys.Contains(key))
            {
                int index = keys.IndexOf(key);
                keys.RemoveAt(index);
                values.RemoveAt(index);
            }
        }
        public U this[T key]
        {
            get
            {
                if (!keys.Contains(key))
                {
                    throw new Exception(String.Format("\"{0}\" is not an appropriate key.", key));
                }
                return values[keys.IndexOf(key)];
            }
            set
            {
                if (keys.Contains(key))
                {
                    values[keys.IndexOf(key)] = value;
                }
                else
                {
                    Add(key, value);
                }
            }
        }
        public int Count
        {
            get
            {
                return keys.Count;
            }
        }
    }
}
