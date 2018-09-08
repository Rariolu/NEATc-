using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.Xml.Serialization;
using NEATc__Interpreter;

namespace SudokuShiat
{
    public static class SudokuLoad
    {
        public static void SaveSudoku(WholeGrid grid, string filepath)
        {
            filepath = filepath.EndsWith(".xml") ? filepath : filepath + ".xml";
            XmlWriter xmlwriter = XmlWriter.Create(filepath, XML_Formatting.GetSettings());
            xmlwriter.WriteStartDocument();
            xmlwriter.WriteStartElement("sudoku");
            for (short X = 0; X < 3; X++)
            {
                for (short Y = 0; Y < 3; Y++)
                {
                    xmlwriter.WriteStartElement("Cube");
                    xmlwriter.WriteAttributeString("x", X.ToString());
                    xmlwriter.WriteAttributeString("y", Y.ToString());
                    for (short x = 0; x < 3; x++)
                    {
                        xmlwriter.WriteStartElement("subcolumn");
                        xmlwriter.WriteAttributeString("x", x.ToString());
                        for (short y = 0; y < 3; y++)
                        {
                            xmlwriter.WriteStartElement("val");
                            xmlwriter.WriteAttributeString("y", y.ToString());
                            xmlwriter.WriteValue(grid[X][Y][x][y]);
                            xmlwriter.WriteEndElement();
                        }
                        xmlwriter.WriteEndElement();
                    }
                    xmlwriter.WriteEndElement();
                }
            }
            xmlwriter.WriteEndElement();
            xmlwriter.WriteEndDocument();
            xmlwriter.Close();
        }
        public static bool ParseSudoku(string filepath, out WholeGrid grid)
        {
            filepath = filepath.EndsWith(".xml") ? filepath : filepath + ".xml";
            if (!File.Exists(filepath))
            {
                grid = null;
                return false;
            }
            grid = new WholeGrid();
            XmlReader xmlreader = XmlReader.Create(filepath);
            while (xmlreader.Read())
            {
                if (xmlreader.IsStartElement("Cube"))
                {
                    int X = int.Parse(xmlreader["x"]);
                    int Y = int.Parse(xmlreader["y"]);
                    XmlReader cube = xmlreader.ReadSubtree();
                    while (cube.Read())
                    {
                        if (cube.IsStartElement("subcolumn"))
                        {
                            int x = int.Parse(cube["x"]);
                            XmlReader subcolumn = xmlreader.ReadSubtree();
                            while (subcolumn.Read())
                            {
                                if (subcolumn.IsStartElement("val"))
                                {
                                    int y = int.Parse(subcolumn["y"]);
                                    subcolumn.Read();
                                    grid[X][Y][x][y] = int.Parse(subcolumn.Value);
                                }
                            }
                        }
                    }
                }
            }
            return true;
        }
        public static void SaveScore(string filepath, int id, double score)
        {
            filepath = filepath.EndsWith(".xml") ? filepath : filepath + ".xml";
            XmlWriter writer = XmlWriter.Create(filepath, XML_Formatting.GetSettings());
            writer.WriteStartDocument();

            writer.WriteStartElement("maxscore");

            writer.WriteStartElement("genome");

            writer.WriteAttributeString("id", id.ToString());

            writer.WriteAttributeString("score", score.ToString());

            writer.WriteEndElement();

            writer.WriteEndElement();

            writer.WriteEndDocument();
            writer.Close();
        }
        public static bool LoadScore(string filepath, out int id, out double score)
        {
            filepath = filepath.EndsWith(".xml") ? filepath : filepath + ".xml";
            score = -82;
            id = -1;
            if (!File.Exists(filepath))
            {
                return false;
            }
            XmlReader xmlreader = XmlReader.Create(filepath);
            while (xmlreader.Read())
            {
                if (xmlreader.IsStartElement("genome"))
                {
                    id = int.Parse(xmlreader["id"]);
                    score = double.Parse(xmlreader["score"]);
                    return true;
                }
            }
            xmlreader.Close();
            return false;
        }
        public static string GetIncrementalFilePath(string filewithoutextension, string extension = ".xml")
        {
            int i = 1;
            Func<string> newname = () => { return filewithoutextension + "_" + i + extension; };
            while(File.Exists(newname()))
            {
                i++;
            }
            return newname();
        }
    }
}