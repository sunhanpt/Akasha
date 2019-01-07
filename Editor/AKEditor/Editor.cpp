#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_syswm.h>
using namespace std;

const int gWinWdefault = 2560 / 2;
const int gWinHdefault = 1600 / 2;
int gWinW = gWinWdefault;
int gWinH = gWinHdefault;

SDL_Window* gWin = nullptr;
bool gFullscreen = false;

void SDLMainLoop()
{
#if ENABLE_AFTERMATH_SUPPORT
	__try
#endif
	{
		bool quit = false;
		SDL_Event e;
		while (!quit)
		{
			while (SDL_PollEvent(&e))
			{
				switch (e.type)
				{
				case SDL_QUIT:
					quit = true;
					break;

				case SDL_KEYDOWN:
					break;

				case SDL_KEYUP:
					break;

				case SDL_MOUSEMOTION:
					break;

				case SDL_MOUSEBUTTONDOWN:
				case SDL_MOUSEBUTTONUP:
					break;

				case SDL_WINDOWEVENT:
					break;

				case SDL_WINDOWEVENT_LEAVE:
					break;

				case SDL_CONTROLLERBUTTONUP:
				case SDL_CONTROLLERBUTTONDOWN:
					break;

				case SDL_JOYDEVICEADDED:
				case SDL_JOYDEVICEREMOVED:
					break;
				}
			}
		}
	}
#if ENABLE_AFTERMATH_SUPPORT
	__except (true)
	{
		DumpAftermathData();
	}
#endif
}

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER))
	{
		fprintf(stderr, "Failed to init SDL: %s\n", SDL_GetError());
		return 1;
	}

	const char* winName = "AKEdtor";

	gWin = SDL_CreateWindow(winName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		gWinW, gWinH, SDL_WINDOW_RESIZABLE /*| SDL_WINDOW_OPENGL*/);
	if (gWin == nullptr)
	{
		return -1;
	}

	

	SDLMainLoop();

	SDL_DestroyWindow(gWin);
	SDL_Quit();
	return 0;
}