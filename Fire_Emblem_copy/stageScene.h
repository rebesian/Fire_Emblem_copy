#pragma once
#include "gameNode.h"
#include "tileSet.h"
#include "warrior.h"
class stageScene : public gameNode
{
private:

	tileSet* _tileSet;
	warrior* _warrior;
public:
	HRESULT init();
	void update();
	void release();
	void render();

};

