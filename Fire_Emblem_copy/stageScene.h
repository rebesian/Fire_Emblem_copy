#pragma once
#include "gameNode.h"
#include "tileSet.h"
#include "warrior.h"
#include "Roy.h"
class stageScene : public gameNode
{
private:
	struct POINTER
	{
		int indexX;
		int indexY;
		RECT _rc;
		image* _img = IMAGEMANAGER->findImage("현재타일");
	};

	tileSet* _tileSet;
	warrior* _warrior;
	Roy* _roy;
	POINTER _pt;

	int mapSizeX;
	int mapSizeY;
	int selectEnemy;

public:

	HRESULT init();
	void update();
	void release();
	void render();

};

