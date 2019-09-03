#pragma once
#include<vector>
#include<iostream>
#include "SDL.h"
#include "SDL_ttf.h"
#include "Digimon_Stage.h"
#include "Digimon_Monster.h"
#include "Digimon_Unit.h"
class StageHandler
{
private :
	bool Agu_upgrage = false;
	bool Papi_upgrage = false;
	bool Pad_upgrage = false;
	bool Pal_upgrage = false;
	Stage1 st1;
	Stage2 st2;
	Stage3 st3;
	Stage4 st4;
	vector<Digimon_Monster>  d_m[4];
	vector<Digimon_Unit> d_u[8];
	TTF_Font *game_font_;
	TTF_Font *heart_font_;
	//SDL_Color white;
	SDL_Texture *text_money;
	SDL_Rect money_src_rect;
	SDL_Rect money_dest_rect;
	SDL_Texture * text_multiple;
	SDL_Rect multiple_src_rect;
	SDL_Rect multiple_dest_rect;
	SDL_Texture *text_heart;
	SDL_Rect heart_src_rect;
	SDL_Rect heart_dest_rect;
	Boss_Stage BS;
	Digimon_Monster Boss;

	int m_count;
	int m_respawn;
	bool able_to_attack;
	bool attack_ing[8][10];
	bool createmonster;
	bool overlap;
	int attack_delay;
	int money;
	int heart;
	int diecount = 0;
	int who_attack;

public :
	StageHandler();
	~StageHandler();
	void Stage1Render();
	void Stage2Render();
	void Stage3Render();
	void Stage4Render();
	void BossStageRender();
	bool OurMonster(int x, int y, int i);
	void MoveMonster(int stnum);
	void HandleEvents();
	void AttackMonster(int k, int i,int j);
	void UpdateMoneyTexture(int m);
	void UpdateheartTexture(int h);
	bool CheckOverlap(int xpos, int ypos, int i);
	bool CheckLoad(int stnum, int xpos, int ypos, int i);
	void Gameover();
	void Clear();
	void ReInit();
	void CheckClear();
};