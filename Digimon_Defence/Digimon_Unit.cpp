#include "Digimon_Unit.h"
#include "ClassPhase.h"

#include <iostream>
#include <windows.h>
#include <atlstr.h>
#include <string>
#include<vector>
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"


using namespace std;
extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;

Digimon_Unit::Digimon_Unit() {}
Digimon_Unit::Digimon_Unit(int x, int y, int power, int at_len, float at_spd, int idx, int price, int unit_num) : xpos(x), ypos(y), power(power), attack_length(at_len), attack_speed(at_spd), Unit_idx(idx), price(price), Unit_num(unit_num)
{
	Init_Unit(Unit_num);
}
void Digimon_Unit::Init_Unit(int stnum)
{
	SDL_Surface * Unit_Surface;
	if(stnum==0 || stnum == 1 || stnum == 4 || stnum == 5)
		Unit_Surface = IMG_Load("../Resources/total_character_1.png"); //디지몬시트 넣기

	else
	Unit_Surface = IMG_Load("../Resources/total_character_2.png"); //디지몬시트 넣기
	
	Unit_texture = SDL_CreateTextureFromSurface(g_renderer, Unit_Surface);
	SDL_FreeSurface(Unit_Surface);

	for (int i = 0; i < Unit_idx; i++)
	{
		Unit_source_rect.push_back(SDL_Rect());
	}
	switch (stnum)
	{
	case 0:
		
		Unit_source_rect[0].x = 0;
		Unit_source_rect[1].x = 400;
		Unit_source_rect[0].y = 180;
		Unit_source_rect[1].y = 80;
		Unit_source_rect[0].w = Unit_source_rect[1].w = 100;
		Unit_source_rect[0].h = Unit_source_rect[1].h = 100;
		Unit_destination_rect.x = xpos;
		Unit_destination_rect.y = ypos;
		Unit_destination_rect.w = 50;
		Unit_destination_rect.h = 50;
		/*아구몬
		d_u[0].push_back(Digimon_Unit(75, 510, 0, 0, 0, 2, 50, 0));
		*/
		
		break;
	case 1:

		
		Unit_source_rect[0].x = 700;
		Unit_source_rect[1].x = 600;
		Unit_source_rect[0].y = Unit_source_rect[1].y = 580;
		Unit_source_rect[0].w = Unit_source_rect[1].w = 100;
		Unit_source_rect[0].h = Unit_source_rect[1].h = 100;
		Unit_destination_rect.x = xpos;
		Unit_destination_rect.y = ypos;
		Unit_destination_rect.w = 50;
		Unit_destination_rect.h = 50;

		/*파피몬
		d_u[1].push_back(Digimon_Unit(180, 510, 0, 0, 0, 2, 50, 0));//stagehandler
		*/

		break;
	case 2:

		Unit_source_rect[0].x = 280;
		Unit_source_rect[1].x = 580;
		Unit_source_rect[2].x = 380;
		Unit_source_rect[0].y = Unit_source_rect[1].y = Unit_source_rect[2].y = 80;
		Unit_source_rect[0].w = Unit_source_rect[1].w = Unit_source_rect[2].w = 100;
		Unit_source_rect[0].h = Unit_source_rect[1].h = Unit_source_rect[2].h = 100;
		Unit_destination_rect.x = xpos;
		Unit_destination_rect.y = ypos;
		Unit_destination_rect.w = 50;
		Unit_destination_rect.h = 50;

		/*파닥몬3
		d_u[i].push_back(Digimon_Unit(285, 510, 0, 0, 0, 3, 50, 0));

		d_u[i].push_back(Digimon_Unit(xpos, ypos, 10 + (i * 100), 100 + (0.8*i), 100, 3, 2, 0));//StageHandler::OurMonster idx=3!!!!!!!!!!!!

		void Digimon_Unit::RenderUnit(int idx, bool atk)
		{
		if (attack_term < attack_speed*0.3 && atk == true)
		SDL_RenderCopy(g_renderer, Unit_texture_2, &Unit_source_rect[2], &Unit_destination_rect);
		else if (attack_term > attack_speed*0.3 && atk == true)
		SDL_RenderCopy(g_renderer, Unit_texture_2, &Unit_source_rect[1], &Unit_destination_rect);
		else if(atk == false)
		SDL_RenderCopy(g_renderer, Unit_texture_2, &Unit_source_rect[0], &Unit_destination_rect);
		}
		*/


		break;
	case 3:

		Unit_source_rect[0].x = 70;
		Unit_source_rect[1].x = 370;
		Unit_source_rect[2].x = 570;
		Unit_source_rect[0].y = Unit_source_rect[1].y = Unit_source_rect[2].y = 480;
		Unit_source_rect[0].w = Unit_source_rect[1].w = Unit_source_rect[2].w = 100;
		Unit_source_rect[0].h = Unit_source_rect[1].h = Unit_source_rect[2].h = 100;
		Unit_destination_rect.x = xpos;
		Unit_destination_rect.y = ypos;
		Unit_destination_rect.w = 50;
		Unit_destination_rect.h = 50;
		/*팔몬3
		d_u[i].push_back(Digimon_Unit(375, 500, 0, 0, 0, 3, 50, 0));
		*/

		break;
	case 4:
		
		Unit_source_rect[0].x = 100;
		Unit_source_rect[1].x = 200;
		Unit_source_rect[0].y = Unit_source_rect[1].y = 380;
		Unit_source_rect[0].w = Unit_source_rect[1].w = 100;
		Unit_source_rect[0].h = Unit_source_rect[1].h = 100;
		Unit_destination_rect.x = xpos;
		Unit_destination_rect.y = ypos;
		Unit_destination_rect.w = 60;
		Unit_destination_rect.h = 60;
		/* 그레이몬
		d_u[i].push_back(Digimon_Unit(75, 505, 0, 0, 0, 2, 50, 0));//stagehandler
		*/
		break;
	case 5:
		
		Unit_source_rect[0].x = 200;
		Unit_source_rect[1].x = 0;
		Unit_source_rect[0].y = Unit_source_rect[1].y = 780;
		Unit_source_rect[0].w = Unit_source_rect[1].w = 100;
		Unit_source_rect[0].h = Unit_source_rect[1].h = 100;
		Unit_destination_rect.x = xpos;
		Unit_destination_rect.y = ypos;
		Unit_destination_rect.w = 60;
		Unit_destination_rect.h = 60;
		/* 갸루몬
		d_u[i].push_back(Digimon_Unit(175, 505, 0, 0, 0, 2, 50, 0));
		*/
		break;
	case 6:
		
		Unit_source_rect[0].x = 70;
		Unit_source_rect[1].x = 270;
		Unit_source_rect[2].x = 370;
		Unit_source_rect[0].y = Unit_source_rect[1].y = Unit_source_rect[2].y = 280;
		Unit_source_rect[0].w = Unit_source_rect[1].w = Unit_source_rect[2].w = 100;
		Unit_source_rect[0].h = Unit_source_rect[1].h = Unit_source_rect[2].h = 100;
		Unit_destination_rect.x = xpos;
		Unit_destination_rect.y = ypos;
		Unit_destination_rect.w = 60;
		Unit_destination_rect.h = 60;
		/*엔젤몬3
		d_u[i].push_back(Digimon_Unit(275+(100*i), 505, 0, 0, 0, 3, 50, 0));
		*/
		break;
	case 7:
		
		Unit_source_rect[0].x = 70;
		Unit_source_rect[1].x = 370;
		Unit_source_rect[2].x = 470;
		Unit_source_rect[0].y = Unit_source_rect[1].y = Unit_source_rect[2].y = 680;
		Unit_source_rect[0].w = Unit_source_rect[1].w = Unit_source_rect[2].w = 100;
		Unit_source_rect[0].h = Unit_source_rect[1].h = Unit_source_rect[2].h = 100;
		Unit_destination_rect.x = xpos;
		Unit_destination_rect.y = ypos;
		Unit_destination_rect.w = 60;
		Unit_destination_rect.h = 60;
		/*
		d_u[i].push_back(Digimon_Unit(375, 505, 0, 0, 0, 3, 50, 0));
		*/
		
		break;
	}
	Init_Attack(stnum);
}
void Digimon_Unit::Init_Attack(int stnum)
{
	SDL_Surface * Attack_Surface;
	Attack_Surface = IMG_Load("../Resources/Attack_Effect.png");
	//SDL_SetColorKey(Attack_Surface, 1, SDL_MapRGB(Attack_Surface->format, 255, 255, 255));
	Attack_texture = SDL_CreateTextureFromSurface(g_renderer, Attack_Surface);
	SDL_FreeSurface(Attack_Surface);

	Attack_source_rect.w = 50;
	Attack_source_rect.h = 50;

	switch (stnum)
	{
	case 0:
		Attack_source_rect.x = 10;
		Attack_source_rect.y = 10;
		break;
	case 1:
		Attack_source_rect.x = 210;
		Attack_source_rect.y = 10;
		break;
	case 2:
		Attack_source_rect.x = 60;
		Attack_source_rect.y = 60;
		break;
	case 3:
		Attack_source_rect.x = 110;
		Attack_source_rect.y = 60;
		break;
	case 4: case 6:
		Attack_source_rect.x = 60;
		Attack_source_rect.y = 10;
		break;
	case 5:
		Attack_source_rect.x = 260;
		Attack_source_rect.y = 10;
		break;
	case 7:
		Attack_source_rect.x = 260;
		Attack_source_rect.y = 60;
		break;
	default:
		break;
	}
}
Digimon_Unit::~Digimon_Unit()
{}
float Digimon_Unit::Attack()
{
	return power;
}
void Digimon_Unit::upgrade()
{
	power += 1.5*power;
	attack_length += 0.5*attack_length;
	attack_speed += attack_speed;

}
void Digimon_Unit::RenderUnit(int stnum, int idx, bool atk)
{

	if (stnum == 2 || stnum == 3 || stnum == 6 || stnum == 7)
	{
		if (attack_term < attack_speed*0.3 && atk == true)
			SDL_RenderCopy(g_renderer, Unit_texture, &Unit_source_rect[2], &Unit_destination_rect);
		else if (attack_term > attack_speed*0.3 && atk == true)
			SDL_RenderCopy(g_renderer, Unit_texture, &Unit_source_rect[1], &Unit_destination_rect);
		else if(atk == false)
			SDL_RenderCopy(g_renderer, Unit_texture, &Unit_source_rect[0], &Unit_destination_rect);
	}
	else
	{
		if (attack_term > attack_speed*0.3 && atk == true)
			SDL_RenderCopy(g_renderer, Unit_texture, &Unit_source_rect[1], &Unit_destination_rect);
		else 
			SDL_RenderCopy(g_renderer, Unit_texture, &Unit_source_rect[0], &Unit_destination_rect);
	}
}

void Digimon_Unit::RenderAttack(int idx, int xpos, int ypos)
{
	attack_term++;
	if (attack_term > attack_speed*0.25)
	{
		float len_x = abs(xpos - Unit_destination_rect.x);
		float len_y = abs(ypos - Unit_destination_rect.y);
		float length = sqrt(len_x*len_x + len_y*len_y);

		if (xpos < Unit_destination_rect.x)
		{
			if (ypos > Unit_destination_rect.y)
			{
				Attack_destination_rect.x = Unit_destination_rect.x + (Unit_destination_rect.w / 2) - len_x * attack_term / attack_speed;
				Attack_destination_rect.y = Unit_destination_rect.y + (Unit_destination_rect.h / 4) + len_y * attack_term / attack_speed;
			}
			else if (ypos <= Unit_destination_rect.y)
			{
				Attack_destination_rect.x = Unit_destination_rect.x + (Unit_destination_rect.w / 2) - len_x * attack_term / attack_speed;
				Attack_destination_rect.y = Unit_destination_rect.y + (Unit_destination_rect.h / 4) - len_y * attack_term / attack_speed;
			}
		}
		else
		{
			if (ypos > Unit_destination_rect.y)
			{
				Attack_destination_rect.x = Unit_destination_rect.x + (Unit_destination_rect.w / 2) + len_x * attack_term / attack_speed;
				Attack_destination_rect.y = Unit_destination_rect.y + (Unit_destination_rect.h / 4) + len_y * attack_term / attack_speed;
			}
			else if (ypos <= Unit_destination_rect.y)
			{
				Attack_destination_rect.x = Unit_destination_rect.x + (Unit_destination_rect.w / 2) + len_x * attack_term / attack_speed;
				Attack_destination_rect.y = Unit_destination_rect.y + (Unit_destination_rect.h / 4) - len_y * attack_term / attack_speed;
			}
		}
		Attack_destination_rect.w = 30;
		Attack_destination_rect.h = 30;
		SDL_RenderCopy(g_renderer, Attack_texture, &Attack_source_rect, &Attack_destination_rect);
	}
	if (attack_term > attack_speed)
		attack_term = 0;
}