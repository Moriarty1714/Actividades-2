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
void ButtonsManager(SDL_Rect &soundRect, SDL_Rect &playRect, SDL_Rect &exitRect, SDL_Texture *sText, SDL_Texture *pText, SDL_Texture *eText, SDL_MouseButtonEvent mouse,bool &isRunning) {
	
	//Exit
	if (mousePos.x < (exitRect.x + exitRect.w) && mousePos.x>exitRect.x && mousePos.y < (exitRect.y + exitRect.y) && mousePos.y > exitRect.y)
		SDL_SetTextureColorMod(eText, 255, 0, 0);
	else SDL_SetTextureColorMod(eText, 150, 0, 0);

	//Play
	if (mousePos.x < (playRect.x + playRect.w) && mousePos.x>playRect.x && mousePos.y < (playRect.y + playRect.y) && mousePos.y > playRect.y)
		SDL_SetTextureColorMod(pText, 100, 100, 100);
	else SDL_SetTextureColorMod(pText,0, 0,0);

	//Sound
	if (mousePos.x < (soundRect.x + soundRect.w) && mousePos.x>soundRect.x && mousePos.y < (soundRect.y + soundRect.y) && mousePos.y > soundRect.y) {
		SDL_SetTextureColorMod(sText, 0, 255, 0);

		if (mouse.button = SDL_BUTTON_LEFT) isRunning = false;
	}	else SDL_SetTextureColorMod(sText, 32, 155, 13);

}