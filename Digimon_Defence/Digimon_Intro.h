#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
class Digimon_Intro
{
private :
	SDL_Texture * background_texture;
	SDL_Rect background_source_rect; 
	SDL_Rect background_destination_rect; 

	TTF_Font *score_font_;
	SDL_Texture *score_text_;
	SDL_Rect score_rect_;
public :
	Digimon_Intro();
	~Digimon_Intro();
	void HandleEvents();
	void Update();
	void Render();
};
