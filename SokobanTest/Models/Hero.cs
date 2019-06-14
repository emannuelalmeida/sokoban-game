using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SokobanTest.Models
{
    public class Hero
    {
        public int X { get; set; }

        public int Y { get; set; }

        public Hero(int x, int y)
        {
            X = x;
            Y = y;
        }
    }
}
