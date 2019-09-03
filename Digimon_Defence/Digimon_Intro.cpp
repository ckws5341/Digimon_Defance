#include "Digimon_Intro.h"
#include "ClassPhase.h"

#include <iostream>
#include <windows.h>
#include <atlstr.h>
#include <string>

#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern int g_current_game_phase;
extern Mix_Music * opening;
extern Mix_Music * stage1bgm;

Digimon_Intro::Digimon_Intro()
{

	SDL_Surface* temp_surface = IMG_Load("../Resources/Map/Intro_Background.png");
	background_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(background_texture, NULL, NULL, &background_source_rect.w, &background_source_rect.h);
	background_destination_rect.x = background_source_rect.x = 0;
	background_destination_rect.y = background_source_rect.y = 0;
	background_destination_rect.w = background_source_rect.w;
	background_destination_rect.h = background_source_rect.h;

	opening = Mix_LoadMUS("../Resources/Sound/opening.mp3");
	Mix_VolumeMusic(128);
	Mix_PlayMusic(opening, -1);
}

Digimon_Intro::~Digimon_Intro()
{
	SDL_DestroyTexture(background_texture);
	//if (opening) Mix_FreeMusic(opening);
}
void Digimon_Intro::Update()
{

}

void Digimon_Intro::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_MOUSEBUTTONDOWN:

			if (event.button.button == SDL_BUTTON_LEFT)
			{
				int x, y;
				x = event.button.x;
				y = event.button.y;

				if ((x >= 410 && x <= 580) && (y >= 395 && y <= 440))
				{
					Mix_FreeMusic(opening);
					stage1bgm = Mix_LoadMUS("../Resources/Sound/stage1.mp3");
					Mix_PlayMusic(stage1bgm, -1);
					g_current_game_phase = DIGIMON_DEFENCE_STAGE1_PHASE;
				}
			}
			break;

		default:
			break;
		}
	}
}
void Digimon_Intro::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer);

	SDL_RenderClear(g_renderer);
	SDL_RenderCopy(g_renderer, background_texture, &background_source_rect, &background_destination_rect);

	SDL_RenderPresent(g_renderer);
}