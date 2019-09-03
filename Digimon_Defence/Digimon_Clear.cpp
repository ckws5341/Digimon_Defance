# include "Digimon_Clear.h"
#include "Digimon_StageHandler.h"
# include "ClassPhase.h"
#include "SDL_mixer.h"

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern int g_current_game_phase;

extern Mix_Music * stage1bgm;
extern Mix_Music * stage2bgm;
extern Mix_Music * stage3bgm;
extern Mix_Music * stage4bgm;
extern Mix_Music * bossbgm;
extern Mix_Music * clearbgm;
extern Mix_Music * overbgm;
extern Mix_Music * ending;

SDL_Surface * clearbackground_surface;
SDL_Texture * background_texture;
SDL_Rect background_source_rect;
SDL_Rect background_destination_rect;
int next_num;

StageClear::StageClear()
{
}

void StageClear::BeforePhase(int before_num) {

	if (before_num == 1) {
		clearbackground_surface = IMG_Load("../Resources/Map/Stage1_Clear.png");
		stage2bgm = Mix_LoadMUS("../Resources/Sound/stage2.mp3");
		Mix_PlayMusic(stage2bgm, -1);
		next_num = 2;
	}
	else if (before_num == 2) {
		clearbackground_surface = IMG_Load("../Resources/Map/Stage2_Clear.png");
		stage3bgm = Mix_LoadMUS("../Resources/Sound/stage3.mp3");
		Mix_PlayMusic(stage3bgm, -1);
		next_num = 3;
	}
	else if (before_num == 3) {
		clearbackground_surface = IMG_Load("../Resources/Map/Stage3_Clear.png");
		stage4bgm = Mix_LoadMUS("../Resources/Sound/stage4.mp3");
		Mix_PlayMusic(stage4bgm, -1);
		next_num = 4;
	}
	else if (before_num == 4) {
		clearbackground_surface = IMG_Load("../Resources/Map/Stage4_Clear.png");
		bossbgm = Mix_LoadMUS("../Resources/Sound/boss.mp3");
		Mix_PlayMusic(bossbgm, -1);
		next_num = 5;
	}
	else if (before_num == 5) {
		clearbackground_surface = IMG_Load("../Resources/Map/Ending.png");
		next_num = 6;
	}
	

	background_texture = SDL_CreateTextureFromSurface(g_renderer, clearbackground_surface);
	SDL_FreeSurface(clearbackground_surface);
	SDL_QueryTexture(background_texture, NULL, NULL, &background_source_rect.w, &background_source_rect.h);
	background_source_rect.y = 0;
	background_source_rect.x = 0;
	background_destination_rect.x = 0;
	background_destination_rect.y = 0;
	background_destination_rect.w = background_source_rect.w;
	background_destination_rect.h = background_source_rect.h;
}
StageClear :: ~StageClear()
{
	SDL_DestroyTexture(background_texture);
}
void StageClear::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				StageClear :: ~StageClear();
				Mix_FreeMusic(clearbgm);
				Mix_VolumeMusic(128);

				if (next_num == 2) {
					g_current_game_phase = DIGIMON_DEFENCE_STAGE2_PHASE;
					
				}
				if (next_num == 3) {
					g_current_game_phase = DIGIMON_DEFENCE_STAGE3_PHASE;
					
				}
				if (next_num == 4) {
					g_current_game_phase = DIGIMON_DEFENCE_STAGE4_PHASE;
					
				}
				if (next_num == 5) {
					g_current_game_phase = DIGIMON_DEFENCE_BOSS_PHASE;
					
				}
				
			}
			break;

		default:
			if (next_num == 6) {
				g_current_game_phase = DIGIMON_DEFENCE_ENDING_PHASE;
				ending = Mix_LoadMUS("../Resources/Sound/ending.mp3");
				Mix_PlayMusic(ending, -1);
			}
			break;
		}
	}
}

void StageClear::Render() {
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer);
	SDL_RenderCopy(g_renderer, background_texture, &background_source_rect, &background_destination_rect);
	SDL_RenderPresent(g_renderer);
}