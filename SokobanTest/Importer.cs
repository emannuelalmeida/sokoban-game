using SokobanTest.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SokobanTest
{
    public class Importer
    {
        public Map Map { get; set; }

        public Hero Hero { get; set; }

        /// <summary>
        /// Imports and validates the map from file.
        /// </summary>
        /// <param name="file">The file.</param>
        /// <returns></returns>
        public bool ImportMapFromFIle(string file)
        {
            try
            {
                string[] lines = System.IO.File.ReadAllLines(file);
                ProcessLines(lines);
                return true;
            }
            catch (ArgumentException e)
            {
                Console.Error.WriteLine($"Map validation error: {e.Message}");
                return false;
            }
            catch (Exception)
            {
                Console.Error.WriteLine("Error while trying to import file. Make sure the file exists and it's valid.");
                return false;
            }
        }

        private void ProcessLines(string[] lines)
        {
            // Get the dimensions from the first line, just to guarantee that the rows will have the same size.
            string[] sizes = lines[0].Split(',');
            int sizeX = Int32.Parse(sizes[0]);
            int sizeY = Int32.Parse(sizes[1]);

            if (lines.Length - 1 != sizeY)
            {
                throw new ArgumentException("Specified map size and content mismatch.");
            }

            Map = new Map(sizeX, sizeY); 

            for (int i = 1; i < sizeY + 1; i++)
            {
                if (lines[i].Length != sizeY)
                {
                    throw new ArgumentException("Specified map size and content mismatch.");
                }

                for (int j = 0; j < sizeX; j++)
                {
                    char cell = lines[i][j];
                    switch (cell) {
                        case 'W':
                            Map.MarkCellAsWall(j, i - 1);
                            break;
                        case 'B':
                            Map.MarkCellAsBox(j, i - 1);
                            break;
                        case 'S':
                            Map.MarkCellAsSlot(j, i - 1);
                            break;
                        case 'X':
                            Map.MarkCellAsBoxOnSlot(j, i - 1);
                            break;
                        case ' ':
                            Map.MarkCellAsNothing(j, i - 1);
                            break;
                        case 'H':
                            if (Hero == null)
                            {
                                Hero = new Hero(j, i - 1);
                            } else
                            {
                                throw new ArgumentException("Duplicated position for the hero.");
                            }
                            break;
                        default:
                            throw new ArgumentException($"Unrecognized character '{cell}'");
                    }
                }
            }

            if (!Map.IsValid())
            {
                throw new ArgumentException("There should be the same number of boxes and slots");
            }

            if (Hero == null)
            {
                throw new ArgumentException("There should be one hero on the map");
            }
                       
        }
    }
}
