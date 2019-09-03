#include "Digimon_Stage.h"
#include "ClassPhase.h"

#include <iostream>
#include <windows.h>
#include <atlstr.h>
#include <string>

#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "Digimon_StageHandler.h"
extern Mix_Music * opening;
extern Mix_Music * ending;
extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern int g_current_game_phase;
int road_cnt = 0;

Digimon_Stage::Digimon_Stage()
{
}
Digimon_Stage::~Digimon_Stage()
{

}
void Digimon_Stage::HandleEvents()
{
	int win_w, win_h;
	SDL_GetWindowSize(g_window, &win_w, &win_h);

	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_MOUSEBUTTONDOWN:
			break;

		default:
			break;
		}
	}
}
void Digimon_Stage::Update()
{
}

Stage1::Stage1()
{
	SDL_Surface* temp_surface = IMG_Load("../Resources/Map/MAP_FOREST.png");
	background_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(background_texture, NULL, NULL, &background_source_rect.w, &background_source_rect.h);
	background_source_rect.y = 0;
	background_source_rect.x = 0;
	background_destination_rect.x = 0;
	background_destination_rect.y = 0;
	background_destination_rect.w = background_source_rect.w;
	background_destination_rect.h = background_source_rect.h;
	this->Init_Road();


	SDL_Surface * digivice_surface = IMG_Load("../Resources/Item/Digivice.png");
	//SDL_SetColorKey(digivice_surface, 1, SDL_MapRGB(digivice_surface->format, 255, 255, 255));
	digivice_texture = SDL_CreateTextureFromSurface(g_renderer, digivice_surface);
	SDL_FreeSurface(digivice_surface);

	digivice_rect.x = 2;
	digivice_rect.y = 5;
	digivice_rect.w = digivice_rect.h = 45;
	digivice_destination_rect.x = 415;
	digivice_destination_rect.y = 25;
	digivice_destination_rect.w = 55;
	digivice_destination_rect.h = 55;

	



}
void Stage1::Init_Road()
{
	SDL_Surface* temp_surface = IMG_Load("../Resources/Map/total_map_road.png");
	Road_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	for (int i = 0; i < 5; i++)
	{
		Road_source_rect[i].x = 50;
		Road_source_rect[i].y = 51;
		Road_source_rect[i].w = 50;
		Road_source_rect[i].h = 50;
	}
	for (int i = 0; i < 20; i++)
	{
		Road_destination_rect.push_back(SDL_Rect());
		Road_destination_rect[i].x = 50 * i;
		Road_destination_rect[i].y = 300;
		Road_destination_rect[i].w = 50;
		Road_destination_rect[i].h = 50;
	}

}
void Stage1::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer);

	SDL_RenderCopy(g_renderer, background_texture, &background_source_rect, &background_destination_rect);
	for (int i = 0; i < 20; i++)
	{
		SDL_RenderCopy(g_renderer, Road_texture, &Road_source_rect[road_cnt], &Road_destination_rect[i]);
		road_cnt++;
		if (road_cnt == 5)
			road_cnt = 0;
	}

	SDL_RenderCopy(g_renderer, digivice_texture, &digivice_rect, &digivice_destination_rect);
	
}
Stage2::Stage2()
{
	SDL_Surface* temp_surface = IMG_Load("../Resources/Map/MAP OCEAN.png");
	background_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(background_texture, NULL, NULL, &background_source_rect.w, &background_source_rect.h);
	background_source_rect.y = 0;
	background_source_rect.x = 0;
	background_destination_rect.x = 0;
	background_destination_rect.y = 0;
	background_destination_rect.w = background_source_rect.w;
	background_destination_rect.h = background_source_rect.h;
	this->Init_Road();


	SDL_Surface * digivice_surface = IMG_Load("../Resources/Item/Digivice.png");
	//SDL_SetColorKey(digivice_surface, 1, SDL_MapRGB(digivice_surface->format, 255, 255, 255));
	digivice_texture = SDL_CreateTextureFromSurface(g_renderer, digivice_surface);
	SDL_FreeSurface(digivice_surface);

	digivice_rect.x = 2;
	digivice_rect.y = 5;
	digivice_rect.w = digivice_rect.h = 45;
	digivice_destination_rect.x = 415;
	digivice_destination_rect.y = 25;
	digivice_destination_rect.w = 55;
	digivice_destination_rect.h = 55;

}
void Stage2::Init_Road()
{
	SDL_Surface* temp_surface = IMG_Load("../Resources/Map/total_map_road.png");
	Road_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	Road_source_rect[0].x = Road_source_rect[4].x = 50;
	Road_source_rect[1].x = Road_source_rect[5].x = 150;
	Road_source_rect[2].x = 250;
	Road_source_rect[3].x = 350;
	Road_source_rect[0].y = Road_source_rect[1].y = Road_source_rect[2].y = Road_source_rect[3].y = 151;
	Road_source_rect[4].y = Road_source_rect[5].y = 250;
	for (int i = 0; i < 6; i++)
	{
		Road_source_rect[i].w = 50;
		Road_source_rect[i].h = 50;
	}
	for (int i = 0; i < 25; i++)
	{
		Road_destination_rect.push_back(SDL_Rect());
		switch (i)
		{
		case 0: case 1: case 2: case 3:
			Road_destination_rect[i].x = 50 * i;
			Road_destination_rect[i].y = 250;
			Road_destination_rect[i].w = 50;
			Road_destination_rect[i].h = 50;
			break;
		case 4: case 5:		
			Road_destination_rect[i].x = 150;
			Road_destination_rect[i].y = 250 + (i - 3) * 50;
			Road_destination_rect[i].w = 50;
			Road_destination_rect[i].h = 50;
			break;
		case 6: case 7: case 8: case 9: case 10:
			Road_destination_rect[i].x = 150 + (i - 5) * 50;
			Road_destination_rect[i].y = 350;
			Road_destination_rect[i].w = 50;
			Road_destination_rect[i].h = 50;
			break;
		case 11: case 12: case 13:
			Road_destination_rect[i].x = 400;
			Road_destination_rect[i].y = 350 - (i - 10) * 50;
			Road_destination_rect[i].w = 50;
			Road_destination_rect[i].h = 50;
			break;
		default:
			Road_destination_rect[i].x = 400 + (i - 13) * 50;
			Road_destination_rect[i].y = 200;
			Road_destination_rect[i].w = 50;
			Road_destination_rect[i].h = 50;
			break;
		}
	}

}
void Stage2::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer);

	SDL_RenderCopy(g_renderer, background_texture, &background_source_rect, &background_destination_rect);
	for (int i = 0; i < 29; i++)
	{
		switch (i)
		{
		case 3:
			SDL_RenderCopy(g_renderer, Road_texture, &Road_source_rect[2], &Road_destination_rect[i]);
			break;
		case 5:
			SDL_RenderCopy(g_renderer, Road_texture, &Road_source_rect[1], &Road_destination_rect[i]);
			break;
		case 10:
			SDL_RenderCopy(g_renderer, Road_texture, &Road_source_rect[4], &Road_destination_rect[i]);
			break;
		case 13:
			SDL_RenderCopy(g_renderer, Road_texture, &Road_source_rect[5], &Road_destination_rect[i]);
			break;
		default:
			SDL_RenderCopy(g_renderer, Road_texture, &Road_source_rect[0], &Road_destination_rect[i]);
			break;
		}
	}

	SDL_RenderCopy(g_renderer, digivice_texture, &digivice_rect, &digivice_destination_rect);
}
Stage3::Stage3()
{
	SDL_Surface* temp_surface = IMG_Load("../Resources/Map/MAP DESERT.png");
	background_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(background_texture, NULL, NULL, &background_source_rect.w, &background_source_rect.h);
	background_source_rect.y = 0;
	background_source_rect.x = 0;
	background_destination_rect.x = 0;
	background_destination_rect.y = 0;
	background_destination_rect.w = background_source_rect.w;
	background_destination_rect.h = background_source_rect.h;
	this->Init_Road();


	SDL_Surface * digivice_surface = IMG_Load("../Resources/Item/Digivice.png");
	digivice_texture = SDL_CreateTextureFromSurface(g_renderer, digivice_surface);
	upgrade_texture = SDL_CreateTextureFromSurface(g_renderer, digivice_surface);
	upgrade2_texture = SDL_CreateTextureFromSurface(g_renderer, digivice_surface);
	SDL_FreeSurface(digivice_surface);

	upgrade_rect.x = 2;
	upgrade_rect.y = 5;
	upgrade_rect.w = upgrade_rect.h = 45;
	upgrade_destination_rect.x = 85;
	upgrade_destination_rect.y = 475;
	upgrade_destination_rect.w = 30;
	upgrade_destination_rect.h = 30;

	upgrade2_rect.x = 2;
	upgrade2_rect.y = 5;
	upgrade2_rect.w = upgrade2_rect.h = 45;
	upgrade2_destination_rect.x = 190;
	upgrade2_destination_rect.y = 475;
	upgrade2_destination_rect.w = 30;
	upgrade2_destination_rect.h = 30;


	digivice_rect.x = 2;
	digivice_rect.y = 5;
	digivice_rect.w = digivice_rect.h = 45;
	digivice_destination_rect.x = 415;
	digivice_destination_rect.y = 25;
	digivice_destination_rect.w = 55;
	digivice_destination_rect.h = 55;
}
void Stage3::Init_Road()
{
	SDL_Surface* temp_surface = IMG_Load("../Resources/Map/total_map_road.png");
	Road_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	Road_source_rect[0].x = Road_source_rect[0].w = Road_source_rect[0].h = 50;
	Road_source_rect[0].y = 350;

	for (int i = 0; i < 30; i++)
	{
		Road_destination_rect.push_back(SDL_Rect());
		switch (i)
		{
		case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
			Road_destination_rect[i].x = 100;
			Road_destination_rect[i].y = 50 * i;
			Road_destination_rect[i].w = 50;
			Road_destination_rect[i].h = 50;
			break;
		case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15:
			Road_destination_rect[i].x = 100 + (i - 7) * 50;
			Road_destination_rect[i].y = 350;
			Road_destination_rect[i].w = 50;
			Road_destination_rect[i].h = 50;
			break;
		case 16: case 17: case 18: case 19: case 20:
			Road_destination_rect[i].x = 500;
			Road_destination_rect[i].y = 350 - (i - 15) * 50;
			Road_destination_rect[i].w = 50;
			Road_destination_rect[i].h = 50;
			break;

		default:
			Road_destination_rect[i].x = 500 + (i - 20) * 50;
			Road_destination_rect[i].y = 100;
			Road_destination_rect[i].w = 50;
			Road_destination_rect[i].h = 50;
			break;
		}
	}

}
void Stage3::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer);

	SDL_RenderCopy(g_renderer, background_texture, &background_source_rect, &background_destination_rect);
	for (int i = 0; i < 30; i++)
	{
		switch (i)
		{
		case 7:
			SDL_RenderCopy(g_renderer, Road_texture, &Road_source_rect[0], &Road_destination_rect[i]);
			break;
		case 15:
			SDL_RenderCopy(g_renderer, Road_texture, &Road_source_rect[0], &Road_destination_rect[i]);
			break;
		case 20:
			SDL_RenderCopy(g_renderer, Road_texture, &Road_source_rect[0], &Road_destination_rect[i]);
			break;
		default:
			SDL_RenderCopy(g_renderer, Road_texture, &Road_source_rect[0], &Road_destination_rect[i]);
			break;
		}
	}
	SDL_RenderCopy(g_renderer, upgrade_texture, &upgrade_rect, &upgrade_destination_rect);
	SDL_RenderCopy(g_renderer, upgrade2_texture, &upgrade2_rect, &upgrade2_destination_rect);
	SDL_RenderCopy(g_renderer, digivice_texture, &digivice_rect, &digivice_destination_rect);
}
Stage4::Stage4()
{
	SDL_Surface* temp_surface = IMG_Load("../Resources/Map/MAP ICE.png");
	background_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(background_texture, NULL, NULL, &background_source_rect.w, &background_source_rect.h);
	background_source_rect.y = 0;
	background_source_rect.x = 0;
	background_destination_rect.x = 0;
	background_destination_rect.y = 0;
	background_destination_rect.w = background_source_rect.w;
	background_destination_rect.h = background_source_rect.h;
	this->Init_Road();


	SDL_Surface * digivice_surface = IMG_Load("../Resources/Item/Digivice.png");
	digivice_texture = SDL_CreateTextureFromSurface(g_renderer, digivice_surface);	
	upgrade_texture = SDL_CreateTextureFromSurface(g_renderer, digivice_surface);
	upgrade2_texture = SDL_CreateTextureFromSurface(g_renderer, digivice_surface);
	upgrade3_texture = SDL_CreateTextureFromSurface(g_renderer, digivice_surface);
	upgrade4_texture = SDL_CreateTextureFromSurface(g_renderer, digivice_surface);
	SDL_FreeSurface(digivice_surface);

	upgrade_rect.x = 2;
	upgrade_rect.y = 5;
	upgrade_rect.w = upgrade_rect.h = 45;
	upgrade_destination_rect.x = 85;
	upgrade_destination_rect.y = 475;
	upgrade_destination_rect.w = 30;
	upgrade_destination_rect.h = 30;

	upgrade2_rect.x = 2;
	upgrade2_rect.y = 5;
	upgrade2_rect.w = upgrade2_rect.h = 45;
	upgrade2_destination_rect.x = 190;
	upgrade2_destination_rect.y = 475;
	upgrade2_destination_rect.w = 30;
	upgrade2_destination_rect.h = 30;

	upgrade3_rect.x = 2;
	upgrade3_rect.y = 5;
	upgrade3_rect.w = upgrade3_rect.h = 45;
	upgrade3_destination_rect.x = 291;
	upgrade3_destination_rect.y = 475;
	upgrade3_destination_rect.w = 30;
	upgrade3_destination_rect.h = 30;

	upgrade4_rect.x = 2;
	upgrade4_rect.y = 5;
	upgrade4_rect.w = upgrade4_rect.h = 45;
	upgrade4_destination_rect.x = 392;
	upgrade4_destination_rect.y = 475;
	upgrade4_destination_rect.w = 30;
	upgrade4_destination_rect.h = 30;

	digivice_rect.x = 2;
	digivice_rect.y = 5;
	digivice_rect.w = digivice_rect.h = 45;
	digivice_destination_rect.x = 415;
	digivice_destination_rect.y = 25;
	digivice_destination_rect.w = 55;
	digivice_destination_rect.h = 55;

}

void Stage4::Init_Road()
{
	SDL_Surface* temp_surface = IMG_Load("../Resources/Map/total_map_road.png");
	Road_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	Road_source_rect[0].x = Road_source_rect[0].w = Road_source_rect[0].h = 50;
	Road_source_rect[0].y = 550;

	for (int i = 0; i < 58; i++)
	{
		Road_destination_rect.push_back(SDL_Rect());
		switch (i)
		{
		case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18:
			Road_destination_rect[i].x = i * 50;
			Road_destination_rect[i].y = 200;
			Road_destination_rect[i].w = 50;
			Road_destination_rect[i].h = 50;
			break;
		case 19: case 20:
			Road_destination_rect[i].x = 900;
			Road_destination_rect[i].y = 200 + (i - 18) * 50;
			Road_destination_rect[i].w = 50;
			Road_destination_rect[i].h = 50;
			break;
		case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32: case 33: case 34: case 35: case 36:
			Road_destination_rect[i].x = 900 - (i - 20) * 50;
			Road_destination_rect[i].y = 300;
			Road_destination_rect[i].w = 50;
			Road_destination_rect[i].h = 50;
			break;
		case 37: case 38:
			cout << 300 + (i - 36) * 50 << endl;
			Road_destination_rect[i].x = 100;
			Road_destination_rect[i].y = 300 + (i - 36) * 50;
			Road_destination_rect[i].w = 50;
			Road_destination_rect[i].h = 50;
			break;
		default:
			Road_destination_rect[i].x = 100 + (i - 38) * 50;
			Road_destination_rect[i].y = 400;
			Road_destination_rect[i].w = 50;
			Road_destination_rect[i].h = 50;
			break;
		}
	}

}
void Stage4::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer);

	SDL_RenderCopy(g_renderer, background_texture, &background_source_rect, &background_destination_rect);
	for (int i = 0; i < 58; i++)
	{
		switch (i)
		{
		case 7:
			SDL_RenderCopy(g_renderer, Road_texture, &Road_source_rect[0], &Road_destination_rect[i]);
			break;
		case 15:
			SDL_RenderCopy(g_renderer, Road_texture, &Road_source_rect[0], &Road_destination_rect[i]);
			break;
		case 20:
			SDL_RenderCopy(g_renderer, Road_texture, &Road_source_rect[0], &Road_destination_rect[i]);
			break;
		default:
			SDL_RenderCopy(g_renderer, Road_texture, &Road_source_rect[0], &Road_destination_rect[i]);
			break;
		}
	}
	SDL_RenderCopy(g_renderer, upgrade_texture, &upgrade_rect, &upgrade_destination_rect);
	SDL_RenderCopy(g_renderer, upgrade2_texture, &upgrade2_rect, &upgrade2_destination_rect);
	SDL_RenderCopy(g_renderer, upgrade3_texture, &upgrade3_rect, &upgrade3_destination_rect);
	SDL_RenderCopy(g_renderer, upgrade4_texture, &upgrade4_rect, &upgrade4_destination_rect);
	SDL_RenderCopy(g_renderer, digivice_texture, &digivice_rect, &digivice_destination_rect);
}
Boss_Stage::Boss_Stage()
{
	SDL_Surface* temp_surface = IMG_Load("../Resources/Map/MAP_BOSS.png");
	background_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(background_texture, NULL, NULL, &background_source_rect.w, &background_source_rect.h);
	background_source_rect.y = 0;
	background_source_rect.x = 0;
	background_destination_rect.x = 0;
	background_destination_rect.y = 0;
	background_destination_rect.w = background_source_rect.w;
	background_destination_rect.h = background_source_rect.h;
	this->Init_Road();


	SDL_Surface * digivice_surface = IMG_Load("../Resources/Item/Digivice.png");
	digivice_texture = SDL_CreateTextureFromSurface(g_renderer, digivice_surface);
	upgrade_texture = SDL_CreateTextureFromSurface(g_renderer, digivice_surface);
	upgrade2_texture = SDL_CreateTextureFromSurface(g_renderer, digivice_surface);
	upgrade3_texture = SDL_CreateTextureFromSurface(g_renderer, digivice_surface);
	upgrade4_texture = SDL_CreateTextureFromSurface(g_renderer, digivice_surface);
	SDL_FreeSurface(digivice_surface);

	upgrade_rect.x = 2;
	upgrade_rect.y = 5;
	upgrade_rect.w = upgrade_rect.h = 45;
	upgrade_destination_rect.x = 85;
	upgrade_destination_rect.y = 475;
	upgrade_destination_rect.w = 30;
	upgrade_destination_rect.h = 30;

	upgrade2_rect.x = 2;
	upgrade2_rect.y = 5;
	upgrade2_rect.w = upgrade2_rect.h = 45;
	upgrade2_destination_rect.x = 190;
	upgrade2_destination_rect.y = 475;
	upgrade2_destination_rect.w = 30;
	upgrade2_destination_rect.h = 30;

	upgrade3_rect.x = 2;
	upgrade3_rect.y = 5;
	upgrade3_rect.w = upgrade3_rect.h = 45;
	upgrade3_destination_rect.x = 291;
	upgrade3_destination_rect.y = 475;
	upgrade3_destination_rect.w = 30;
	upgrade3_destination_rect.h = 30;

	upgrade4_rect.x = 2;
	upgrade4_rect.y = 5;
	upgrade4_rect.w = upgrade4_rect.h = 45;
	upgrade4_destination_rect.x = 392;
	upgrade4_destination_rect.y = 475;
	upgrade4_destination_rect.w = 30;
	upgrade4_destination_rect.h = 30;

	digivice_rect.x = 2;
	digivice_rect.y = 5;
	digivice_rect.w = digivice_rect.h = 45;
	digivice_destination_rect.x = 415;
	digivice_destination_rect.y = 25;
	digivice_destination_rect.w = 55;
	digivice_destination_rect.h = 55;
}
void Boss_Stage::Init_Road()
{
	SDL_Surface* temp_surface = IMG_Load("../Resources/Map/total_map_road.png");
	Road_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	for (int i = 0; i < 2; i++)
	{
		Road_source_rect[i].x = 100;
		Road_source_rect[i].y = 400;
		Road_source_rect[i].w = 50;
		Road_source_rect[i].h = 50;
	}

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Road_destination_rect.push_back(SDL_Rect());
			Road_destination_rect[i * 5 + j].x = 325 + 50 * i;
			Road_destination_rect[i * 5 + j].y = 175 + 50 * j;
			Road_destination_rect[i * 5 + j].w = 50;
			Road_destination_rect[i * 5 + j].h = 50;
		}
	}

}
void Boss_Stage::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer);

	SDL_RenderCopy(g_renderer, background_texture, &background_source_rect, &background_destination_rect);
	for (int i = 0; i < 35; i++)
	{
		SDL_RenderCopy(g_renderer, Road_texture, &Road_source_rect[0], &Road_destination_rect[i]);
		road_cnt++;
		if (road_cnt == 5)
			road_cnt = 0;
	}
	SDL_RenderCopy(g_renderer, upgrade_texture, &upgrade_rect, &upgrade_destination_rect);
	SDL_RenderCopy(g_renderer, upgrade2_texture, &upgrade2_rect, &upgrade2_destination_rect);
	SDL_RenderCopy(g_renderer, upgrade3_texture, &upgrade3_rect, &upgrade3_destination_rect);
	SDL_RenderCopy(g_renderer, upgrade4_texture, &upgrade4_rect, &upgrade4_destination_rect);
	SDL_RenderCopy(g_renderer, digivice_texture, &digivice_rect, &digivice_destination_rect);

}
Digimon_Ending::Digimon_Ending()
{
	SDL_Surface* temp_surface = IMG_Load("../Resources/Map/Ending.png");
	background_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(background_texture, NULL, NULL, &background_source_rect.w, &background_source_rect.h);
	background_destination_rect.x = background_source_rect.x = 0;
	background_destination_rect.y = background_source_rect.y = 0;
	background_destination_rect.w = background_source_rect.w;
	background_destination_rect.h = background_source_rect.h;

	
}

Digimon_Ending::~Digimon_Ending()
{
}
void Digimon_Ending::endRender()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer);

	SDL_RenderClear(g_renderer);
	SDL_RenderCopy(g_renderer, background_texture, &background_source_rect, &background_destination_rect);


	int win_w, win_h;
	SDL_GetWindowSize(g_window, &win_w, &win_h);

	SDL_RenderPresent(g_renderer);
}
void Digimon_Ending::HandleEvents() {
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
				if ((x > 398 && x < 603) && (y > 415 && y < 470)) {
					g_current_game_phase = DIGIMON_DEFENCE_INTRO_PHASE;
					Mix_FreeMusic(ending);
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