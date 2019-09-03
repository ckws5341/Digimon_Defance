#include "Digimon_Monster.h"
#include "ClassPhase.h"

#include <iostream>
#include <windows.h>
#include <atlstr.h>
#include <string>
#include<vector>
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

int Boss_Attack_Term=0;
using namespace std;
extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
Digimon_Monster::Digimon_Monster()
{}
Digimon_Monster::Digimon_Monster(int x, int y, int hp, float spd, int idx, int stnum) : xpos(x), ypos(y), HP(hp), speed(spd), monster_idx(idx)
{
	switch (stnum)
	{
	case 0:
		Init_Monster(DIGIMON_DEFENCE_STAGE1_PHASE);
		break;
	case 1:
		Init_Monster(DIGIMON_DEFENCE_STAGE2_PHASE);
		break;
	case 2:
		Init_Monster(DIGIMON_DEFENCE_STAGE3_PHASE);
		break;
	case 3:
		Init_Monster(DIGIMON_DEFENCE_STAGE4_PHASE);
		break;
	case 4:
		Init_Monster(DIGIMON_DEFENCE_BOSS_PHASE);
		break;
	}
}
void Digimon_Monster::Init_Monster(int stnum)
{
	Monster_Surface = IMG_Load("../Resources/Monster_sprite_sheet.png");
	Monster_texture = SDL_CreateTextureFromSurface(g_renderer, Monster_Surface);
	SDL_FreeSurface(Monster_Surface);
	for (int i = 0; i < monster_idx; i++)
	{
		Monster_source_rect.push_back(SDL_Rect());
	}
	switch (stnum)
	{
	case DIGIMON_DEFENCE_STAGE1_PHASE:
		Monster_source_rect[0].x = 108;
		Monster_source_rect[1].x = 148;
		Monster_source_rect[0].y = Monster_source_rect[1].y = 30;
		Monster_source_rect[0].w = Monster_source_rect[1].w = 40;
		Monster_source_rect[0].h = Monster_source_rect[1].h = 40;
		Monster_destination_rect.x = xpos;
		Monster_destination_rect.y = ypos;
		Monster_destination_rect.w = Monster_source_rect[0].w;
		Monster_destination_rect.h = Monster_source_rect[0].h;
		break;
	case DIGIMON_DEFENCE_STAGE2_PHASE:
		Monster_source_rect[0].x = 148;
		Monster_source_rect[1].x = 190;
		Monster_source_rect[0].y = Monster_source_rect[1].y = 270;
		Monster_source_rect[0].w = Monster_source_rect[1].w = 40;
		Monster_source_rect[0].h = Monster_source_rect[1].h = 45;
		Monster_destination_rect.x = xpos;
		Monster_destination_rect.y = ypos;
		Monster_destination_rect.w = Monster_source_rect[0].w;
		Monster_destination_rect.h = Monster_source_rect[0].h;
		break;
	case DIGIMON_DEFENCE_STAGE3_PHASE:
		Monster_source_rect[0].x = 148;
		Monster_source_rect[1].x = 108;
		Monster_source_rect[0].y = Monster_source_rect[1].y = 110;
		Monster_source_rect[0].w = Monster_source_rect[1].w = 40;
		Monster_source_rect[0].h = Monster_source_rect[1].h = 40;
		Monster_destination_rect.x = xpos;
		Monster_destination_rect.y = ypos;
		Monster_destination_rect.w = Monster_source_rect[0].w;
		Monster_destination_rect.h = Monster_source_rect[0].h;
		break;
	case DIGIMON_DEFENCE_STAGE4_PHASE:
		Monster_source_rect[0].x = 148;
		Monster_source_rect[1].x = 108;
		Monster_source_rect[0].y = Monster_source_rect[1].y = 190;
		Monster_source_rect[0].w = Monster_source_rect[1].w = 40;
		Monster_source_rect[0].h = Monster_source_rect[1].h = 40;
		Monster_destination_rect.x = xpos;
		Monster_destination_rect.y = ypos;
		Monster_destination_rect.w = Monster_source_rect[0].w;
		Monster_destination_rect.h = Monster_source_rect[0].h;
		break;
	case DIGIMON_DEFENCE_BOSS_PHASE:
		Monster_source_rect[0].x = 330;
		Monster_source_rect[1].x = 430;
		Monster_source_rect[0].y = Monster_source_rect[1].y = 350;
		Monster_source_rect[0].w = 70;
		Monster_source_rect[1].w = 90;
		Monster_source_rect[0].h = 100;
		Monster_source_rect[1].h = 90;
		Monster_destination_rect.x = xpos - 50;
		Monster_destination_rect.y = ypos - 110;
		Monster_destination_rect.w = Monster_source_rect[0].w * 3;
		Monster_destination_rect.h = Monster_source_rect[0].h * 3;
		break;
	}
	if (DIGIMON_DEFENCE_BOSS_PHASE)
		Init_Attack(stnum);
}

Digimon_Monster::~Digimon_Monster()
{}

void Digimon_Monster::Init_Attack(int stnum)
{
	SDL_Surface * Attack_Surface;
	Attack_Surface = IMG_Load("../Resources/Attack_Effect.png");
	SDL_SetColorKey(Attack_Surface, 1, SDL_MapRGB(Attack_Surface->format, 255, 255, 255));
	Devil_attack_texture = SDL_CreateTextureFromSurface(g_renderer, Attack_Surface);
	SDL_FreeSurface(Attack_Surface);

	Devil_attack_source_rect.x = 360;
	Devil_attack_source_rect.y = 60;
	Devil_attack_source_rect.w = 50;
	Devil_attack_source_rect.h = 50;

	Devil_attack_destination_rect.x = 465;
	Devil_attack_destination_rect.y = 390;
	Devil_attack_destination_rect.w = 100;
	Devil_attack_destination_rect.h = 100;
}
void Digimon_Monster::Move(int stnum)
{
	switch (stnum)
	{
	case DIGIMON_DEFENCE_STAGE1_PHASE:
		
		xpos += speed;
		Monster_destination_rect.x = xpos;
		break;
	case DIGIMON_DEFENCE_STAGE2_PHASE:
		if (xpos == 150 && ypos <= 350)
		{
			ypos += speed;
			Monster_destination_rect.y = ypos;
		}
		else if (xpos == 400 && ypos >= 200)
		{
			ypos -= speed;
			Monster_destination_rect.y = ypos;
		}
		else
		{
			xpos += speed;
			Monster_destination_rect.x = xpos;
		}
		break;
	case DIGIMON_DEFENCE_STAGE3_PHASE:
		if (xpos == 100 && ypos <= 350)
		{
			ypos += speed;
			Monster_destination_rect.y = ypos;
		}
		else if (xpos == 500 && ypos >= 100)
		{
			ypos -= speed;
			Monster_destination_rect.y = ypos;
		}
		else
		{
			xpos += speed;
			Monster_destination_rect.x = xpos;
		}
		break;
	case DIGIMON_DEFENCE_STAGE4_PHASE:
		
		if (xpos == 900 && ypos >= 200 && ypos < 300)
		{
			ypos += speed;
			Monster_destination_rect.y = ypos;
		}
		else if (ypos == 300 && xpos > 100 && xpos <= 900)
		{
			xpos -= speed;
			Monster_destination_rect.x = xpos;
		}
		else if (xpos == 100 && ypos >= 300 && ypos < 400)
		{
			ypos += speed;
			Monster_destination_rect.y = ypos;
		}
		else
		{
			xpos += speed;
			Monster_destination_rect.x = xpos;
		}

		break;
	case DIGIMON_DEFENCE_BOSS_PHASE:
		xpos += speed;
		Monster_destination_rect.x = xpos;
		break;
	}
	
}
void Digimon_Monster::Render(int idx)
{
	int m_idx;
	if (g_current_game_phase == DIGIMON_DEFENCE_BOSS_PHASE)
	{
		idx = Boss_Attack_Term;
		m_idx = 3000;
		Boss_Attack_Term += 20;
		if (Boss_Attack_Term > 10000) {
			Boss_Attack_Term = 0;
		}
	}
	else
		m_idx = 30;

	if (idx< m_idx)
		SDL_RenderCopy(g_renderer, Monster_texture, &Monster_source_rect[0], &Monster_destination_rect);
	else
		SDL_RenderCopy(g_renderer, Monster_texture, &Monster_source_rect[1], &Monster_destination_rect);
}
int Digimon_Monster::BossRender(int h)
{
	int m_idx, idx;
	idx = Boss_Attack_Term;
	m_idx = 3000;
	Boss_Attack_Term += 20;
	if (Boss_Attack_Term > 10000) {
		Devil_attack_destination_rect.y = 400;
		cout << h << endl;
		h--;
		Boss_Attack_Term = 0;
	}
	cout << HP << endl;
	if (idx < m_idx)
		SDL_RenderCopy(g_renderer, Monster_texture, &Monster_source_rect[0], &Monster_destination_rect);
	else
	{
		SDL_RenderCopy(g_renderer, Monster_texture, &Monster_source_rect[1], &Monster_destination_rect);
		SDL_RenderCopy(g_renderer, Devil_attack_texture, &Devil_attack_source_rect, &Devil_attack_destination_rect);
		Devil_attack_destination_rect.y = Devil_attack_destination_rect.y + Boss_Attack_Term*0.0002;
	}
	return h;
}
void Digimon_Monster::Attacked(int dmg)
{
	HP -= dmg;
}