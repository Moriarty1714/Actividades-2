#include <SDL.h>		
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <exception>
#include <iostream>
#include <string>
#include <time.h>

#include "Structs.h"
#include "Constants.h"

int main(int, char*[])
{
	#pragma region INIT SDL
	// --- INIT SDL ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw "No es pot inicialitzar SDL subsystems";
#pragma endregion

	#pragma region INIT WINDOW
	// --- WINDOW ---
	SDL_Window *m_window{ SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	if (m_window == nullptr)
		throw "No espot inicialitzar SDL_Window";
#pragma endregion

	#pragma region INIT RENDER
	// --- RENDERER ---
	SDL_Renderer *m_renderer{ SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (m_renderer == nullptr)
		throw "No es pot inicialitzar SDL_Renderer";
#pragma endregion

	#pragma region INIT IMAGE

	//-->SDL_Image 
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
	if (!(IMG_Init(imgFlags) & imgFlags)) throw "Error: SDL_image init";
#pragma endregion

	//-->SDL_TTF
	//-->SDL_Mix

	#pragma region SPRITES
// --- SPRITES ---
	//Background
	SDL_Texture* bgTexture{ IMG_LoadTexture(m_renderer, RES_IMG "bg.jpg") };
	if (bgTexture == nullptr) throw "Error: bgTexture init";
	SDL_Rect bgRect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };

	//Mouse
	SDL_Texture *mouseTexture{ IMG_LoadTexture(m_renderer,RES_IMG "kintoun.png") };
	if (mouseTexture == nullptr) throw "Error: Kintoun doesn't exist";
	SDL_Rect mouseRect{ 0,0, 100, 50 };
#pragma endregion

	#pragma region ANIMATED SPRITES
	//-->Animated Sprite ---
	SDL_Texture *playerTexture{ IMG_LoadTexture(m_renderer, RES_IMG "sp01.png") };
	SDL_Rect playerRect, playerPosition;
	int textWidth{ 0 }, textHeight{ 0 }, frameWidth{ 0 }, frameHeight {0};
	SDL_QueryTexture(playerTexture, NULL, NULL, &textWidth, &textHeight);
	frameWidth = textWidth / 6; frameHeight = textHeight / 1;
	playerPosition.x = playerPosition.y = 0;
	playerRect.x = playerRect.y = 0;
	int frameTime = 0;

	#pragma endregion

	#pragma region TEXT
	// --- TEXT ---
	if (TTF_Init() == -1) throw "Error: SDL_ttf init";
	TTF_Font *font80(TTF_OpenFont(RES_TTF"saiyan.ttf", 80));
	TTF_Font *font60(TTF_OpenFont(RES_TTF"saiyan.ttf", 60));
	if (font80 == nullptr)throw "Error: saiyan.ttf doesn't exist";
	SDL_Surface *tmpSurf{ TTF_RenderText_Blended(font80, "My SDL game", SDL_Color{ 255, 155, 0}) };	//?Perque no funciona el alpha
	if (tmpSurf == nullptr) throw "Error: it can't inicialize font";

		//Title
	SDL_Texture *titleTextTexture(SDL_CreateTextureFromSurface(m_renderer, tmpSurf));
	SDL_Rect titleRect{ SCREEN_WIDTH/2 - (tmpSurf->w / 2), 50, tmpSurf->w, tmpSurf->h };

		//Play
	tmpSurf = TTF_RenderText_Blended(font80, "PLAY", SDL_Color{ 200,200,200});
		if (tmpSurf == nullptr) throw "Error: it can't inicialize font";
	SDL_Texture *playTextTexture{ (SDL_CreateTextureFromSurface(m_renderer, tmpSurf)) };
	SDL_Rect playRect{ (SCREEN_WIDTH * 2 / 4) - (tmpSurf->w / 2), SCREEN_HEIGHT * 2 / 3, tmpSurf->w, tmpSurf->h };
 
		//Sound
	tmpSurf = TTF_RenderText_Blended(font60, "SOUND", SDL_Color{ 255,255,255 });
		if (tmpSurf == nullptr) throw "Error: it can't inicialize font";
	SDL_Texture *soundTextTexture(SDL_CreateTextureFromSurface(m_renderer, tmpSurf));
	SDL_Rect soundRect{ (SCREEN_WIDTH / 4) - (tmpSurf->w / 2), SCREEN_HEIGHT * 2 / 3, tmpSurf->w, tmpSurf->h };

		//Exit
	tmpSurf = TTF_RenderText_Blended(font60, "EXIT", SDL_Color{ 255,0,255 });
		if (tmpSurf == nullptr) throw "Error: it can't inicialize font";
	SDL_Texture *exitTextTexture(SDL_CreateTextureFromSurface(m_renderer, tmpSurf));
	SDL_Rect exitRect{(SCREEN_WIDTH *3/4) - (tmpSurf->w / 2), SCREEN_HEIGHT * 2 / 3, tmpSurf->w, tmpSurf->h };

	SDL_FreeSurface(tmpSurf);
	TTF_CloseFont(font60);
	TTF_CloseFont(font80);
	#pragma endregion

	#pragma region AUDIO
	// --- AUDIO ---
	const Uint8 mixFlags(MIX_INIT_MP3 | MIX_INIT_OGG);
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1)	//MIX_OpenAudio(frequenia, format, canal, chunksize)
		throw "Errors SDL_MIX init";
	Mix_Music *soundtrack{ Mix_LoadMUS(RES_AU "mainTheme.mp3") };
	if (!soundtrack) throw "Error: mainTheme doesn't exist";
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	Mix_PlayMusic(soundtrack, -1);
	#pragma endregion

	#pragma region TIME
	// --- TIME ---
	clock_t lastTime = clock();
	float timeDown = 10.;//Timer
	float deltaTime;
	#pragma endregion

	// --- EVENT VARIABLES ---
	bool clickLeftButton{false};
	
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
				if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false; //Arreglar
				break;
			case SDL_MOUSEMOTION:
				mousePos.x = event.motion.x ;
				mousePos.y = event.motion.y ;
				break;
			case SDL_MOUSEBUTTONUP:				//SDL_MOUSEPRESSED canviar (fer struct del mouse)
				if (event.button.button == SDL_BUTTON_LEFT) clickLeftButton = true; //Arreglar
				break;
			default:;
			}
		}

		#pragma region UPDATE
		// UPDATE

			//DeltaTime
		deltaTime = (clock() - lastTime);
		lastTime = clock();
		deltaTime /= CLOCKS_PER_SEC;
		timeDown -= deltaTime;
		std::cout << timeDown << std::endl;

			//Mouse update
		mouseRect.x += ((mousePos.x - mouseRect.w/2)- mouseRect.x) / 10;
		mouseRect.y += ((mousePos.y- mouseRect.h/2) - mouseRect.y) / 10;

			//Buttons
		ButtonsMenuManager(soundRect,playRect,exitRect,soundTextTexture,playTextTexture,exitTextTexture,clickLeftButton,isRunning, soundtrack);

		#pragma endregion

		#pragma region DRAW
		// DRAW
		SDL_RenderClear(m_renderer);

			//Background
		SDL_RenderCopy(m_renderer, bgTexture, nullptr, &bgRect);

			//Text
		SDL_RenderCopy(m_renderer, titleTextTexture, nullptr, &titleRect);
		SDL_RenderCopy(m_renderer, playTextTexture, nullptr, &playRect);
		SDL_RenderCopy(m_renderer, soundTextTexture, nullptr, &soundRect);
		SDL_RenderCopy(m_renderer, exitTextTexture, nullptr, &exitRect);
	
			//Mouse
		SDL_RenderCopy(m_renderer, playerTexture, nullptr, &playerRect);

			//Player
		frameTime++;
		if (FPS / frameTime <= 9) {}

			//PRINT!
		SDL_RenderPresent(m_renderer);
		#pragma endregion
	}

	// --- DESTROY ---
	SDL_DestroyTexture(bgTexture);
	SDL_DestroyTexture(mouseTexture);
	SDL_DestroyTexture(titleTextTexture);
	IMG_Quit();

	Mix_CloseAudio();
	Mix_Quit();

	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	// --- QUIT ---
	SDL_Quit();

	return 0;
}