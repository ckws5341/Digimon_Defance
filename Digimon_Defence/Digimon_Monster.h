#pragma once
#include "SDL_image.h"
#include <vector>
#include<iostream>
using namespace std;
class Digimon_Monster
{
private :

public:
	SDL_Surface * Monster_Surface;
	vector<SDL_Rect> Monster_source_rect;
	SDL_Rect Monster_destination_rect;
	SDL_Texture * Monster_texture;
	SDL_Texture * Devil_attack_texture;
	SDL_Rect Devil_attack_source_rect;
	SDL_Rect Devil_attack_destination_rect;

	float xpos, ypos;
	float speed;
	int monster_idx = 0;
	float HP;
	Digimon_Monster();
	Digimon_Monster(int x, int y, int hp, float spd, int idx, int stnum);
	~Digimon_Monster();
	void Move(int stnum);
	void Init_Monster(int stnum);
	void Render(int idx);
	int BossRender(int h);
	void Attacked(int dmg);
	void Init_Attack(int stnum);
};