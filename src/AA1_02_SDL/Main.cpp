#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <exception>
#include <iostream>
#include <string>

#include "Structs.h"
#include "Constants.h"

int main(int, char*[])
{
	// --- INIT SDL ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw "No es pot inicialitzar SDL subsystems";

	// --- WINDOW ---
	SDL_Window *m_window{ SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	if (m_window == nullptr)
		throw "No es pot inicialitzar SDL_Window";

	// --- RENDERER ---
	SDL_Renderer *m_renderer{ SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (m_renderer == nullptr)
		throw "No es pot inicialitzar SDL_Renderer";

	//-->SDL_Image 
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
	if (!(IMG_Init(imgFlags) & imgFlags)) throw "Error: SDL_image init";

	//-->SDL_TTF
	//-->SDL_Mix

	// --- SPRITES ---
		//Background
	SDL_Texture* bgTexture{ IMG_LoadTexture(m_renderer, RES_IMG "bg.jpg") };
	if (bgTexture == nullptr) throw "Error: bgTexture init";
	SDL_Rect bgRect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };

		//Mouse
	SDL_Texture *playerTexture{ IMG_LoadTexture(m_renderer,RES_IMG "kintoun.png") };
	if (playerTexture == nullptr) throw "Error: Kintoun doesn't exist";
	SDL_Rect playerRect{ 0,0, 100, 50 };
	
	//-->Animated Sprite ---

	// --- TEXT ---
	if (TTF_Init() == -1) throw "Error: SDL_ttf init";
	TTF_Font *font(TTF_OpenFont(RES_TTF"saiyan.ttf", 80));
	if (font == nullptr)throw "Error: saiyan.ttf doesn't exist";
	SDL_Surface *tmpSurf{ TTF_RenderText_Blended(font, "My SDL game", SDL_Color{ 255,10,25,255 }) };
	if (tmpSurf == nullptr) throw "Error: it can't inicialize font";
	SDL_Texture *textTexture(SDL_CreateTextureFromSurface(m_renderer, tmpSurf));
	SDL_Rect textRect{ 170, 50, tmpSurf->w, tmpSurf->h };
	
	// --- AUDIO ---
	const Uint8 mixFlags(MIX_INIT_MP3 | MIX_INIT_OGG);
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1)	//MIX_OpenAudio(frequenia, format, canals, chunksize)
		throw "Errors SDL_MIX init";
	Mix_Music *soundtrack{ Mix_LoadMUS(RES_AU"mainTheme.mp3") };
	if (!soundtrack) throw "Error: mainTheme doesn't exist";
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	Mix_PlayMusic(soundtrack, -1);

	// --- GAME LOOP ---
	SDL_Event event;
	bool isRunning = true;
	while (isRunning) {
		// HANDLE EVENTS
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false;
				break;
			case SDL_MOUSEMOTION:
				mousePos.x = event.motion.x ;
				mousePos.y = event.motion.y ;
				break;
			default:;
			}
		}

		// UPDATE
		playerRect.x += ((mousePos.x - playerRect.w/2)- playerRect.x) / 10;
		playerRect.y += ((mousePos.y- playerRect.h/2) - playerRect.y) / 10;

		// DRAW
		SDL_RenderClear(m_renderer);

			//Background
		SDL_RenderCopy(m_renderer, bgTexture, nullptr, &bgRect);
		
			//Mouse
		SDL_RenderCopy(m_renderer, playerTexture, nullptr, &playerRect);

			//Text
		SDL_RenderCopy(m_renderer, textTexture, nullptr, &textRect);

			//PRINT!
		SDL_RenderPresent(m_renderer);

	}

	// --- DESTROY ---
	SDL_DestroyTexture(bgTexture);
	SDL_DestroyTexture(playerTexture);
	SDL_DestroyTexture(textTexture);
	IMG_Quit();

	Mix_CloseAudio();
	Mix_Quit();

	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	// --- QUIT ---
	SDL_Quit();

	return 0;
}