#pragma once
#include "gameNode.h"
#include "tileSet.h"
#include "warrior.h"
#include "Roy.h"
class stageScene : public gameNode
{
private:

	tileSet* _tileSet;
	warrior* _warrior;
	Roy* _roy;
public:
	HRESULT init();
	void update();
	void release();
	void render();

};

