#pragma once

#include<vector>
#include<iostream>
#include "SDL.h"
#include "SDL_ttf.h"
#include "Digimon_Monster.h"
#include <string>

using namespace std;

class Digimon_Stage
{
private:
	vector<Digimon_Monster>  d_m;

public:
	Digimon_Stage();
	~Digimon_Stage();
	void HandleEvents();
	void Update();
	virtual void Render() = 0;
	virtual void Init_Road() = 0;
};

class Stage1 : public Digimon_Stage
{
private:
	SDL_Texture * background_texture;
	SDL_Rect background_source_rect;
	SDL_Rect background_destination_rect;
	SDL_Texture* Road_texture;
	SDL_Rect Road_source_rect[6];
	vector<SDL_Rect> Road_destination_rect;

	SDL_Texture * upgrade_texture;
	SDL_Rect upgrade_rect;
	SDL_Rect upgrade_destination_rect;
	SDL_Texture * digivice_texture;
	SDL_Rect digivice_rect;
	SDL_Rect digivice_destination_rect;

public:
	Stage1();
	virtual void Init_Road();
	virtual void Render();
};
class Stage2 : public Digimon_Stage
{
private:
	SDL_Texture * background_texture;
	SDL_Rect background_source_rect;
	SDL_Rect background_destination_rect;
	SDL_Texture* Road_texture;
	SDL_Rect Road_source_rect[6];
	vector<SDL_Rect> Road_destination_rect;
	SDL_Texture * digivice_texture;
	SDL_Rect digivice_rect;
	SDL_Rect digivice_destination_rect;

public:
	Stage2();
	virtual void Init_Road();
	virtual void Render();
};
class Stage3 : public Digimon_Stage
{
private:
	SDL_Texture * background_texture;
	SDL_Rect background_source_rect;
	SDL_Rect background_destination_rect;
	SDL_Texture* Road_texture;
	SDL_Rect Road_source_rect[6];
	vector<SDL_Rect> Road_destination_rect;
	SDL_Texture * digivice_texture;
	SDL_Rect digivice_rect;
	SDL_Rect digivice_destination_rect;

	SDL_Texture * upgrade_texture;
	SDL_Rect upgrade_rect;
	SDL_Rect upgrade_destination_rect;
	SDL_Texture * upgrade2_texture;
	SDL_Rect upgrade2_rect;
	SDL_Rect upgrade2_destination_rect;
public:
	Stage3();
	virtual void Init_Road();
	virtual void Render();
};
class Stage4 : public Digimon_Stage
{
private:
	SDL_Texture * background_texture;
	SDL_Rect background_source_rect;
	SDL_Rect background_destination_rect;
	SDL_Texture* Road_texture;
	SDL_Rect Road_source_rect[6];
	vector<SDL_Rect> Road_destination_rect;
	SDL_Texture * digivice_texture;
	SDL_Rect digivice_rect;
	SDL_Rect digivice_destination_rect;
	SDL_Texture * upgrade_texture;
	SDL_Rect upgrade_rect;
	SDL_Rect upgrade_destination_rect;
	SDL_Texture * upgrade2_texture;
	SDL_Rect upgrade2_rect;
	SDL_Rect upgrade2_destination_rect;
	SDL_Texture * upgrade3_texture;
	SDL_Rect upgrade3_rect;
	SDL_Rect upgrade3_destination_rect;
	SDL_Texture * upgrade4_texture;
	SDL_Rect upgrade4_rect;
	SDL_Rect upgrade4_destination_rect;
public:
	Stage4();
	virtual void Init_Road();
	virtual void Render();
};
class Boss_Stage : public Digimon_Stage
{
private:
	SDL_Texture * background_texture;
	SDL_Rect background_source_rect;
	SDL_Rect background_destination_rect;
	SDL_Texture* Road_texture;
	SDL_Rect Road_source_rect[6];
	vector<SDL_Rect> Road_destination_rect;
	SDL_Texture * digivice_texture;
	SDL_Rect digivice_rect;
	SDL_Rect digivice_destination_rect;
	SDL_Texture * upgrade_texture;
	SDL_Rect upgrade_rect;
	SDL_Rect upgrade_destination_rect;
	SDL_Texture * upgrade2_texture;
	SDL_Rect upgrade2_rect;
	SDL_Rect upgrade2_destination_rect;
	SDL_Texture * upgrade3_texture;
	SDL_Rect upgrade3_rect;
	SDL_Rect upgrade3_destination_rect;
	SDL_Texture * upgrade4_texture;
	SDL_Rect upgrade4_rect;
	SDL_Rect upgrade4_destination_rect;
public:
	Boss_Stage();
	virtual void Init_Road();
	virtual void Render();
};
class Digimon_Ending
{
private:
	SDL_Texture * background_texture;
	SDL_Rect background_source_rect;
	SDL_Rect background_destination_rect;

public:
	Digimon_Ending();
	~Digimon_Ending();
	void HandleEvents();
	//void Update();
	void endRender();
};
