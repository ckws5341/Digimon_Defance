#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <iostream>
#include "ClassPhase.h"
#include "Digimon_Intro.h"
#include "Digimon_Stage.h"
#include "Digimon_StageHandler.h"
#include "Digimon_Clear.h"
#include "Digimon_GameOver.h"

Mix_Music * opening;
Mix_Music * ending;
Mix_Music * stage1bgm;
Mix_Music * stage2bgm;
Mix_Music * stage3bgm;
Mix_Music * stage4bgm;
Mix_Music * bossbgm;
Mix_Music * clearbgm;
Mix_Music * overbgm;
SDL_Window* g_window;
SDL_Renderer* g_renderer;
Uint32 g_last_time_ms = 0;
bool g_flag_running;
int g_frame_time_ms = 8;
int g_current_game_phase;

bool InitializeWindow(const char* title, int xpos, int ypos, int width, int height, int fullscreen);
void ClearWindow();

int main(int argc, char* argv[])
{
	InitializeWindow("Digimon Defence", 100, 100, 1000, 600, false);
	TTF_Init();

	int audio_rate = 44100;//MIX_DEFAULT_FREQUENCY; 주파수
	Uint16 audio_format = MIX_DEFAULT_FORMAT; // 16bit, 사운드 샘플링 크기
	int audio_channels = 2; // stereo , 채널

	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, 4096) < 0) // 4096 = 버퍼 사이즈
	{
		fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
		Mix_CloseAudio();
	}
	else
	{
		// For debug
		Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
		printf("Opened audio at %d Hz %d bit %s\n", audio_rate,
			(audio_format & 0xFF),
			(audio_channels > 2) ? "surround" : (audio_channels > 1) ? "stereo" : "mono");
	}
	StageClear d_clear;
	GameOver d_over;
	Digimon_Intro d_intro;
	Stage1 d_stage1;
	Stage2 d_stage2, d_stage3, d_stage4;
	StageHandler stHandler;
	//Digimon_Boss d_boss;
	Digimon_Ending d_ending;
	while (g_flag_running)
	{
		Uint32 cur_time_ms = SDL_GetTicks();
		if (cur_time_ms - g_last_time_ms < g_frame_time_ms)
			continue;

		if (g_current_game_phase == DIGIMON_DEFENCE_INTRO_PHASE)
		{
			d_intro.HandleEvents();
			d_intro.Update();
			d_intro.Render();
		}
		else if (g_current_game_phase == DIGIMON_DEFENCE_STAGE1_PHASE )
		{
			stHandler.HandleEvents();
			stHandler.Stage1Render();
			stHandler.MoveMonster(DIGIMON_DEFENCE_STAGE1_PHASE);
			stHandler.CheckClear();
		}
		else if (g_current_game_phase == DIGIMON_DEFENCE_STAGE2_PHASE  )
		{
			stHandler.HandleEvents();
			stHandler.Stage2Render();
			stHandler.MoveMonster(DIGIMON_DEFENCE_STAGE2_PHASE);
			stHandler.CheckClear();
		}
		else if (g_current_game_phase == DIGIMON_DEFENCE_STAGE3_PHASE)
		{
			stHandler.HandleEvents();
			stHandler.Stage3Render();
			stHandler.MoveMonster(DIGIMON_DEFENCE_STAGE3_PHASE);
			stHandler.CheckClear();
		}
		else if (g_current_game_phase == DIGIMON_DEFENCE_STAGE4_PHASE)
		{
			stHandler.HandleEvents();
			stHandler.Stage4Render();
			stHandler.MoveMonster(DIGIMON_DEFENCE_STAGE4_PHASE);
			stHandler.CheckClear();
		}
		else if (g_current_game_phase == DIGIMON_DEFENCE_CLEAR_PHASE)
		{
			d_clear.HandleEvents();
			d_clear.Render();
		}
		else if (g_current_game_phase == DIGIMON_DEFENCE_GAMEOVER_PHASE)
		{
			d_over.HandleEvents();
			d_over.Render();
		}
		
		else if (g_current_game_phase == DIGIMON_DEFENCE_BOSS_PHASE)
		{
			stHandler.HandleEvents();
			stHandler.BossStageRender();
			stHandler.MoveMonster(DIGIMON_DEFENCE_BOSS_PHASE);
			stHandler.CheckClear();
		}
		
		else if (g_current_game_phase == DIGIMON_DEFENCE_ENDING_PHASE)
		{
			//d_ending.Update();
			d_ending.endRender();
			d_ending.HandleEvents();
		}
		g_last_time_ms = cur_time_ms;
	}
	Mix_CloseAudio();

	ClearWindow();
	TTF_Quit();
	return 0;
}

bool InitializeWindow(const char* title, int xpos, int ypos, int width, int height, int fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// attempt to initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL init success\n";
		// init the window
		g_window = SDL_CreateWindow(title, xpos, ypos,
			width, height, flags);

		if (g_window != 0) // window init success
		{
			std::cout << "window creation success\n";
			g_renderer = SDL_CreateRenderer(g_window, -1, 0);
			if (g_renderer != 0) // renderer init success
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(g_renderer,
					255, 255, 255, 255);
			}
			else
			{
				std::cout << "renderer init fail\n";
				return false; // renderer init fail
			}
		}
		else
		{
			std::cout << "window init fail\n";
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false; // SDL init fail
	}
	std::cout << "init success\n";
	g_flag_running = true; // everything inited successfully, start the main loop

	return true;

}

void ClearWindow()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(g_window);
	SDL_DestroyRenderer(g_renderer);
	SDL_Quit();
}