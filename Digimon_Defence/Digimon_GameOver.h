#include "SDL_image.h"

class GameOver
{
public:
	GameOver();
	~GameOver();
	void HandleEvents();
	void Render();
	SDL_Texture * background_texture;
	SDL_Rect background_source_rect;
	SDL_Rect background_destination_rect;
};