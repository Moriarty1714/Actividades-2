#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

//Vec2 
struct Vec2 {
	int x;
	int y;

	Vec2() { x = 0; y = 0; }
}mousePos;


//Buttons main menu manager
void ButtonsMenuManager(SDL_Rect &soundRect, SDL_Rect &playRect, SDL_Rect &exitRect, SDL_Texture *sText, SDL_Texture *pText, SDL_Texture *eText, bool &cLeft,bool &isRunning, Mix_Music *sTrack) {
	
	//Exit
	if (mousePos.x < (exitRect.x + exitRect.w) && mousePos.x>exitRect.x && mousePos.y  < (exitRect.y + exitRect.h) && mousePos.y > exitRect.y) {	
		SDL_SetTextureColorMod(eText, 255, 0, 0);
		if (cLeft) isRunning = false;
	}	else SDL_SetTextureColorMod(eText, 150, 0, 0);

	//Play
	if (mousePos.x < (playRect.x + playRect.w) && mousePos.x>playRect.x && mousePos.y < (playRect.y + playRect.h) && mousePos.y > playRect.y)
		SDL_SetTextureColorMod(pText, 255, 212, 0);
	else SDL_SetTextureColorMod(pText,0, 0,0);

	//Sound
	switch (Mix_PausedMusic()) {
	case true:
		if (mousePos.x < (soundRect.x + soundRect.w) && mousePos.x>soundRect.x && mousePos.y < (soundRect.y + soundRect.h) && mousePos.y > soundRect.y) {
			SDL_SetTextureColorMod(sText, 0, 250, 0);
			if (cLeft) Mix_PlayMusic(sTrack,-1);
		}
		else SDL_SetTextureColorMod(sText, 250,0,0);
		break;
	case false:
		if (mousePos.x < (soundRect.x + soundRect.w) && mousePos.x>soundRect.x && mousePos.y < (soundRect.y + soundRect.h) && mousePos.y > soundRect.y) {
			SDL_SetTextureColorMod(sText, 250, 0,0);
			if (cLeft) Mix_PauseMusic();
		}
		else SDL_SetTextureColorMod(sText, 0, 250, 0);
		break;
	}
	
	cLeft = false;
}