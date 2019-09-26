#include <SDL.h>
#include <exception>
#include <iostream>
#include <string>


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void Init(SDL_Window* &m_window, SDL_Renderer* &m_renderer) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw "No es pot inicialitzar SDL subsystems";

	m_window = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (m_window == nullptr) throw "No es pot inicialitzar SDL_Window";

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) throw "No es pot inicialitzar SDL_Renderer";

	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void Close(SDL_Window* &m_window, SDL_Renderer* &m_renderer) {
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	m_window = nullptr;
	m_renderer = nullptr;
	SDL_Quit();
}

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;

		if (SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) == 0) {
			SDL_bool done = SDL_FALSE;
			float i = 0;
			while (!done) {
				SDL_Event event;

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				//SDL_RenderClear(renderer);

				SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
				SDL_RenderDrawLine(renderer, 320+i, 200-i, 300-i, 240+i);
				SDL_RenderDrawLine(renderer, 300-i, 240, 340+i, 240);
				SDL_RenderDrawLine(renderer, 340+i, 240+i, 320-i, 200-i);
				SDL_RenderPresent(renderer);

				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT) {
						done = SDL_TRUE;
					}
				}
				i=i+0.01f;
			}
		}

		if (renderer) {
			SDL_DestroyRenderer(renderer);
		}
		if (window) {
			SDL_DestroyWindow(window);
		}
	}
	SDL_Quit();
	return 0;
}