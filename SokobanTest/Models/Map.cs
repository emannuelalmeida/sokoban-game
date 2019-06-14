using SokobanTest.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SokobanTest.Models
{
    public class Map
    {
        public int SizeX { get; set; }

        public int SizeY { get; set; }

        private enum MapObject
        {
            Slot = 'S',
            Wall = 'W',
            Box = 'B',
            BoxOnSlot = 'X',
            Nothing = ' '
        }

        private MapObject [] [] Surface { get; set; }

        private int NumBoxes { get; set; }

        private int NumSlots { get; set; }

        private int NumBoxesOnSlot { get; set; }

        /// <summary>
        /// Default constructor for the Map class.
        /// It initializes the matrix, putting wals on the borders and marking the rest as "Nothing"
        /// </summary>
        /// <param name="sizeX">The size x.</param>
        /// <param name="sizeY">The size y.</param>
        public Map (int sizeX, int sizeY)
        {
            Surface = new MapObject[sizeX][];
            for (int i = 0; i < sizeX; i++)
            {
                Surface[i] = new MapObject[sizeY];
            }

            SizeX = sizeX;
            SizeY = sizeY;
        }

        /// <summary>
        /// Attemps to push the element present on the origin coordinates, in the direction indicated by the delta vector.
        /// </summary>
        /// <param name="origX">The original x.</param>
        /// <param name="origY">The original y.</param>
        /// <param name="deltaX">The delta x.</param>
        /// <param name="deltaY">The delta y.</param>
        /// <returns></returns>
        public bool TryPushBox(int origX, int origY, int deltaX, int deltaY)
        {
            if (Surface[origX][origY] == MapObject.Box)
            {
                // First case: The box will be pushed to an empty cell.
                if (Surface[origX + deltaX][origY + deltaY] == MapObject.Nothing)
                {
                    Surface[origX][origY] = MapObject.Nothing;
                    Surface[origX + deltaX][origY + deltaY] = MapObject.Box;
                    return true;
                }
                // Second case: The box will pushed to cell with a slot
                else if (Surface[origX + deltaX][origY + deltaY] == MapObject.Slot)
                {
                    Surface[origX][origY] = MapObject.Nothing;
                    Surface[origX + deltaX][origY + deltaY] = MapObject.BoxOnSlot;
                    NumBoxesOnSlot++;
                    return true;
                }
                // Third case: The box can't be pushed cause there is a wall or another box
                else
                {
                    return false;
                }
            }
            else if (Surface[origX][origY] == MapObject.BoxOnSlot)
            {
                // First case: The box will be pushed to an empty cell.
                if (Surface[origX + deltaX][origY + deltaY] == MapObject.Nothing)
                {
                    Surface[origX][origY] = MapObject.Slot;
                    Surface[origX + deltaX][origY + deltaY] = MapObject.Box;
                    NumBoxesOnSlot--;
                    return true;
                }
                // Second case: The box will pushed to cell with a slot
                else if (Surface[origX + deltaX][origY + deltaY] == MapObject.Slot)
                {
                    Surface[origX][origY] = MapObject.Slot;
                    Surface[origX + deltaX][origY + deltaY] = MapObject.BoxOnSlot;
                    return true;
                }
                // Third case: The box can't be pushed cause there is a wall or another box
                else
                {
                    return false;
                }
            }
            else
            {
                // Can't push a wall...
                return false;
            }
        }

        /// <summary>
        /// Marks the specified position on the map as wall.     
        /// </summary>
        /// <param name="x">The x.</param>
        /// <param name="y">The y.</param>
        public void MarkCellAsWall(int x, int y)
        {
            if (x < SizeX && y < SizeY)
            {
                Surface[x][y] = MapObject.Wall;
            }
        }

        /// <summary>
        /// Marks the specified position on the map as nothing (empty cell).       
        /// </summary>
        /// <param name="x">The x.</param>
        /// <param name="y">The y.</param>
        public void MarkCellAsNothing(int x, int y)
        {
            if (x < SizeX && y < SizeY)
            {
                Surface[x][y] = MapObject.Nothing;
            }
        }

        /// <summary>
        /// Gets the cell by coords.
        /// </summary>
        /// <param name="x">The x.</param>
        /// <param name="y">The y.</param>
        /// <returns></returns>
        public char GetCellByCoords(int x, int y)
        {
            return (char)Surface[x][y];
        }

        /// <summary>
        /// Marks the specified position on the map as box.
        /// </summary>
        /// <param name="x">The x.</param>
        /// <param name="y">The y.</param>
        public void MarkCellAsBox(int x, int y)
        {
            if (x < SizeX && y < SizeY)
            {
                Surface[x][y] = MapObject.Box;
                NumBoxes++;
            }
        }

        /// <summary>
        /// Marks the specified position on the map as slot.        
        /// </summary>
        /// <param name="x">The x.</param>
        /// <param name="y">The y.</param>
        public void MarkCellAsSlot(int x, int y)
        {
            if (x < SizeX && y < SizeY)
            {
                Surface[x][y] = MapObject.Slot;
                NumSlots++;
            }
        }

        /// <summary>
        /// Marks the specified position on the map as a box on a slot.        
        /// </summary>
        /// <param name="x">The x.</param>
        /// <param name="y">The y.</param>
        public void MarkCellAsBoxOnSlot(int x, int y)
        {
            if (x < SizeX && y < SizeY)
            {
                Surface[x][y] = MapObject.BoxOnSlot;
                NumBoxes++;
                NumSlots++;
                NumBoxesOnSlot++;
            }
        }

        /// <summary>
        /// Checks if the referred position allows the hero to walk over it.
        /// It will return true if the position contains "Nothing" or "Slot"
        /// </summary>
        /// <param name="x">The x.</param>
        /// <param name="y">The y.</param>
        /// <returns>
        ///   <c>true</c> if the specified x is walkable; otherwise, <c>false</c>.
        /// </returns>
        public bool IsWalkable(int x, int y)
        {
            if (Surface[x][y] == MapObject.Nothing || Surface[x][y] == MapObject.Slot)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        /// <summary>
        /// Returns true if the map is solved.
        /// The map is solved when the number of boxes is the same the number of boxes in slots.
        /// </summary>
        /// <returns>
        ///   <c>true</c> if [is victory state]; otherwise, <c>false</c>.
        /// </returns>
        public bool IsVictoryState()
        {
            return NumBoxes == NumBoxesOnSlot;
        }

        /// <summary>
        /// Returns true if the number of boxes and slots is the same.
        /// </summary>
        /// <returns>
        ///   <c>true</c> if this instance is valid; otherwise, <c>false</c>.
        /// </returns>
        public bool IsValid()
        {
            if (NumBoxes != NumSlots)
            {
                Console.Error.WriteLine("The number of boxes should be the same as the number of slots.");
                return false;
            }

            return true;
        }
    }
}
