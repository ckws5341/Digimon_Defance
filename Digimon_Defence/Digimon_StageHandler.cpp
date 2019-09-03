#include "ClassPhase.h"
#include "Digimon_StageHandler.h"

#include <iostream>
#include <windows.h>
#include <atlstr.h>
#include <string>
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "Digimon_Clear.h"

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern int g_current_game_phase;
int unit_num;

SDL_Color black = { 0,0,0,0 };
SDL_Color white = { 255, 255, 255, 0 };
StageClear stage_clear;
extern Mix_Music * stage1bgm;
extern Mix_Music * stage2bgm;
extern Mix_Music * stage3bgm;
extern Mix_Music * stage4bgm;
extern Mix_Music * bossbgm;
extern Mix_Music * clearbgm;
extern Mix_Music * overbgm;

StageHandler::StageHandler() : m_count(0), m_respawn(0), st1(),st2(),st3(), st4(), able_to_attack(false), attack_delay(0), money(500), heart(5)
{
	bool overlap = true;
	bool createmonster = false;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 10; j++)
			attack_ing[i][j] = false;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			switch (i)
			{
			case 0:
				d_m[i].push_back(Digimon_Monster(-50, 300, 1, 0.8, 2, i)); // x, y, hp, spd
				break;
			case 1:
				d_m[i].push_back(Digimon_Monster(-50, 250, 14, 2, 2, i));//14
				break;
			case 2:
				d_m[i].push_back(Digimon_Monster(100, -50, 241, 0.5, 3, i));//241
				break;
			case 3:
				d_m[i].push_back(Digimon_Monster(-50, 200, 165, 2.5, 3, i));//165
				break;
			case 4:
				Boss = Digimon_Monster(450, 250, 5000, 0, 2, i);//5000
				break;

			}
		}
	}

	d_u[0].push_back(Digimon_Unit(75, 510, 0, 0, 0, 2, 50, 0));
	d_u[1].push_back(Digimon_Unit(180, 510, 0, 0, 0, 2, 75, 1));
	d_u[2].push_back(Digimon_Unit(285, 510, 0, 0, 0, 3, 75, 2));
	d_u[3].push_back(Digimon_Unit(380, 505, 0, 0, 0, 3, 100, 3));

	d_u[4].push_back(Digimon_Unit(-100, 505, 0, 0, 0, 2, 125, 4));
	d_u[5].push_back(Digimon_Unit(-100, 505, 0, 0, 0, 2, 150, 5));
	d_u[6].push_back(Digimon_Unit(-100, 505, 0, 0, 0, 3, 200, 6));
	d_u[7].push_back(Digimon_Unit(-100, 503, 0, 0, 0, 3, 150, 7));

	game_font_ = TTF_OpenFont("../Resources/Font/ChessType.ttf", 45);
	heart_font_ = TTF_OpenFont("../Resources/Font/Chunq.ttf", 50);

	SDL_Surface * multiple_surface = TTF_RenderText_Blended(heart_font_, "X", white);
	multiple_src_rect.x = multiple_src_rect.y = 0;
	multiple_src_rect.w = multiple_surface->w;
	multiple_src_rect.h = multiple_surface->h;
	text_multiple = SDL_CreateTextureFromSurface(g_renderer, multiple_surface);
	SDL_FreeSurface(multiple_surface);

	multiple_dest_rect.x = 500;
	multiple_dest_rect.y = 28;
	multiple_dest_rect.w = multiple_src_rect.w;
	multiple_dest_rect.h = multiple_src_rect.h;
	
	heart_dest_rect.x = 560;
	heart_dest_rect.y = 28;
	UpdateheartTexture(heart);
	
	money_dest_rect.x = 800;
	money_dest_rect.y = 525;

}

bool StageHandler::OurMonster(int xpos, int ypos, int i)
{
	switch (i)
	{
	case 0:
		d_u[i].push_back(Digimon_Unit(xpos, ypos, 10, 100, 100, 2, 50, i)); // atk, range, spd,idx,money
		break;
	case 1:
		d_u[i].push_back(Digimon_Unit(xpos, ypos, 20, 100, 100, 2, 75, i));
		break;
	case 2:
		d_u[i].push_back(Digimon_Unit(xpos, ypos, 10, 200, 100, 3, 75, i));
		break;
	case 3:
		d_u[i].push_back(Digimon_Unit(xpos, ypos, 40, 70, 100, 3, 100, i));
		break;
	case 4:
		d_u[i].push_back(Digimon_Unit(xpos, ypos, 50, 140, 100, 2, 125, i));
		break;
	case 5:
		d_u[i].push_back(Digimon_Unit(xpos, ypos, 70, 150, 100, 2, 150, i));
		break;
	case 6:
		d_u[i].push_back(Digimon_Unit(xpos, ypos, 80, 250, 100, 3, 200, i));
		break;
	case 7:
		d_u[i].push_back(Digimon_Unit(xpos, ypos, 165, 70, 100, 3, 150, i));
		break;
	}
	return true;
}

StageHandler::~StageHandler() 
{
	SDL_DestroyTexture(text_heart);
	SDL_DestroyTexture(text_multiple);
	SDL_DestroyTexture(text_money);

}
void StageHandler::Stage1Render()
{

	float len_x;
	float len_y;
	st1.Render();
	
	for (int i = 0; i < d_m->size(); i++)
	{
		if (d_m[0][i].HP > 0)
		{
			d_m[0][i].Render(m_respawn);
		}
	}
	for (int k = 0; k < 2; k++)
	{
		for (int i = 0; i < d_u[k].size(); i++)
		{
			for (int j = 0; j < 30 - diecount; j++)
			{
				float d_center_x = d_u[k][i].Unit_destination_rect.x + d_u[k][i].Unit_destination_rect.w / 2;
				float d_center_y = d_u[k][i].Unit_destination_rect.y + d_u[k][i].Unit_destination_rect.h / 2;
				float m_center_x = d_m[0][j].Monster_destination_rect.x + d_m[0][j].Monster_destination_rect.w / 2;
				float m_center_y = d_m[0][j].Monster_destination_rect.y + d_m[0][j].Monster_destination_rect.h / 2;

				if ((d_center_x + d_u[k][i].attack_length >m_center_x &&d_center_x - d_u[k][i].attack_length < m_center_x) &&
					(d_center_y + d_u[k][i].attack_length > m_center_y && d_center_y - d_u[k][i].attack_length < m_center_y))
				{
					if (d_m[0][j].HP > 0 && d_m[0][j].Monster_destination_rect.x > 0 && !d_u[k][i].motionattack) {

						if (!attack_ing[k][i])
						{
							AttackMonster(k, j, i);
							able_to_attack = true;
							who_attack = j;
							d_u[k][i].Attack_End_destination_rect.x = d_m[0][j].Monster_destination_rect.x;
							d_u[k][i].Attack_End_destination_rect.y = d_m[0][j].Monster_destination_rect.y;
							attack_ing[k][i] = false;
						}
						break;
					}
				}

				else
				{
					d_u[k][i].Attack_End_destination_rect.x = d_m[0][who_attack].Monster_destination_rect.x;
					d_u[k][i].Attack_End_destination_rect.y = d_m[0][who_attack].Monster_destination_rect.y;
					able_to_attack = false;

				}

			}
			if ((k == 0 && Agu_upgrage) || (k == 1 && Papi_upgrage) || (k == 2 && Pad_upgrage) || (k == 3 && Pal_upgrage))
			{
				switch (k)
				{
				case 0:
					d_u[4][0].Unit_destination_rect.x = 75;
					break;
				case 1:
					d_u[5][0].Unit_destination_rect.x = 180;
					break;
				case 2:
					d_u[6][0].Unit_destination_rect.x = 285;
					break;
				case 3:
					d_u[7][0].Unit_destination_rect.x = 380;
					break;
				}
				d_u[k][0].Unit_destination_rect.x = -100;
			}
			d_u[k][i].RenderUnit(k, m_respawn, able_to_attack);


			if (able_to_attack)
			{
				d_u[k][i].RenderAttack(k, d_u[k][i].Attack_End_destination_rect.x, d_u[k][i].Attack_End_destination_rect.y);
				if (abs(d_u[k][i].Unit_destination_rect.x - d_m[0][who_attack].Monster_destination_rect.x) >= d_u[k][i].attack_length && abs(d_u[k][i].Unit_destination_rect.y - d_m[0][who_attack].Monster_destination_rect.y) >= d_u[k][i].attack_length)
					attack_ing[k][i] = false;
			}
		}
	}

	SDL_RenderCopy(g_renderer, text_multiple, &multiple_src_rect, &multiple_dest_rect);
	SDL_RenderCopy(g_renderer, text_money, &money_src_rect, &money_dest_rect);
	SDL_RenderCopy(g_renderer, text_heart, &heart_src_rect, &heart_dest_rect);
	SDL_RenderPresent(g_renderer);
}
void StageHandler::Stage2Render()
{
	able_to_attack = false;
	float len_x;
	float len_y;
	st2.Render();
	for (int i = 0; i < d_m[1].size(); i++)
	{
		if (d_m[1][i].HP > 0)
		{
			d_m[1][i].Render(m_respawn);
		}
	}
	for (int k = 0; k < 8; k++)
	{
		for (int i = 0; i < d_u[k].size(); i++)
		{
			for (int j = 0; j < 30 - diecount; j++)
			{
				float d_center_x = d_u[k][i].Unit_destination_rect.x + d_u[k][i].Unit_destination_rect.w / 2;
				float d_center_y = d_u[k][i].Unit_destination_rect.y + d_u[k][i].Unit_destination_rect.h / 2;
				float m_center_x = d_m[1][j].Monster_destination_rect.x + d_m[1][j].Monster_destination_rect.w / 2;
				float m_center_y = d_m[1][j].Monster_destination_rect.y + d_m[1][j].Monster_destination_rect.h / 2;

				if ((d_center_x + d_u[k][i].attack_length >m_center_x &&d_center_x - d_u[k][i].attack_length < m_center_x) &&
					(d_center_y + d_u[k][i].attack_length > m_center_y && d_center_y - d_u[k][i].attack_length < m_center_y))
				{
					if (d_m[1][j].HP > 0 && d_m[1][j].Monster_destination_rect.x > 0 && !d_u[k][i].motionattack) {
						
						if (!attack_ing[k][i])
						{
							AttackMonster(k, j, i);
							able_to_attack = true;
							who_attack = j;
							d_u[k][i].Attack_End_destination_rect.x = d_m[1][j].Monster_destination_rect.x;
							d_u[k][i].Attack_End_destination_rect.y = d_m[1][j].Monster_destination_rect.y;
							attack_ing[k][i] = false;
						}
						break;
					}
				}

				else
				{
					d_u[k][i].Attack_End_destination_rect.x = d_m[1][who_attack].Monster_destination_rect.x;
					d_u[k][i].Attack_End_destination_rect.y = d_m[1][who_attack].Monster_destination_rect.y;
					able_to_attack = false;
					
				}

			}
			if ((k == 0 && Agu_upgrage) || (k == 1 && Papi_upgrage) || (k == 2 && Pad_upgrage) || (k == 3 && Pal_upgrage))
			{
				switch (k)
				{
				case 0:
					d_u[4][0].Unit_destination_rect.x = 75;
					break;
				case 1:
					d_u[5][0].Unit_destination_rect.x = 180;
					break;
				case 2:
					d_u[6][0].Unit_destination_rect.x = 285;
					break;
				case 3:
					d_u[7][0].Unit_destination_rect.x = 380;
					break;
				}
				d_u[k][0].Unit_destination_rect.x = -100;
			}
			d_u[k][i].RenderUnit(k, m_respawn, able_to_attack);


			if (able_to_attack)
			{
				d_u[k][i].RenderAttack(k, d_u[k][i].Attack_End_destination_rect.x, d_u[k][i].Attack_End_destination_rect.y);
				if (abs(d_u[k][i].Unit_destination_rect.x - d_m[1][who_attack].Monster_destination_rect.x) >= d_u[k][i].attack_length && abs(d_u[k][i].Unit_destination_rect.y - d_m[1][who_attack].Monster_destination_rect.y) >= d_u[k][i].attack_length)
					attack_ing[k][i] = false;
			}
		}
	}

	SDL_RenderCopy(g_renderer, text_multiple, &multiple_src_rect, &multiple_dest_rect);
	SDL_RenderCopy(g_renderer, text_money, &money_src_rect, &money_dest_rect);
	SDL_RenderCopy(g_renderer, text_heart, &heart_src_rect, &heart_dest_rect);
	SDL_RenderPresent(g_renderer);
}
void StageHandler::Stage3Render()
{
	able_to_attack = false;
	float len_x;
	float len_y;
	st3.Render();
	for (int i = 0; i < d_m[2].size(); i++)
	{
		if (d_m[2][i].HP > 0)
		{
			d_m[2][i].Render(m_respawn);
		}
	}
	for (int k = 0; k < 8; k++)
	{
		for (int i = 0; i < d_u[k].size(); i++)
		{
			for (int j = 0; j < 30 - diecount; j++)
			{
				float d_center_x = d_u[k][i].Unit_destination_rect.x + d_u[k][i].Unit_destination_rect.w / 2;
				float d_center_y = d_u[k][i].Unit_destination_rect.y + d_u[k][i].Unit_destination_rect.h / 2;
				float m_center_x = d_m[2][j].Monster_destination_rect.x + d_m[2][j].Monster_destination_rect.w / 2;
				float m_center_y = d_m[2][j].Monster_destination_rect.y + d_m[2][j].Monster_destination_rect.h / 2;

				if ((d_center_x + d_u[k][i].attack_length >m_center_x &&d_center_x - d_u[k][i].attack_length < m_center_x) &&
					(d_center_y + d_u[k][i].attack_length > m_center_y && d_center_y - d_u[k][i].attack_length < m_center_y))
				{
					if (d_m[2][j].HP > 0 && d_m[2][j].Monster_destination_rect.x > 0 && !d_u[k][i].motionattack) {

						if (!attack_ing[k][i])
						{
							AttackMonster(k, j, i);
							able_to_attack = true;
							who_attack = j;
							d_u[k][i].Attack_End_destination_rect.x = d_m[2][j].Monster_destination_rect.x;
							d_u[k][i].Attack_End_destination_rect.y = d_m[2][j].Monster_destination_rect.y;
							attack_ing[k][i] = false;
						}
						break;
					}
				}

				else
				{
					d_u[k][i].Attack_End_destination_rect.x = d_m[2][who_attack].Monster_destination_rect.x;
					d_u[k][i].Attack_End_destination_rect.y = d_m[2][who_attack].Monster_destination_rect.y;
					able_to_attack = false;

				}

			}
			if ((k == 0 && Agu_upgrage) || (k == 1 && Papi_upgrage) || (k == 2 && Pad_upgrage) || (k == 3 && Pal_upgrage))
			{
				switch (k)
				{
				case 0:
					d_u[4][0].Unit_destination_rect.x = 75;
					break;
				case 1:
					d_u[5][0].Unit_destination_rect.x = 180;
					break;
				case 2:
					d_u[6][0].Unit_destination_rect.x = 285;
					break;
				case 3:
					d_u[7][0].Unit_destination_rect.x = 380;
					break;
				}
				d_u[k][0].Unit_destination_rect.x = -100;
			}
			d_u[k][i].RenderUnit(k, m_respawn, able_to_attack);


			if (able_to_attack)
			{
				d_u[k][i].RenderAttack(k, d_u[k][i].Attack_End_destination_rect.x, d_u[k][i].Attack_End_destination_rect.y);
				if (abs(d_u[k][i].Unit_destination_rect.x - d_m[2][who_attack].Monster_destination_rect.x) >= d_u[k][i].attack_length && abs(d_u[k][i].Unit_destination_rect.y - d_m[2][who_attack].Monster_destination_rect.y) >= d_u[k][i].attack_length)
					attack_ing[k][i] = false;
			}
		}
	}

	SDL_RenderCopy(g_renderer, text_multiple, &multiple_src_rect, &multiple_dest_rect);
	SDL_RenderCopy(g_renderer, text_money, &money_src_rect, &money_dest_rect);
	SDL_RenderCopy(g_renderer, text_heart, &heart_src_rect, &heart_dest_rect);
	SDL_RenderPresent(g_renderer);
}
void StageHandler::Stage4Render()
{
	able_to_attack = false;
	float len_x;
	float len_y;
	st4.Render();
	for (int i = 0; i < d_m[3].size(); i++)
	{
		if (d_m[3][i].HP > 0)
		{
			d_m[3][i].Render(m_respawn);
		}
	}
	for (int k = 0; k < 8; k++)
	{
		for (int i = 0; i < d_u[k].size(); i++)
		{
			for (int j = 0; j < 30 - diecount; j++)
			{
				float d_center_x = d_u[k][i].Unit_destination_rect.x + d_u[k][i].Unit_destination_rect.w / 2;
				float d_center_y = d_u[k][i].Unit_destination_rect.y + d_u[k][i].Unit_destination_rect.h / 2;
				float m_center_x = d_m[3][j].Monster_destination_rect.x + d_m[3][j].Monster_destination_rect.w / 2;
				float m_center_y = d_m[3][j].Monster_destination_rect.y + d_m[3][j].Monster_destination_rect.h / 2;

				if ((d_center_x + d_u[k][i].attack_length >m_center_x &&d_center_x - d_u[k][i].attack_length < m_center_x) &&
					(d_center_y + d_u[k][i].attack_length > m_center_y && d_center_y - d_u[k][i].attack_length < m_center_y))
				{
					if (d_m[3][j].HP > 0 && d_m[3][j].Monster_destination_rect.x > 0 && !d_u[k][i].motionattack) {

						if (!attack_ing[k][i])
						{
							AttackMonster(k, j, i);
							able_to_attack = true;
							who_attack = j;
							d_u[k][i].Attack_End_destination_rect.x = d_m[3][j].Monster_destination_rect.x;
							d_u[k][i].Attack_End_destination_rect.y = d_m[3][j].Monster_destination_rect.y;
							attack_ing[k][i] = false;
						}
						break;
					}
				}

				else
				{
					d_u[k][i].Attack_End_destination_rect.x = d_m[3][who_attack].Monster_destination_rect.x;
					d_u[k][i].Attack_End_destination_rect.y = d_m[3][who_attack].Monster_destination_rect.y;
					able_to_attack = false;

				}

			}
			if ((k == 0 && Agu_upgrage) || (k == 1 && Papi_upgrage) || (k == 2 && Pad_upgrage) || (k == 3 && Pal_upgrage))
			{
				switch (k)
				{
				case 0:
					d_u[4][0].Unit_destination_rect.x = 75;
					break;
				case 1:
					d_u[5][0].Unit_destination_rect.x = 180;
					break;
				case 2:
					d_u[6][0].Unit_destination_rect.x = 285;
					break;
				case 3:
					d_u[7][0].Unit_destination_rect.x = 380;
					break;
				}
				d_u[k][0].Unit_destination_rect.x = -100;
			}
			d_u[k][i].RenderUnit(k, m_respawn, able_to_attack);


			if (able_to_attack)
			{
				d_u[k][i].RenderAttack(k, d_u[k][i].Attack_End_destination_rect.x, d_u[k][i].Attack_End_destination_rect.y);
				if (abs(d_u[k][i].Unit_destination_rect.x - d_m[3][who_attack].Monster_destination_rect.x) >= d_u[k][i].attack_length && abs(d_u[k][i].Unit_destination_rect.y - d_m[3][who_attack].Monster_destination_rect.y) >= d_u[k][i].attack_length)
					attack_ing[k][i] = false;
			}
		}
	}

	SDL_RenderCopy(g_renderer, text_multiple, &multiple_src_rect, &multiple_dest_rect);
	SDL_RenderCopy(g_renderer, text_money, &money_src_rect, &money_dest_rect);
	SDL_RenderCopy(g_renderer, text_heart, &heart_src_rect, &heart_dest_rect);
	SDL_RenderPresent(g_renderer);
}
void StageHandler::BossStageRender()
{

	float len_x;
	float len_y;
			

	for (int i = 0; i < 4; i++) {
		d_u[i][0].Unit_destination_rect.y = 500;
		d_u[i][0].Unit_destination_rect.x = 120 + (i * 85);
		d_u[i][0].Unit_destination_rect.w = 50;
		d_u[i][0].Unit_destination_rect.h = 55;
		if (i == 2) {
			d_u[i][0].Unit_destination_rect.x += 8;
			d_u[i][0].Unit_destination_rect.y += 5;
		}
		
		if (i == 3)
		d_u[i][0].Unit_destination_rect.x += 4;
	}
	
	BS.Render();

	heart = Boss.BossRender(heart);
	UpdateheartTexture(heart);

	for (int k = 0; k < 8; k++)
	{
		for (int i = 0; i < d_u[k].size(); i++)
		{
			for (int j = 0; j < 30; j++)
			{
				float d_center_x = d_u[k][i].Unit_destination_rect.x + d_u[k][i].Unit_destination_rect.w / 2;
				float d_center_y = d_u[k][i].Unit_destination_rect.y + d_u[k][i].Unit_destination_rect.h / 2;
				float m_center_x = Boss.Monster_destination_rect.x + Boss.Monster_destination_rect.w / 2;
				float m_center_y = Boss.Monster_destination_rect.y + Boss.Monster_destination_rect.h / 2;

				if ((d_center_x + d_u[k][i].attack_length >m_center_x &&d_center_x - d_u[k][i].attack_length < m_center_x) &&
					(d_center_y + d_u[k][i].attack_length > m_center_y && d_center_y - d_u[k][i].attack_length < m_center_y)) 
				{
					if (Boss.HP > 0 && !d_u[k][i].motionattack) {
						AttackMonster(k, j, i);
						able_to_attack = true;
						if (!attack_ing[k][i])
						{
							d_u[k][i].Attack_End_destination_rect.x = m_center_x;
							d_u[k][i].Attack_End_destination_rect.y = m_center_y;

							attack_ing[k][i] = true;
						}

						break;
					}
				}
				else
					able_to_attack = false;
			}
			if ((k == 0 && Agu_upgrage) || (k == 1 && Papi_upgrage) || (k == 2 && Pad_upgrage) || (k == 3 && Pal_upgrage))
			{
				switch (k)
				{
				case 0:
					d_u[4][0].Unit_destination_rect.x = 120;
					d_u[4][0].Unit_destination_rect.y = 500;
					break;
				case 1:
					d_u[5][0].Unit_destination_rect.x = 200;
					break;
				case 2:
					d_u[6][0].Unit_destination_rect.x = 290;
					d_u[6][0].Unit_destination_rect.y = 500;
					break;
				case 3:
					d_u[7][0].Unit_destination_rect.x = 375;
					d_u[7][0].Unit_destination_rect.y = 503;
					break;
				}
				 
				d_u[k][0].Unit_destination_rect.x = -100;
			}
			d_u[k][i].RenderUnit(k,m_respawn, able_to_attack);
			if (able_to_attack)
			{
				d_u[k][i].RenderAttack(m_respawn, d_u[k][i].Attack_End_destination_rect.x, d_u[k][i].Attack_End_destination_rect.y);
				if (d_u[k][i].Attack_End_destination_rect.x + d_u[k][i].Attack_End_destination_rect.w / 2 <= d_u[k][i].Attack_destination_rect.x && d_u[k][i].Attack_End_destination_rect.y + d_u[k][i].Attack_End_destination_rect.h / 2 <= d_u[k][i].Attack_destination_rect.y)
					attack_ing[k][i] = false;
			}
		}
	}

	multiple_dest_rect.y = heart_dest_rect.y = 20;
	money_dest_rect.x = 615;
	money_dest_rect.y = 485;
	money_dest_rect.w = 180;
	money_dest_rect.h = 85;
	SDL_RenderCopy(g_renderer, text_multiple, &multiple_src_rect, &multiple_dest_rect);
	SDL_RenderCopy(g_renderer, text_money, &money_src_rect, &money_dest_rect);
	SDL_RenderCopy(g_renderer, text_heart, &heart_src_rect, &heart_dest_rect);
	SDL_RenderPresent(g_renderer);
}

void StageHandler::HandleEvents()
{
	int win_w, win_h;
	SDL_GetWindowSize(g_window, &win_w, &win_h);
	
	int x, y;

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
				x = event.button.x;
				y = event.button.y;
				if (g_current_game_phase == 6)
				{
					if ((120 <= x && x <= 180) && (475 <= y && y < 495))
					{
						if (money > 100 && !Agu_upgrage)
						{
							money -= 100;
							Agu_upgrage = true;
						}
						
					}
					else if ((205 <= x && x <= 265) && (475 <= y && y < 495))
					{
						if (money > 150 && !Papi_upgrage)
						{
							money -= 150;
							Papi_upgrage = true;
						}
					}
					else if ((290 <= x && x <= 350) && (475 <= y && y < 495))
					{
						if (money > 175 && !Pad_upgrage)
						{
							money -= 175;
							Pad_upgrage = true;
						}
					}
					else if ((370 <= x && x <= 430) && (475 <= y && y < 495))
					{
						if (money > 125 && !Pal_upgrage)
						{
							money -= 125;
							Pal_upgrage = true;
						}
					}
				}
				if (g_current_game_phase <= 6) {
					if (g_current_game_phase >= 2)
					{
						if (g_current_game_phase >= 3)
						{
							if (g_current_game_phase >= 4)
							{
								if (g_current_game_phase >= 5)
								{
									if ((270 <= x && x <= 370) && (450 <= y && y < 500))
									{
										if (money >= 175 && !Pad_upgrage)
										{
											money -= 175;
											Pad_upgrage = true;
										}
									}
									else if ((390 <= x && x <= 490) && (450 <= y && y < 500))
									{
										if (money >= 125 && !Pal_upgrage)
										{
											money -= 125;
											Pal_upgrage = true;
										}
									}
								}
								if ((30 <= x && x <= 130) && (450 <= y && y < 500))
								{
									if (money >= 100 && !Agu_upgrage)
									{
										money -= 100;
										Agu_upgrage = true;
									}
								}
								else if ((150 <= x && x <= 250) && (450 <= y && y < 500))
								{
									if (money >= 150 && !Papi_upgrage)
									{
										money -= 150;
										Papi_upgrage = true;
									}
								}
							}
							if ((270 <= x && x <= 370) && (500 <= y && y <= 600))
							{
								if (Pad_upgrage)
									unit_num = 6;
								else
									unit_num = 2;
							}
							else if ((390 <= x && x <= 490) && (500 <= y && y <= 600))
							{
								if (Pal_upgrage)
									unit_num = 7;
								else
									unit_num = 3;
							}
							if (money >= d_u[unit_num][0].price)
							{
								if ((270 <= x && x <= 370) && (500 <= y && y <= 600))
								{
									createmonster = OurMonster(x, y, unit_num);
								}
								else if ((390 <= x && x <= 490) && (500 <= y && y <= 600))
								{
									createmonster = OurMonster(x, y, unit_num);
								}
							}
						}
						if ((30 <= x && x <= 130) && (500 <= y && y <= 600)) {
							if (Agu_upgrage)
								unit_num = 4;
							else
								unit_num = 0;
						}
						else if ((150 <= x && x <= 250) && (500 <= y && y <= 600))
						{
							if (Papi_upgrage)
								unit_num = 5;
							else
								unit_num = 1;
						}
						if (money >= d_u[unit_num][0].price)
						{
							if ((30 <= x && x <= 130) && (500 <= y && y <= 600)) {
								createmonster = OurMonster(x, y, unit_num);
							}
							else if ((150 <= x && x <= 250) && (500 <= y && y <= 600))
							{
								createmonster = OurMonster(x, y, unit_num);
							}
						}
					}
				}
				break;
		case SDL_MOUSEMOTION:
			if (event.button.button == SDL_BUTTON_LEFT && createmonster)
			{
				d_u[unit_num][d_u[unit_num].size() - 1].motionattack = true;
				d_u[unit_num][d_u[unit_num].size() - 1].Unit_destination_rect.x = event.motion.x / 50 * 50 + 50;
				d_u[unit_num][d_u[unit_num].size() - 1].Unit_destination_rect.y = event.motion.y / 50 * 50;
				CheckOverlap(d_u[unit_num][d_u[unit_num].size() - 1].Unit_destination_rect.x, d_u[unit_num][d_u[unit_num].size() - 1].Unit_destination_rect.y, unit_num);
				CheckLoad(g_current_game_phase,d_u[unit_num][d_u[unit_num].size() - 1].Unit_destination_rect.x, d_u[unit_num][d_u[unit_num].size() - 1].Unit_destination_rect.y, unit_num);

			}
			break;

		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT && createmonster)
			{
				d_u[unit_num][d_u[unit_num].size() - 1].motionattack = false;
				cout << unit_num << d_u[unit_num].size() - 1 << endl;
				money -= d_u[unit_num][d_u[unit_num].size() - 1].price;
				createmonster = false;
			}
			break;

		default:
			break;
			}
		}
	}
	UpdateMoneyTexture(money);
}

void StageHandler::MoveMonster(int stnum)
{
	for (int i = 0; i < m_count-diecount; i++)
	{
		
		switch (stnum)
		{
		case DIGIMON_DEFENCE_STAGE1_PHASE:

			d_m[0][i].Move(stnum);
			if (d_m[0][i].Monster_destination_rect.x == 1000 && d_m[0][i].HP > 0)
			{
				//cout << heart << endl;
				if (heart > 0)
				{
					heart--;
					UpdateheartTexture(heart);
					d_m[0].erase(d_m[0].begin());
					diecount++;
				}
			}
			break;
		case DIGIMON_DEFENCE_STAGE2_PHASE:
			d_m[1][i].Move(stnum);

			if (d_m[1][i].Monster_destination_rect.x == 1000 && d_m[1][i].HP > 0)
			{
				//cout << heart << endl;
				if (heart > 0)
				{
					heart--;
					UpdateheartTexture(heart);
					d_m[1].erase(d_m[1].begin());
					diecount++;
				};
			}
			break;

		case DIGIMON_DEFENCE_STAGE3_PHASE:
			d_m[2][i].Move(stnum);

			if (d_m[2][i].Monster_destination_rect.x == 1000 && d_m[2][i].HP > 0)
			{
				//cout << heart << endl;
				if (heart > 0)
				{
					heart--;
					UpdateheartTexture(heart);
					d_m[2].erase(d_m[2].begin());
					diecount++;
				}
			}
			break;

		case DIGIMON_DEFENCE_STAGE4_PHASE:
			d_m[3][i].Move(stnum);

			if (d_m[3][i].Monster_destination_rect.x == 1000 && d_m[3][i].HP > 0)
			{
				//cout << heart << endl;
				if (heart > 0)
				{
					heart--;
					UpdateheartTexture(heart);
					d_m[3].erase(d_m[3].begin());
					diecount++;
				}
			}
			break;
		}
	}
	m_respawn++;
	if (m_respawn == 120)
	{
		m_respawn = 0;
		if (m_count < 30)
			m_count++;
	}
}
void StageHandler::AttackMonster(int k, int j, int i)
{
	if (g_current_game_phase == DIGIMON_DEFENCE_BOSS_PHASE)
	{
		if (attack_delay > d_u[k][i].attack_speed * 10)
		{
			Boss.Attacked(d_u[k][i].Attack());
			attack_delay = 0;
		}
		else
			attack_delay += 8;
	}
	else
	{
		if (attack_delay > d_u[k][i].attack_speed * 10)
		{
			d_m[g_current_game_phase-2][j].Attacked(d_u[k][i].Attack());
			attack_delay = 0;

			if (d_m[g_current_game_phase - 2][j].HP <= 0) {
				vector<Digimon_Monster>::iterator itr = d_m[g_current_game_phase - 2].begin() + j;
				d_m[g_current_game_phase - 2].erase(itr);
				
				diecount++;
				
			}
		}
		else
			attack_delay += 8;
	}


}

void StageHandler::UpdateMoneyTexture(int m) {
	if (money != 500)
		SDL_DestroyTexture(text_money);

	SDL_Surface *tmp_surface = TTF_RenderText_Blended(game_font_, std::to_string((long long)m).c_str(), white);
	money_src_rect.x = 0;
	money_src_rect.y = 0;
	money_src_rect.w = money_dest_rect.w = tmp_surface->w;
	money_src_rect.h = money_dest_rect.h = tmp_surface->h;

	text_money = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);

	SDL_FreeSurface(tmp_surface);
}

void StageHandler::UpdateheartTexture(int h) {
	if (heart != 5)
		SDL_DestroyTexture(text_heart);

	SDL_Surface * heart_surface = TTF_RenderText_Blended(heart_font_, std::to_string((long long)h).c_str(), white);
	heart_src_rect.x = 0;
	heart_src_rect.y = 0;
	heart_src_rect.w = heart_dest_rect.w = heart_surface->w;
	heart_src_rect.h = heart_dest_rect.h = heart_surface->h;

	text_heart = SDL_CreateTextureFromSurface(g_renderer, heart_surface);

	SDL_FreeSurface(heart_surface);
}

bool StageHandler::CheckOverlap(int xpos, int ypos, int i)
{
	
	for (int k = 0; k < 8; k++)
	{
		for (int j = 1; j < d_u[k].size(); j++)
		{
			if (d_u[k][j].Unit_destination_rect.x == xpos && d_u[k][j].Unit_destination_rect.y == ypos)
			{

				CheckOverlap(xpos - 50, ypos, i);
				d_u[i][d_u[i].size()-1].Unit_destination_rect.x -= 50;
				return true;
			}
		}
	}
	return false;
}
bool StageHandler::CheckLoad(int stnum, int xpos, int ypos, int i)
{
	switch (stnum)
	{
	case DIGIMON_DEFENCE_STAGE1_PHASE:

		if (ypos ==300)
		{
			StageHandler::CheckOverlap(xpos, ypos - 50, i);
			d_u[i][d_u[i].size() - 1].Unit_destination_rect.y -= 50;
			return true;
		}
		return false;
		break;
	case DIGIMON_DEFENCE_STAGE2_PHASE:
		if ((xpos <= 150 && ypos == 250) || (xpos >= 400 && ypos == 200))
		{
			StageHandler::CheckOverlap(xpos, ypos - 50, i);
			d_u[i][d_u[i].size() - 1].Unit_destination_rect.y -= 50;
			return true;
		}
		else if (xpos >= 150 && xpos <= 400 && ypos == 350 )
		{
			StageHandler::CheckOverlap(xpos, ypos + 50, i);
			d_u[i][d_u[i].size() - 1].Unit_destination_rect.y += 50;
			return true;
		}
		else if (xpos == 150 && ypos == 300)
		{
			StageHandler::CheckOverlap(xpos - 50, ypos, i);
			d_u[i][d_u[i].size() - 1].Unit_destination_rect.x -= 50;
			return true;
		}
		else if (xpos == 400 && ypos >= 250 && ypos <= 300)
		{
			StageHandler::CheckOverlap(xpos + 50, ypos, i);
			d_u[i][d_u[i].size() - 1].Unit_destination_rect.x += 50;

		}
		return false;

		break;
	case DIGIMON_DEFENCE_STAGE3_PHASE:
		if (xpos == 100 && ypos <= 350)
		{
			StageHandler::CheckOverlap(xpos - 50, ypos, i);
			d_u[i][d_u[i].size() - 1].Unit_destination_rect.x -= 50;
			return true;
		}
		else if (xpos >= 150 && xpos <= 500 && ypos == 350)
		{
			StageHandler::CheckOverlap(xpos, ypos + 50, i);
			d_u[i][d_u[i].size() - 1].Unit_destination_rect.y += 50;
			return true;
		}
		else if (xpos == 500 && ypos <= 300 && ypos >= 100)
		{
			StageHandler::CheckOverlap(xpos - 50, ypos, i);
			d_u[i][d_u[i].size() - 1].Unit_destination_rect.x -= 50;
			return true;
		}
		else if (xpos >= 550 && ypos ==100)
		{
			StageHandler::CheckOverlap(xpos, ypos - 50, i);
			d_u[i][d_u[i].size() - 1].Unit_destination_rect.y -= 50;

		}
		return false;

		break;
	case DIGIMON_DEFENCE_STAGE4_PHASE:
		if (xpos <= 900 && ypos == 200)
		{
			StageHandler::CheckOverlap(xpos, ypos - 50, i);
			d_u[i][d_u[i].size() - 1].Unit_destination_rect.y -= 50;
			return true;
		}
		else if (xpos == 900 && ypos >= 200 && ypos <= 300)
		{
			StageHandler::CheckOverlap(xpos + 50, ypos , i);
			d_u[i][d_u[i].size() - 1].Unit_destination_rect.x += 50;
			return true;
		}
		else if (xpos <= 900 && xpos >= 100 && ypos == 300)
		{
			StageHandler::CheckOverlap(xpos, ypos - 50, i);
			d_u[i][d_u[i].size() - 1].Unit_destination_rect.y -= 50;
			return true;
		}
		else if (xpos == 100 && ypos >= 300 && ypos <= 400)
		{
			StageHandler::CheckOverlap(xpos - 50, ypos, i);
			d_u[i][d_u[i].size() - 1].Unit_destination_rect.x -= 50;
			return true;
		}
		else if (xpos >= 100 && ypos == 400)
		{
			StageHandler::CheckOverlap(xpos, ypos + 50, i);
			d_u[i][d_u[i].size() - 1].Unit_destination_rect.y += 50;
			return true;
		}
		
		return false;
		break;
	case DIGIMON_DEFENCE_BOSS_PHASE:	

		break;
	}
	
}
void StageHandler::Gameover()
{
	if (g_current_game_phase == DIGIMON_DEFENCE_BOSS_PHASE && Boss.HP <= 0)
	{
		clearbgm = Mix_LoadMUS("../Resources/Sound/clear.mp3");
		Mix_VolumeMusic(128);
		Mix_PlayMusic(clearbgm, -1);

		stage_clear.BeforePhase(g_current_game_phase - 1);
		g_current_game_phase = DIGIMON_DEFENCE_CLEAR_PHASE;
	}
	else
	{
		g_current_game_phase = DIGIMON_DEFENCE_GAMEOVER_PHASE;
		clearbgm = Mix_LoadMUS("../Resources/Sound/over.mp3");
		Mix_VolumeMusic(128);
		Mix_PlayMusic(clearbgm, -1);
	}
	for (int i = 0; i <= g_current_game_phase - 2; i++)
	{
		if(i<4)
			d_m[i].clear();
		for (int j = 0; j < 30; j++)
		{
			switch (i)
			{
			case 0:
				d_m[i].push_back(Digimon_Monster(-50, 300, 1, 0.8, 2, i)); // x, y, hp, spd
				break;
			case 1:
				d_m[i].push_back(Digimon_Monster(-50, 250, 14, 2, 2, i));//14
				break;
			case 2:
				d_m[i].push_back(Digimon_Monster(100, -50, 241, 0.5, 3, i));//241
				break;
			case 3:
				d_m[i].push_back(Digimon_Monster(-50, 200, 165, 2.5, 3, i));//165
				break;
			case 4:
				Boss = Digimon_Monster(450, 250, 5000, 0, 2, i);//5000
				break;

			}
		}
	}


	ReInit();
	heart = 5;
	money = 500;
	UpdateheartTexture(heart);
	
	Agu_upgrage = false;
	Papi_upgrage = false;
	Pad_upgrage = false;
	Pal_upgrage = false;
}

void StageHandler::Clear()
{

	ReInit();
	money += 500;
	
	stage_clear.BeforePhase(g_current_game_phase - 1);
	if(g_current_game_phase == DIGIMON_DEFENCE_BOSS_PHASE)
		g_current_game_phase = DIGIMON_DEFENCE_ENDING_PHASE;
	else
		g_current_game_phase = DIGIMON_DEFENCE_CLEAR_PHASE;
}
void StageHandler::ReInit()
{
	if (g_current_game_phase == 2)
		Mix_FreeMusic(stage1bgm);
	else if (g_current_game_phase == 3)
		Mix_FreeMusic(stage2bgm);
	else if (g_current_game_phase == 4)
		Mix_FreeMusic(stage3bgm);
	else if (g_current_game_phase == 5)
		Mix_FreeMusic(stage4bgm);
	else if (g_current_game_phase == 6)
		Mix_FreeMusic(bossbgm);

	m_count = 0;
	m_respawn = 0;
	
	able_to_attack = false;
	attack_delay = 0;
	overlap = true;
	createmonster = false;
	diecount = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 10; j++)
			attack_ing[i][j] = false;
	money_dest_rect.x = 800;
	money_dest_rect.y = 525;
	money_dest_rect.w = 180;
	money_dest_rect.h = 85;
	for (int i = 0; i < 8; i++) {
		vector<Digimon_Unit> temp_u[8];
		temp_u[i].swap(d_u[i]);
	}
	d_u[0].push_back(Digimon_Unit(75, 510, 0, 0, 0, 2, 50, 0));
	d_u[1].push_back(Digimon_Unit(180, 510, 0, 0, 0, 2, 75, 1));
	d_u[2].push_back(Digimon_Unit(285, 510, 0, 0, 0, 3, 75, 2));
	d_u[3].push_back(Digimon_Unit(380, 505, 0, 0, 0, 3, 100, 3));
	d_u[4].push_back(Digimon_Unit(-100, 510, 0, 0, 0, 2, 125, 4));
	d_u[5].push_back(Digimon_Unit(-100, 510, 0, 0, 0, 2, 150, 5));
	d_u[6].push_back(Digimon_Unit(-100, 510, 0, 0, 0, 3, 200, 6));
	d_u[7].push_back(Digimon_Unit(-100, 505, 0, 0, 0, 3, 150, 7));
	SDL_RenderClear(g_renderer);
}
void StageHandler::CheckClear()
{
	if (g_current_game_phase == DIGIMON_DEFENCE_BOSS_PHASE)
	{
		if (Boss.HP <= 0) {
			Gameover();
		}
		if (heart <= 0)
			Gameover();
	}
	else
	{
		if (d_m[g_current_game_phase - 2].size() == 0 && heart > 0)
			Clear();
		if (heart == 0)
			Gameover();
	}
}