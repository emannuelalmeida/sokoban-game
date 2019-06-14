using SDL2;
using SokobanTest.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static SDL2.SDL;

namespace SokobanTest
{
    class Program
    {
        static Mechanics mechanics;

        static Graphics graphics;

        static void Main(string[] args)
        {
            #region Architecture initializer code

            if (args.Length == 0)
            {
                Console.WriteLine("Write the path to a map file.");
                Environment.Exit(0);
            }

            Importer importer = new Importer();

            if (!importer.ImportMapFromFIle(args[0]))
            {
                Environment.Exit(1);
            }

            var map = importer.Map;

            mechanics = new Mechanics(importer.Hero, map);         

            #endregion

            #region SDL initializer code
            SDL_Init(SDL_INIT_EVERYTHING);
            
            IntPtr wnd = SDL_CreateWindow("Sokoban Test", 50, 50, map.SizeX * 38, map.SizeY * 38, SDL_WindowFlags.SDL_WINDOW_SHOWN);
            IntPtr ren = SDL_CreateRenderer(wnd, 0, SDL_RendererFlags.SDL_RENDERER_SOFTWARE);
            SDL_RenderPresent(ren);
            graphics = new Graphics(importer.Hero, map, ren);

            #endregion

            // GAME MAIN LOOP STARTS HERE. THIS APP DOESN'T CONTAINS THE "GAME" MODULE THOUGH.

            #region Main loop
            SDL_Event e;
            SDL_Keysym? lastKeyPressed = null;
            bool quit = false;
            int steps = 0;
            while (!quit)
            {
                
                SDL_PollEvent(out e);
                if (e.type == SDL_EventType.SDL_QUIT)
                {
                    quit = true;
                }
                else if (e.type == SDL_EventType.SDL_KEYDOWN && !e.key.keysym.Equals(lastKeyPressed))
                {

                    lastKeyPressed = e.key.keysym;
                    ProcessInput(e.key.keysym, ref quit, ref steps);

                } else if (e.type == SDL_EventType.SDL_KEYUP)
                {
                    lastKeyPressed = null;
                }

                if (map.IsVictoryState())
                {
                    Console.WriteLine($"And the map has been solved in only {steps} steps!! Congratulations :D");
                    graphics.DisplayVictoryScreen();
                    quit = true;
                    SDL_Delay(10000);
                } else
                {
                    graphics.UpdateMap();
                }
            }

            graphics.Shutdown();
            SDL_DestroyRenderer(ren);
            SDL_DestroyWindow(wnd);
            SDL_Quit();

            #endregion
        }

        private static void ProcessInput(SDL_Keysym key, ref bool quit, ref int steps)
        {
            switch (key.sym) { 
                case SDL_Keycode.SDLK_UP:
                    if (mechanics.MoveHero(0, -1))
                    {
                        steps++;
                    }
                    break;
                case SDL_Keycode.SDLK_LEFT:
                    if (mechanics.MoveHero(-1, 0))
                    {
                        steps++;
                    }
                    break;
                case SDL_Keycode.SDLK_DOWN:
                    if (mechanics.MoveHero(0, 1))
                    {
                        steps++;
                    }
                    break;
                case SDL_Keycode.SDLK_RIGHT:
                    if (mechanics.MoveHero(1, 0))
                    {
                        steps++;
                    }
                    break;
                case SDL_Keycode.SDLK_ESCAPE:
                    quit = true;
                    break;
                default:
                    break;
            }
        }
    }
}
