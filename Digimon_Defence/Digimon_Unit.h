#pragma once
#include "SDL_image.h"
#include <vector>
#include<iostream>
using namespace std; 
class Digimon_Unit
{
private:

public:

	vector<SDL_Rect> Unit_source_rect;
	SDL_Rect Unit_destination_rect;
	SDL_Texture *Unit_texture;
	SDL_Rect Attack_source_rect;
	SDL_Rect Attack_destination_rect;
	SDL_Rect Attack_End_destination_rect;
	SDL_Texture *Attack_texture;

	int xpos, ypos;
	float power;
	int attack_length;
	float attack_speed;
	int attack_term=0;
	int Unit_idx = 0;
	int price;
	int Unit_num;
	bool motionattack=false;
	Digimon_Unit();
	Digimon_Unit(int x, int y, int power, int at_len, float at_spd, int idx, int price, int unit_num);
	~Digimon_Unit();
	float Attack();
	void Init_Unit(int stnum);
	void Init_Attack(int stnum);
	void RenderUnit(int stnum, int idx, bool atk);
	void RenderAttack(int idx,int xpos,int ypos);
	void upgrade();
};