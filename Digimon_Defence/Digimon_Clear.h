#include "SDL_image.h"

class StageClear 
{
public:
	StageClear();
	~StageClear();
	void HandleEvents();
	void Render();
	void BeforePhase(int before_num);
};
