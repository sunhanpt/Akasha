#include <iostream>
#include <SDL.h>
#include <SDL_main.h>

using namespace std;

// 窗口 
SDL_Window *Window = NULL;

bool isRunning = true;

//初始化函数 

int init()
{
	SDL_Init(SDL_INIT_VIDEO);
	Window = SDL_CreateWindow("SDL_Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 240, 400, SDL_WINDOW_SHOWN);  
	if (Window == NULL) {
		return 0;
	}
	else {
		return 1;
	}
}

void quit()
{
	SDL_DestroyWindow(Window);
	SDL_Quit();
}

void handleEvent()
{
	SDL_Event sdlEvent;
	if (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			switch (sdlEvent.key.keysym.sym)
			{
			case 'a':
			{
				int bb = 0;
				break;
			}
				
			default:
				break;
			}
			isRunning = false;
			break;
		default:
			break;
		}
	}
}


int main(int argc, char *argv[])
{
	int initSuccess = init();
	if (!initSuccess) {
		return 0;
	}
	while (isRunning) {
		handleEvent();
	}
	return 0;
}