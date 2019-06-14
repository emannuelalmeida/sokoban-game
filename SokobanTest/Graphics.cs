using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SokobanTest.Models;
using SDL2;

namespace SokobanTest
{
    class Graphics
    {
        private Hero hero;
        private Map map;
        private IntPtr renderer;

        private IntPtr HeroTex;
        private IntPtr WallTex;
        private IntPtr BoxTex;
        private IntPtr SlotTex;
        private IntPtr BoxOnSlotTex;
        private IntPtr VictoryTex;

        /// <summary>
        /// Default constructor
        /// </summary>
        /// <param name="hero">The hero.</param>
        /// <param name="map">The map.</param>
        /// <param name="renderer">The renderer.</param>
        public Graphics(Hero hero, Map map, IntPtr renderer)
        {
            this.hero = hero;
            this.map = map;
            this.renderer = renderer;

            SDL_image.IMG_Init(SDL_image.IMG_InitFlags.IMG_INIT_JPG);
            SDL.SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

            // Load the images from the media folder.
            var heroImg = SDL_image.IMG_Load("media//hero.jpg");
            var wallImg = SDL_image.IMG_Load("media//wall.jpg");
            var boxImg = SDL_image.IMG_Load("media//box.jpg");
            var slotImg = SDL_image.IMG_Load("media//slot.jpg");
            var boxOnSlotImg = SDL_image.IMG_Load("media//boxOnSlot.jpg");
            var victoryImg = SDL_image.IMG_Load("media//victory.jpg");

            HeroTex = SDL.SDL_CreateTextureFromSurface(renderer, heroImg);
            WallTex = SDL.SDL_CreateTextureFromSurface(renderer, wallImg);
            BoxTex = SDL.SDL_CreateTextureFromSurface(renderer, boxImg);
            SlotTex = SDL.SDL_CreateTextureFromSurface(renderer, slotImg);
            BoxOnSlotTex = SDL.SDL_CreateTextureFromSurface(renderer, boxOnSlotImg);
            VictoryTex = SDL.SDL_CreateTextureFromSurface(renderer, victoryImg);
        }

        /// <summary>
        /// Redraws the map to the selected interface.
        /// </summary>
        public void UpdateMap()
        {
            SDL.SDL_RenderClear(renderer);
            var tileSrc = new SDL.SDL_Rect() { x = 0, y = 0, w = 35, h = 35 };

            for (int i = 0; i < map.SizeX; i++)
            {
                for (int j = 0; j < map.SizeY; j++)
                {
                   
                    IntPtr mapCell;
                    switch (map.GetCellByCoords(i, j))
                    {
                        case 'W':
                            mapCell = WallTex;
                            break;
                        case 'B':
                            mapCell = BoxTex;
                            break;
                        case 'X':
                            mapCell = BoxOnSlotTex;
                            break;
                        case 'S':
                            mapCell = SlotTex;
                            break;
                        default:
                            continue;                        
                    }

                    var tileArea = new SDL.SDL_Rect()
                    {
                        h = 35,
                        w = 35,
                        x = 2 + 35 * i,
                        y = 2 + 35 * j
                    };

                    SDL.SDL_RenderCopy(renderer, mapCell, ref tileSrc, ref tileArea);
                }
            }

            var heroArea = new SDL.SDL_Rect()
            {
                h = 35,
                w = 35,
                x = 2 + hero.X * 35,
                y = 2 + hero.Y * 35
            };
            SDL.SDL_RenderCopy(renderer, HeroTex, ref tileSrc, ref heroArea);

            SDL.SDL_RenderPresent(renderer);
        }

        /// <summary>
        /// Shows a victory message.
        /// </summary>
        /// <param name="steps">The steps.</param>
        public void DisplayVictoryScreen()
        {
            SDL.SDL_RenderClear(renderer);
            SDL.SDL_RenderCopy(renderer, VictoryTex, IntPtr.Zero, IntPtr.Zero);

        }

        /// <summary>
        /// Destroys the memory objects related to this element.
        /// </summary>
        public void Shutdown()
        {
            SDL_image.IMG_Quit();
        }
    }
}
