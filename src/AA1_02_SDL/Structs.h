#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

enum class State {MENU,GAME,EXIT};

//Vec2 
class Vec2 {
public:
	int x;
	int y;

	Vec2() { x = 0; y = 0; }
}mousePos;

bool colPointToRect(int xPoint, int yPoint, int xRect, int yRect, int wRect, int hRect) {
	return xPoint < (xRect + wRect) && xPoint>xRect && yPoint  < (yRect + hRect) && yPoint > yRect;
}

//Buttons main menu manager ARREGLAR
void ButtonsMenuManager(SDL_Rect &soundRect, SDL_Rect &playRect, SDL_Rect &exitRect, SDL_Texture *sText, SDL_Texture *pText, SDL_Texture *eText, bool &cLeft,bool &isRunning, Mix_Music *sTrack) {
	
	//CANVIAR SDL AL UPDATE
	
	//Exit
	if (colPointToRect(mousePos.x, mousePos.y, exitRect.x, exitRect.y, exitRect.w, exitRect.h)){	
		SDL_SetTextureColorMod(eText, 255, 0, 0);	
		if (cLeft) isRunning = false;
	}	else SDL_SetTextureColorMod(eText, 150, 0, 0);

	//Play
	if (colPointToRect(mousePos.x, mousePos.y, playRect.x, playRect.y, playRect.w, playRect.h))
		SDL_SetTextureColorMod(pText, 255, 212, 0);
	else SDL_SetTextureColorMod(pText,0, 0,0);

	//Sound			
	switch (Mix_PausedMusic()) {
	case true:
		if (colPointToRect(mousePos.x, mousePos.y, soundRect.x, soundRect.y, soundRect.w, soundRect.h)) {
			SDL_SetTextureColorMod(sText, 0, 250, 0);
			if (cLeft) Mix_PlayMusic(sTrack,-1);
		}
		else SDL_SetTextureColorMod(sText, 250,0,0);
		break;
	case false:
		if (colPointToRect(mousePos.x, mousePos.y, soundRect.x, soundRect.y, soundRect.w, soundRect.h)) {
			SDL_SetTextureColorMod(sText, 250, 0,0);
			if (cLeft) Mix_PauseMusic();
		}
		else SDL_SetTextureColorMod(sText, 0, 250, 0);
		break;
	}
	
	cLeft = false;
}