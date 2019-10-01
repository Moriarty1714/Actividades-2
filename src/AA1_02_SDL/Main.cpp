#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>

#include <exception>
#include <iostream>
#include <string>

//Game general information
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

int main(int, char*[])
{
	// --- INIT SDL ---																																		//Constructor de la librer�a (ya que est� en C++)
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw "No es pot inicialitzar SDL subsystems";																										//Preguntar siempre si se ha podido inicializar
	
	// --- WINDOW ---
	SDL_Window *m_window{ SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	if (m_window == nullptr)
		throw "No es pot inicialitzar SDL_Window";

	// --- RENDERER ---
	SDL_Renderer *m_renderer{ SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (m_renderer == nullptr)
		throw "No es pot inicialitzar SDL_Renderer";

	//-->SDL_Image 
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };																					// Formatos de im�gen a trabajar (lo de dentro son enum) Binari
	if (!(IMG_Init(imgFlags) & imgFlags)) throw "Error: SDL_image init";

	//-->SDL_TTF
	//-->SDL_Mix

	// --- SPRITES ---
		//Background
	SDL_Texture* bgTexture{ IMG_LoadTexture(m_renderer, "../../res/img/bgM.jpg") };															//IMG_LoadTexture(renderizador, donde se encuentra la textura)
	if (bgTexture == nullptr) throw "Error: bgTexture init";
	SDL_Rect bgRect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };																						//Pinta un Rect al 0,0 de la dimensiones de la pantalla
		
		//Dragon
	SDL_Texture *dragonTexture{ IMG_LoadTexture(m_renderer,"../../res/img/dragonM.png") };
	if (dragonTexture);
	//-->Animated Sprite ---

	// --- TEXT ---

	// --- AUDIO ---

	// --- VARIABLES ---
	int x{ 0 };
	int y{ 0 };

	// --- GAME LOOP ---
	SDL_Event event;
	bool isRunning = true;
	while (isRunning) {
		// HANDLE EVENTS
		while (SDL_PollEvent(&event)) {											//Cada vez que entres en el while, dame un evento.
			switch (event.type) {
			case SDL_QUIT:														//Bot�n de cruz de salida
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false;
				break;
			default:;
			}
		}

		// UPDATE
		x+=2;
		y+=2;
		if (x == SCREEN_WIDTH || y == SCREEN_HEIGHT) { x = 0; y = 0; }
		SDL_Rect dragonRect1 { x,y, 200,200 };
		SDL_Rect dragonRect2{ x+200,y, 200,200 };
		SDL_Rect dragonRect3{ x+400,y, 200,200 };
		// DRAW
		SDL_RenderClear(m_renderer);

			//Background
		SDL_RenderCopy(m_renderer, bgTexture, nullptr, &bgRect);	//SDL_RenderCopy(este render, esta textura, - , en este rectangulo)																			
		
			//Dragon
		SDL_RenderCopy(m_renderer, dragonTexture, nullptr, &dragonRect1);
		SDL_RenderCopy(m_renderer, dragonTexture, nullptr, &dragonRect2);
		SDL_RenderCopy(m_renderer, dragonTexture, nullptr, &dragonRect3);
			
			//Print
		SDL_RenderPresent(m_renderer);
	}

	// --- DESTROY ---
	SDL_DestroyTexture(bgTexture);
	SDL_DestroyTexture(dragonTexture);
	IMG_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	// --- QUIT ---
	SDL_Quit();

	return 0;
}