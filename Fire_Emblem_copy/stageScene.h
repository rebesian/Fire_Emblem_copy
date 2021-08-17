#pragma once
#include "gameNode.h"
#include "tileSet.h"
class stageScene : public gameNode
{
private:

	tileSet* _tileSet;

public:
	HRESULT init();
	void update();
	void release();
	void render();

};

