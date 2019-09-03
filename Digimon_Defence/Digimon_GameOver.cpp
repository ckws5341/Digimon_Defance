#include "Digimon_Stage.h"
#include "Digimon_GameOver.h"
#include "ClassPhase.h"
#include "SDL_mixer.h"

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern int g_current_game_phase;

extern Mix_Music * overbgm;
extern Mix_Music * opening;

GameOver::GameOver()
{
	SDL_Surface * overbackground_surface = IMG_Load("../Resources/Map/Gameover.png");
	background_texture = SDL_CreateTextureFromSurface(g_renderer, overbackground_surface);
	SDL_FreeSurface(overbackground_surface);

	SDL_QueryTexture(background_texture, NULL, NULL, &background_source_rect.w, &background_source_rect.h);
	background_source_rect.y = 0;
	background_source_rect.x = 0;
	background_destination_rect.x = 0;
	background_destination_rect.y = 0;
	background_destination_rect.w = background_source_rect.w;
	background_destination_rect.h = background_source_rect.h;
}
GameOver :: ~GameOver()
{
	SDL_DestroyTexture(background_texture);
}
void GameOver::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_MOUSEBUTTONUP:

			if (event.button.button == SDL_BUTTON_LEFT)
			{
				int x, y;
				x = event.button.x;
				y = event.button.y;
				//GameOver :: ~GameOver();
				if ((x > 390 && x < 610) && (y > 430 && y < 490)) {
					g_current_game_phase = DIGIMON_DEFENCE_INTRO_PHASE;
					Mix_FreeMusic(overbgm);
					opening = Mix_LoadMUS("../Resources/Sound/opening.mp3");
					Mix_VolumeMusic(128);
					Mix_PlayMusic(opening, -1);
				}
			}
			break;

		default:
			break;
		}
	}
}

void GameOver::Render() {
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer);
	SDL_RenderCopy(g_renderer, background_texture, &background_source_rect, &background_destination_rect);
	SDL_RenderPresent(g_renderer);
}