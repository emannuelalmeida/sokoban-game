using SokobanTest.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SokobanTest
{
    /// <summary>
    /// This class contains all the event methods associated with keyboard keys.
    /// </summary>
    public class Mechanics
    {
        private Hero hero;

        private Map map;

        /// <summary>
        /// Default constructor for the Mechanics module.
        /// </summary>
        /// <param name="hero">The hero.</param>
        /// <param name="map">The map.</param>
        public Mechanics(Hero hero, Map map)
        {
            this.hero = hero;
            this.map = map;
        }

        /// <summary>
        /// Check if it's possible to move the hero in the requested direction. 
        /// The hero can move to cells with slots just as to free spots.
        /// It will return true if a movement was possible.
        /// </summary>
        /// <param name="x">The x.</param>
        /// <param name="y">The y.</param>
        public bool MoveHero(int x, int y)
        {
            if (map.IsWalkable(hero.X + x, hero.Y + y))
            {
                // Nothing prevents the hero from moving freely. Update its coords.
                hero.X += x;
                hero.Y += y;
                Console.WriteLine($"Current hero's position is ({hero.X}, {hero.Y}).");
                return true;
            }
            else if (map.TryPushBox(hero.X + x, hero.Y + y, x, y))
            {
                // The hero can't move freely. Checked if it's possible to push something.
                hero.X += x;
                hero.Y += y;          
                Console.WriteLine($"Current hero's position is ({hero.X}, {hero.Y}). A box was pushed.");
                return true;
            } else
            {
                Console.WriteLine($"It seems our hero has found an obstacle...");
                return false;
            }
        }
    }
}
